/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:44:37 by alex              #+#    #+#             */
/*   Updated: 2025/06/07 18:04:42 by aherlaud         ###   ########.fr       */
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

	philo = (t_philo *)arg;
	// test
	// while(1)
	// {
	//     printf("index is %d\n", philo->index);
	//     usleep(3000 * 1000);
	// }
	// if (philo->index % 2 == 1)
	// 	usleep(100);
	eat_routine(philo, philo->index, (philo->data)->nb_philo);
	sleep_routine(philo, philo->index);
	think_routine(philo, philo->index);
	// gettimeofday(&time, NULL);
	// printf("%ld%ld %d is eating\n", (time.tv_sec), (time.tv_usec)/1000,
	// *((int *)arg));
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