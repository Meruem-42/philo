/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:12:46 by alex              #+#    #+#             */
/*   Updated: 2025/07/05 21:30:45 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_lock(pthread_mutex_t *lock, t_data *data)
{
	// (void)data;
	if (lock)
	{
		if (lock == data->lock_dead || lock == data->lock_eat)
			pthread_mutex_unlock(lock);
		pthread_mutex_destroy(lock);
		free(lock);
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
			free_lock(data->lock_tab[i], data);
			i++;
		}
		free(data->lock_tab);
	}
	free_lock(data->lock_time, data);
	pthread_mutex_lock((data->lock_dead));
	free_lock(data->lock_dead, data);
	free_lock(data->lock_write, data);
	pthread_mutex_lock((data->lock_eat));
	free_lock(data->lock_eat, data);
}
