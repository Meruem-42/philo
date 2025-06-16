/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:44:37 by alex              #+#    #+#             */
/*   Updated: 2025/06/16 17:28:24 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	fill_tab(t_philo *philo_tab, t_data *data, int index)
{
	t_philo	philo;

	philo.data = data;
	philo.index = index;
	philo.nb_eat = 0;
	philo_tab[index] = philo;
}

void	solo_philo_error(t_data *data)
{
	struct timeval	time;

	printf("%ld %d has taken a fork\n", time_diff(data->initial_time,
			data->initial_time), 1);
	usleep(data->time_to_die * 1000);
	gettimeofday(&time, NULL);
	printf("%ld %d is dead\n", time_diff(data->initial_time, time), 1);
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
		return (solo_philo_error(data), free(philo_tab));
	while (i < data->nb_philo)
	{
		if (begin_thread(&(philo_tab[i++])) == 0)
			return (free(philo_tab));
	}
	monitor_thread(philo_tab);
	return (free(philo_tab));
}
