/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:44:37 by alex              #+#    #+#             */
/*   Updated: 2025/06/03 00:14:54 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void    *philo_behavior(void *arg)
{
    struct timeval time;

    (void)arg;
    gettimeofday(&time, NULL);
    printf("time in ms is : %ld", (time.tv_sec));
    printf("%ld\n", (time.tv_usec)/1000);
    return (NULL);
}
void philo(t_data *data)
{
    pthread_t thread;

    (void)data;
    pthread_create(&thread, NULL, function, "lala");
    pthread_join(thread, NULL);
    // sleep(2);
    // pthread_detach(thread);
    return ;
}