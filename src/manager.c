/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:53:49 by aherlaud          #+#    #+#             */
/*   Updated: 2025/06/15 18:54:14 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_iffull(t_philo *philo)
{
	struct timeval	time;

	pthread_mutex_lock((philo[0].data->lock_eat));
	if (((philo[0]).data)->is_full == ((philo[0]).data)->nb_philo)
	{
		pthread_mutex_unlock((philo[0].data->lock_eat));
		pthread_mutex_lock((philo[0].data->lock_write));
		gettimeofday(&time, NULL);
		printf("%ld everybody has eaten\n",
			time_diff(philo[0].data->initial_time, time));
		pthread_mutex_unlock((philo[0].data->lock_write));
		return (usleep(philo[0].data->time_to_eat * 1000), 0);
	}
	pthread_mutex_unlock((philo[0].data->lock_eat));
	return (1);
}

int	check_ifdead(t_philo *philo, int index)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	pthread_mutex_lock((philo[0].data->lock_time));
	if (time_diff(philo[index].last_meal,
			time) >= philo[index].data->time_to_die)
	{
		pthread_mutex_unlock((philo[0].data->lock_time));
		pthread_mutex_lock((philo[0].data->lock_dead));
		philo->data->is_dead = index + 1;
		pthread_mutex_unlock((philo[0].data->lock_dead));
		pthread_mutex_lock((philo[0].data->lock_write));
		gettimeofday(&time, NULL);
		printf("%ld %d is dead\n", time_diff(philo[0].data->initial_time, time),
			index + 1);
		pthread_mutex_unlock((philo[0].data->lock_write));
		return (usleep(philo[0].data->time_to_eat * 1000), 0);
	}
	pthread_mutex_unlock((philo[0].data->lock_time));
	return (1);
}

void	*manager_thread(void *arg)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		i = 0;
		while (i < ((philo[0]).data)->nb_philo)
		{
			if (check_ifdead(philo, i++) == 0)
				return (NULL);
		}
		if (check_iffull(philo) == 0)
			return (NULL);
		usleep(8 * 1000);
	}
}

void	monitor_thread(t_philo *philo)
{
	pthread_t thread;

	pthread_create(&thread, NULL, manager_thread, philo);
	pthread_join(thread, NULL);
}