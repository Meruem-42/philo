/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:12:46 by alex              #+#    #+#             */
/*   Updated: 2025/06/16 17:56:42 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_lock(pthread_mutex_t *lock)
{
	if (lock)
	{
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
			free_lock(data->lock_tab[i]);
			i++;
		}
		free(data->lock_tab);
	}
	free_lock(data->lock_time);
	free_lock(data->lock_dead);
	free_lock(data->lock_write);
	free_lock(data->lock_eat);
}
