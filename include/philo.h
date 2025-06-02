/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:45:35 by alex              #+#    #+#             */
/*   Updated: 2025/06/03 00:06:12 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct s_philo
{
    pthread_t *thread;
    int     fork;
    int     index;
    struct s_philo *next;
}               t_philo;

typedef struct s_data
{
    t_philo *philo_lst;
    int nb_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int nb_meal;
    int is_dead;
}               t_data;

// struct timeval {
//     time_t      tv_sec;   // seconds since Jan 1, 1970 (epoch)
//     suseconds_t tv_usec;  // microseconds (0 to 999999)
// };


void philo(t_data *data);

void	create_lst_philo(t_data *data);

int	ft_atoi(const char *str);

#endif