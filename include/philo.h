/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:45:35 by alex              #+#    #+#             */
/*   Updated: 2025/06/12 17:46:40 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <pthread.h>
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
	int				is_full;
	struct timeval	initial_time;
	pthread_mutex_t	*lock_tab;
	pthread_mutex_t	lock_dead;
}					t_data;

typedef struct s_philo
{
	t_data			*data;
	int				index;
	struct timeval	last_meal;
	int				nb_eat;
}					t_philo;

void				philo(t_data *data);

int					ft_atoi(const char *str);

time_t				time_diff(struct timeval start, struct timeval end);

time_t				tv_to_ms(struct timeval time);

#endif