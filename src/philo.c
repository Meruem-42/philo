/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:44:37 by alex              #+#    #+#             */
/*   Updated: 2025/06/12 18:02:17 by aherlaud         ###   ########.fr       */
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

time_t	tv_to_ms(struct timeval time)
{
	time_t	time_full;

	time_full = time.tv_sec;
	time_full = time_full * 1000;
	time_full = time_full + (time.tv_usec / 1000);
	return (time_full);
}

time_t	time_diff(struct timeval start, struct timeval end)
{
	time_t	start_full;
	time_t	end_full;

	start_full = tv_to_ms(start);
	end_full = tv_to_ms(end);
	return (end_full - start_full);
}

void	think_routine(t_philo *philo, int index)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	printf("%ld %d is thinking\n", time_diff((philo->data)->initial_time, time),
		index + 1);
}

void	sleep_routine(t_philo *philo, int index)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	printf("%ld %d is sleeping\n", time_diff((philo->data)->initial_time, time),
		index + 1);
	printf("\t\t\t\t\t\ttime to sleep : %d\n", ((philo->data)->time_to_sleep));
	usleep(((philo->data)->time_to_sleep) * 1000);
	printf("\t\t\t\t\t\t%ld %d finished sleeping\n",
		time_diff((philo->data)->initial_time, time), index + 1);
}

void	eat_routine(t_philo *philo, int index, int nb_philo)
{
	struct timeval	time;
	int				fork_l;
	int				fork_r;

	if (index == 0)
	{
		fork_l = index;
		fork_r = nb_philo - 1;
	}
	else
	{
		fork_l = index - 1;
		fork_r = index;
	}
	pthread_mutex_lock(&(((philo->data)->lock_tab)[fork_l]));
	gettimeofday(&time, NULL);
	printf("%ld %d has taken a fork\n", time_diff((philo->data)->initial_time,
			time), index + 1);
	pthread_mutex_lock(&(((philo->data)->lock_tab)[fork_r]));
	gettimeofday(&time, NULL);
	printf("%ld %d has taken a fork\n", time_diff((philo->data)->initial_time,
			time), index + 1);
	gettimeofday(&time, NULL);
	printf("%ld %d is eating\n", time_diff((philo->data)->initial_time, time),
		index + 1);
	gettimeofday(&time, NULL);
	philo->last_meal = time;
	philo->nb_eat += 1;
	if (philo->nb_eat == (philo->data)->nb_meal)
		(philo->data)->is_full += 1;
	usleep(((philo->data)->time_to_eat) * 1000);
	pthread_mutex_unlock(&(((philo->data)->lock_tab)[fork_r]));
	pthread_mutex_unlock(&(((philo->data)->lock_tab)[fork_l]));
}

void	*philo_behavior(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->index % 2 == 0)
		usleep(1000);
	while (1)
	{
		eat_routine(philo, philo->index, (philo->data)->nb_philo);
		if ((philo->data)->is_dead > 0
			|| (philo->data)->is_full == (philo->data)->nb_philo)
			break ;
		sleep_routine(philo, philo->index);
		if ((philo->data)->is_dead > 0
			|| (philo->data)->is_full == (philo->data)->nb_philo)
			break ;
		think_routine(philo, philo->index);
		if ((philo->data)->is_dead > 0
			|| (philo->data)->is_full == (philo->data)->nb_philo)
			break ;
	}
	return (NULL);
}
// printf("\t\t\t\t\tlast meal of philo %d is %ld", (philo->index) + 1,
// philo->last_meal);

void	begin_thread(t_philo *philo)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, philo_behavior, philo);
	pthread_detach(thread);
}

void	*manager_thread(void *arg)
{
	int				i;
	t_philo			*philo;
	struct timeval	time;

	philo = (t_philo *)arg;
	while (1)
	{
		i = 0;
		while (i < ((philo[0]).data)->nb_philo)
		{
			gettimeofday(&time, NULL);
			printf("\t\t\t\t\t\tfor index %d : %ld\n", i + 1,
				time_diff(philo[i].last_meal, time));
			if (time_diff(philo[i].last_meal,
					time) >= philo[i].data->time_to_die)
			{
				philo->data->is_dead = i + 1;
				gettimeofday(&time, NULL);
				printf("%ld %d is dead\n",
					time_diff(philo[0].data->initial_time, time), i + 1);
				return (NULL);
			}
			i++;
		}
		if (((philo[0]).data)->is_full == ((philo[0]).data)->nb_philo)
		{
			gettimeofday(&time, NULL);
			printf("%ld everybody has eaten\n",
				time_diff(philo[0].data->initial_time, time));
			return (NULL);
		}
		usleep(8 * 1000);
	}
}

void	monitor_thread(t_philo *philo)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, manager_thread, philo);
	pthread_join(thread, NULL);
}

void	fill_tab(t_philo *philo_tab, t_data *data, int index)
{
	t_philo	philo;

	philo.data = data;
	philo.index = index;
	philo.nb_eat = 0;
	philo_tab[index] = philo;
}

void	philo(t_data *data)
{
	int				i;
	t_philo			*philo_tab;
	struct timeval	time;

	philo_tab = malloc((data->nb_philo) * sizeof(t_philo));
	if (!philo_tab)
		return ;
	i = 0;
	while (i < data->nb_philo)
		fill_tab(philo_tab, data, i++);
	i = 0;
	gettimeofday(&time, NULL);
	data->initial_time = time;
	if (data->nb_philo == 1)
	{
		printf("%ld %d has taken a fork\n", time_diff(data->initial_time,
				data->initial_time), 1);
		usleep(data->time_to_die * 1000);
		gettimeofday(&time, NULL);
		printf("%ld %d is dead\n", time_diff(data->initial_time, time), 1);
		return ;
	}
	while (i < data->nb_philo)
	{
		gettimeofday(&time, NULL);
		philo_tab[i].last_meal = time;
		begin_thread(&(philo_tab[i]));
		i++;
	}
	monitor_thread(philo_tab);
	return ;
}
