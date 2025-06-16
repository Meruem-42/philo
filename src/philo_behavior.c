/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behavior.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:42:46 by aherlaud          #+#    #+#             */
/*   Updated: 2025/06/16 17:24:37 by aherlaud         ###   ########.fr       */
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

void	sleep_routine(t_philo *philo)
{
	print_message(philo, "is sleeping");
	usleep(((philo->data)->time_to_sleep) * 1000);
}

void	*philo_behavior(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->index % 2 == 0)
		usleep(500);
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
	pthread_t thread;
	struct timeval time;

	gettimeofday(&time, NULL);
	philo->last_meal = time;
	if (pthread_create(&thread, NULL, philo_behavior, philo) != 0)
		return (0);
	pthread_detach(thread);
	return (1);
}