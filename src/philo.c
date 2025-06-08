/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:44:37 by alex              #+#    #+#             */
/*   Updated: 2025/06/08 19:00:48 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// t_philo *ft_find_node(t_philo *philo, int index)
// {
// 	while (philo->index != index)
// 		philo = philo->next;
// 	return (philo);
// }

// t_philo *find_neighbor(t_philo *philo, int index)
// {
//     t_philo *tmp;

//     tmp = philo;
//     if(index == 0)
//         philo = ft_lstlast_philo(tmp);
//     else
//         philo = ft_find_node(tmp, index - 1);
//     return (philo);
// }

time_t tv_to_ms(struct timeval time)
{
	time_t time_full;

	time_full = time.tv_sec;
	time_full = time_full * 1000;
	time_full = time_full + (time.tv_usec / 1000);
	return (time_full);
}

time_t time_diff(struct timeval start, struct timeval end)
{
	time_t start_full;
	time_t end_full;

	start_full = tv_to_ms(start);	
	end_full = tv_to_ms(end);	

	return (end_full - start_full);
}

time_t times_over(t_philo *philo, int time_to_action)
{
	struct timeval	time;
	time_t time_micro;
	time_t time_passed;

	gettimeofday(&time, NULL);
	time_micro = tv_to_ms(time) - philo->last_meal + time_to_action;
	if(time_micro > ((philo->data)->time_to_die))
	{
		time_passed = tv_to_ms(time) - philo->last_meal;
		return ((((philo->data)->time_to_die)) - time_passed);
	}
	return (0);
}

void	think_routine(t_philo *philo, int index)
{
	struct timeval	time;
	int				time_to_think;

	time_to_think = ((philo->data)->time_to_die)
		- ((philo->data)->time_to_sleep) - ((philo->data)->time_to_eat);
	gettimeofday(&time, NULL);
	printf("%ld%ld %d is thinking\n", (time.tv_sec), (time.tv_usec) / 1000,
		index);
	if (time_to_think > 0)
		usleep(time_to_think * 1000);
}

void	sleep_routine(t_philo *philo, int index)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	printf("%ld%ld %d is sleeping\n", (time.tv_sec), (time.tv_usec) / 1000,
		index);
	if(times_over(philo, (philo->data)->time_to_sleep) > 0)
	{
		usleep(times_over(philo, (philo->data)->time_to_sleep) * 1000);
		philo->data->is_dead = index;
	}
	else
		usleep(((philo->data)->time_to_sleep) * 1000);
}

void	eat_routine(t_philo *philo, int index, int nb_philo)
{
	struct timeval	time;

	if (philo->index == 0)
	{
		pthread_mutex_lock(&(((philo->data)->lock_tab)[index]));
		gettimeofday(&time, NULL);
		printf("%ld%ld %d has taken a fork\n", (time.tv_sec), (time.tv_usec)
			/ 1000, index);
		pthread_mutex_lock(&(((philo->data)->lock_tab)[nb_philo - 1]));
		gettimeofday(&time, NULL);
		printf("%ld%ld %d has taken a fork\n", (time.tv_sec), (time.tv_usec)
			/ 1000, index);
		gettimeofday(&time, NULL);
		printf("%ld%ld %d is eating\n", (time.tv_sec), (time.tv_usec) / 1000,
			index);
		usleep(((philo->data)->time_to_sleep) * 1000);
		pthread_mutex_unlock(&(((philo->data)->lock_tab)[nb_philo - 1]));
		pthread_mutex_unlock(&(((philo->data)->lock_tab)[index]));
	}
	else
	{
		pthread_mutex_lock(&(((philo->data)->lock_tab)[index - 1]));
		gettimeofday(&time, NULL);
		printf("%ld%ld %d has taken a fork\n", (time.tv_sec), (time.tv_usec)
			/ 1000, index);
		pthread_mutex_lock(&(((philo->data)->lock_tab)[index]));
		gettimeofday(&time, NULL);
		printf("%ld%ld %d has taken a fork\n", (time.tv_sec), (time.tv_usec)
			/ 1000, index);
		gettimeofday(&time, NULL);
		printf("%ld%ld %d is eating\n", (time.tv_sec), (time.tv_usec) / 1000,
			index);
		usleep(((philo->data)->time_to_eat) * 1000);
		pthread_mutex_unlock(&(((philo->data)->lock_tab)[index]));
		pthread_mutex_unlock(&(((philo->data)->lock_tab)[index - 1]));
	}
}

void	*philo_behavior(void *arg)
{
	t_philo	*philo;
	struct timeval	time_start;


	philo = (t_philo *)arg;
	// if (philo->index % 2 == 1)
	// 	usleep(100);
	while (1)
	{
		gettimeofday(&time_start, NULL);
		philo->last_meal = tv_to_ms(time_start);
		eat_routine(philo, philo->index, (philo->data)->nb_philo);
		if((philo->data)->is_dead > 0)
			break;
		sleep_routine(philo, philo->index);
		if((philo->data)->is_dead > 0)
			break;
		think_routine(philo, philo->index);
		if((philo->data)->is_dead > 0)
			break;
	}
	return (NULL);
}

void	begin_thread(t_philo *philo)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, philo_behavior, philo);
	pthread_detach(thread);
}

void	fill_tab(t_philo *philo_tab, t_data *data, int index)
{
	t_philo	philo;

	philo.data = data;
	philo.index = index;
	philo_tab[index] = philo;
}

void	philo(t_data *data)
{
	int i;
	t_philo *philo_tab;
	// pthread_t thread;
	// t_philo philo;

	// (void)data;

	// while(1)
	// {
	// tmp = data->philo_lst;
	// create and seperate each struct for each philo
	philo_tab = malloc((data->nb_philo) * sizeof(t_philo));
	if (!philo_tab)
		return ;
	i = 0;
	while (i < data->nb_philo)
		fill_tab(philo_tab, data, i++);
	// begin all thread
	i = 0;
	while (i < data->nb_philo)
	{
		// t_philo
		// printf("%d\n", i);
		begin_thread(&(philo_tab[i]));
		i++;
	}
	while (1)
	{
	}
	// }
	// sleep(2);
	// pthread_detach(thread);
	return ;
}