/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:12:46 by alex              #+#    #+#             */
/*   Updated: 2025/06/15 00:37:31 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void free_data(t_data *data)
{
    int i;
    i = 0;

    // printf("\t\t\t\t%d\n", data->time_to_eat);
    while(i < data->nb_philo)
    {
        pthread_mutex_destroy(data->lock_tab[i]);
        free(data->lock_tab[i]);
        i++;
    }
    free(data->lock_tab);
    pthread_mutex_destroy(data->lock_time);
    free(data->lock_time);
    pthread_mutex_destroy(data->lock_dead);
    free(data->lock_dead);
    pthread_mutex_destroy(data->lock_write);
    free(data->lock_write);
}   