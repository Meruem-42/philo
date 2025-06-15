/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:45:50 by aherlaud          #+#    #+#             */
/*   Updated: 2025/06/15 18:46:09 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_message(t_philo *philo, char *str)
{
	struct timeval time;

	pthread_mutex_lock((philo->data->lock_write));
	gettimeofday(&time, NULL);
	printf("%ld %d %s\n", time_diff((philo->data)->initial_time, time),
		philo->index + 1, str);
	pthread_mutex_unlock((philo->data->lock_write));
}