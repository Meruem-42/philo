/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:57:06 by aherlaud          #+#    #+#             */
/*   Updated: 2025/07/22 17:35:54 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meal;
	int				is_dead;
	int				forced_exit;
	int				is_full;
	struct timeval	initial_time;
	pthread_mutex_t	**lock_tab;
	pthread_mutex_t	*lock_dead;
	pthread_mutex_t	*lock_time;
	pthread_mutex_t	*lock_write;
	pthread_mutex_t	*lock_eat;
}					t_data;

typedef struct s_philo
{
	t_data			*data;
	int				index;
	struct timeval	last_meal;
	int				nb_eat;
	int				fork_l;
	int				fork_r;
}					t_philo;

void				philo(t_data *data);

int					ft_atoi(const char *str);

time_t				time_diff(struct timeval start, struct timeval end);

time_t				tv_to_ms(struct timeval time);

void				free_data(t_data *data);

time_t				time_diff(struct timeval start, struct timeval end);

void				print_message(t_philo *philo, char *str);

int					begin_thread(t_philo *philo);

int					monitor_thread(t_philo *philo);

void				eat_routine(t_philo *philo);

int					check_int_range(const char *str);

#endif