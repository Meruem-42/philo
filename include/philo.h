/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:45:35 by alex              #+#    #+#             */
/*   Updated: 2025/06/10 22:59:51 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

// typedef struct s_philo
// {
//     pthread_t *thread;
//     int     fork;
//     int     index;
//     struct s_philo *next;
// }               t_philo;

typedef struct s_data
{
	int				*fork_tab;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meal;
	int				is_dead;
	int				is_full;
	struct timeval		initial_time;
	pthread_mutex_t	*lock_tab;
}					t_data;

typedef struct s_philo
{
	t_data			*data;
	int				index;
	struct timeval			last_meal;
	int				nb_eat;
}					t_philo;

// struct timeval {
//     time_t      tv_sec;   // seconds since Jan 1, 1970 (epoch)
//     suseconds_t tv_usec;  // microseconds (0 to 999999)
// };

void				philo(t_data *data);

// void	create_lst_philo(t_data *data);

// t_philo	*ft_lstlast_philo(t_philo *lst);

int					ft_atoi(const char *str);

time_t				tv_to_ms(struct timeval time);

#endif