/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:48:04 by aherlaud          #+#    #+#             */
/*   Updated: 2025/07/25 18:43:21 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	meal_count(t_philo *philo)
{
	pthread_mutex_lock((philo->data->lock_eat));
	philo->nb_eat += 1;
	if (philo->nb_eat == (philo->data)->nb_meal)
		(philo->data)->is_full += 1;
	pthread_mutex_unlock((philo->data->lock_eat));
}

void	fork_assignement(t_philo *philo)
{
	if (philo->index == 0)
	{
		philo->fork_l = philo->index;
		philo->fork_r = philo->data->nb_philo - 1;
	}
	else
	{
		philo->fork_l = philo->index - 1;
		philo->fork_r = philo->index;
	}
}

int	check_fork(t_philo *philo, int fork_l, int fork_r)
{
	pthread_mutex_lock((philo->data->lock_dead));
	pthread_mutex_lock((philo->data->lock_eat));
	if ((philo->data)->is_dead > 0
		|| (philo->data)->is_full == (philo->data)->nb_philo)
	{
		if (fork_r != -1)
			pthread_mutex_unlock((((philo->data)->lock_tab)[fork_r]));
		pthread_mutex_unlock((((philo->data)->lock_tab)[fork_l]));
		pthread_mutex_unlock((philo->data->lock_eat));
		pthread_mutex_unlock((philo->data->lock_dead));
		return (0);
	}
	pthread_mutex_unlock((philo->data->lock_dead));
	pthread_mutex_unlock((philo->data->lock_eat));
	return (1);
}

int	meal_time(t_philo *philo)
{
	time_t			temp_time;
	struct timeval	time;

	gettimeofday(&time, NULL);
	temp_time = tv_to_ms(time) + (philo->data)->time_to_eat;
	while (tv_to_ms(time) < temp_time)
	{
		if (check_fork(philo, philo->fork_l, philo->fork_r) == 0)
			return (0);
		gettimeofday(&time, NULL);
		usleep(100);
	}
	return (1);
}

void	eat_routine(t_philo *philo)
{
	struct timeval	time;

	fork_assignement(philo);
	pthread_mutex_lock((((philo->data)->lock_tab)[philo->fork_l]));
	if (check_fork(philo, philo->fork_l, -1) == 0)
		return ;
	gettimeofday(&time, NULL);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock((((philo->data)->lock_tab)[philo->fork_r]));
	if (check_fork(philo, philo->fork_l, philo->fork_r) == 0)
		return ;
	print_message(philo, "has taken a fork");
	print_message(philo, "is eating");
	gettimeofday(&time, NULL);
	pthread_mutex_lock((philo->data->lock_time));
	philo->last_meal = time;
	pthread_mutex_unlock((philo->data->lock_time));
	if (meal_time(philo) == 0)
		return ;
	meal_count(philo);
	pthread_mutex_unlock((((philo->data)->lock_tab)[philo->fork_r]));
	pthread_mutex_unlock((((philo->data)->lock_tab)[philo->fork_l]));
}
