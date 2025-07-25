/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:12:46 by alex              #+#    #+#             */
/*   Updated: 2025/07/25 18:23:46 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_lock(pthread_mutex_t *lock)
{
	if (lock)
	{
		pthread_mutex_unlock(lock);
		pthread_mutex_destroy(lock);
		free(lock);
	}
}

void	free_spare_mutex(t_data *data)
{
	if (data->lock_time)
	{
		pthread_mutex_lock((data->lock_time));
		free_lock(data->lock_time);
	}
	if (data->lock_dead)
	{
		pthread_mutex_lock((data->lock_dead));
		free_lock(data->lock_dead);
	}
	if (data->lock_write)
	{
		pthread_mutex_lock((data->lock_write));
		free_lock(data->lock_write);
	}
	if (data->lock_eat)
	{
		pthread_mutex_lock((data->lock_eat));
		free_lock(data->lock_eat);
	}
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	if (data->lock_tab)
	{
		while (i < data->nb_philo)
		{
			if (data->lock_tab[i])
			{
				pthread_mutex_lock((data->lock_tab[i]));
				free_lock(data->lock_tab[i]);
			}
			i++;
		}
		free(data->lock_tab);
	}
	free_spare_mutex(data);
}
