/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 23:44:03 by alex              #+#    #+#             */
/*   Updated: 2025/06/10 18:03:39 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	*create_fork_tab(int nb_philo)
{
	int	*philo_tab;
	int	i;

	i = 0;
	philo_tab = malloc(nb_philo * sizeof(int));
	if (!philo_tab)
		return (0);
	while (i < nb_philo)
		philo_tab[i++] = 1;
	return (philo_tab);
}

void	fill_tab_lock(pthread_mutex_t *lock_tab, int index)
{
	pthread_mutex_t	lock;

	pthread_mutex_init(&lock, NULL);
	lock_tab[index] = lock;
}

pthread_mutex_t	*create_lock_tab(t_data *data)
{
	pthread_mutex_t	*lock_tab;
	int				i;

	lock_tab = malloc(data->nb_philo * sizeof(pthread_mutex_t));
	if (!lock_tab)
		return (NULL);
	i = 0;
	while (i < data->nb_philo)
		fill_tab_lock(lock_tab, i++);
	return (lock_tab);
}

void	data_init(t_data *data, char **av)
{
	// int i;
	// i = 0;
	data->nb_philo = ft_atoi(av[1]);
	data->fork_tab = create_fork_tab(ft_atoi(av[1]));
	// while(i < data->nb_philo)
	//     fill_tab(data->thread_tab, i++);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->nb_meal = ft_atoi(av[5]);
	else
		data->nb_meal = -1;
	data->is_dead = 0;
	data->is_full = 0;
	// pthread_mutex_init(&lock, NULL);
	data->lock_tab = create_lock_tab(data);
}

int	main(int ac, char **av)
{
	t_data data;

	(void)ac;
	// if(ac < 5)
	//     return (printf("not enough arguments\n"));
	// if(ft_atoi(av[1]) < 1)
	//     return (printf("not enough philosophers\n"));
	// if(ft_atoi(av[2]) < 0 || ft_atoi(av[3]) < 0 || ft_atoi(av[4]) < 0)
	//     return (printf("latence can't be negative\n"));
	// if(av[3] && ft_atoi(av[3]) < 0)
	//     return (printf("Can't be negative\n"));

	data_init(&data, av);
	// ==============================================
	// ================== CREATE LST ================
	// ==============================================
	// create_lst_philo(&data);
	// t_philo *tmp;
	// tmp = data.philo_lst;
	// while(tmp)
	// {
	//     printf("fork of tmp num %d is : %d\n", tmp->index, tmp->fork);
	//     tmp = tmp->next;
	// }
	philo(&data);
	return (1);
}