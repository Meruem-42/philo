/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behavior.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:42:46 by aherlaud          #+#    #+#             */
/*   Updated: 2025/07/25 19:11:28 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_ifend_behavior(t_philo *philo)
{
	pthread_mutex_lock((philo->data->lock_dead));
	pthread_mutex_lock((philo->data->lock_eat));
	if ((philo->data)->is_dead > 0
		|| (philo->data)->is_full == (philo->data)->nb_philo)
	{
		pthread_mutex_unlock((philo->data->lock_eat));
		pthread_mutex_unlock((philo->data->lock_dead));
		return (0);
	}
	pthread_mutex_unlock((philo->data->lock_dead));
	pthread_mutex_unlock((philo->data->lock_eat));
	return (1);
}

int	sleep_routine(t_philo *philo)
{
	time_t			temp_time;
	struct timeval	time;

	print_message(philo, "is sleeping");
	gettimeofday(&time, NULL);
	temp_time = tv_to_ms(time) + (philo->data)->time_to_sleep;
	while (tv_to_ms(time) < temp_time)
	{
		pthread_mutex_lock((philo->data->lock_dead));
		pthread_mutex_lock((philo->data->lock_eat));
		if ((philo->data)->is_dead > 0
			|| (philo->data)->is_full == (philo->data)->nb_philo)
		{
			pthread_mutex_unlock((philo->data->lock_eat));
			pthread_mutex_unlock((philo->data->lock_dead));
			return (0);
		}
		pthread_mutex_unlock((philo->data->lock_dead));
		pthread_mutex_unlock((philo->data->lock_eat));
		gettimeofday(&time, NULL);
		usleep(100);
	}
	return (1);
}

void	*philo_behavior(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->index % 2 == 0)
		usleep(100);
	if (philo->index % 2 == 0 && philo->index == philo->data->nb_philo - 1)
		usleep(100);
	while (1)
	{
		eat_routine(philo);
		if (check_ifend_behavior(philo) == 0)
			return (NULL);
		sleep_routine(philo);
		if (check_ifend_behavior(philo) == 0)
			return (NULL);
		print_message(philo, "is thinking");
		if (check_ifend_behavior(philo) == 0)
			return (NULL);
	}
	return (NULL);
}

int	begin_thread(t_philo *philo)
{
	pthread_t		thread;
	struct timeval	time;

	gettimeofday(&time, NULL);
	philo->last_meal = time;
	if (pthread_create(&thread, NULL, philo_behavior, philo) != 0)
		return (0);
	pthread_detach(thread);
	return (1);
}
