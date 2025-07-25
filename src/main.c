/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 23:44:03 by alex              #+#    #+#             */
/*   Updated: 2025/06/16 18:03:38 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	fill_tab_lock(pthread_mutex_t **lock_tab, int index)
{
	pthread_mutex_t	*lock;

	lock = malloc(sizeof(pthread_mutex_t));
	if (!lock)
		return (0);
	if (pthread_mutex_init(lock, NULL) != 0)
		return (free(lock), lock = NULL, lock_tab[index] = lock, 0);
	lock_tab[index] = lock;
	return (1);
}

pthread_mutex_t	*create_lock(void)
{
	pthread_mutex_t	*lock;

	lock = malloc(sizeof(pthread_mutex_t));
	if (!lock)
		return (NULL);
	if (pthread_mutex_init(lock, NULL) != 0)
		return (free(lock), NULL);
	return (lock);
}

pthread_mutex_t	**create_lock_tab(t_data *data)
{
	pthread_mutex_t	**lock_tab;
	int				i;

	lock_tab = malloc(data->nb_philo * sizeof(pthread_mutex_t *));
	if (!lock_tab)
		return (NULL);
	i = 0;
	while (i < data->nb_philo)
	{
		if (fill_tab_lock(lock_tab, i++) == 0)
		{
			i = 0;
			while (lock_tab[i])
			{
				pthread_mutex_destroy(data->lock_tab[i]);
				free(data->lock_tab[i]);
				i++;
			}
			return (free(lock_tab), NULL);
		}
	}
	return (lock_tab);
}

int	data_init(t_data *data, char **av)
{
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->nb_meal = ft_atoi(av[5]);
	else
		data->nb_meal = -1;
	data->is_dead = 0;
	data->is_full = 0;
	data->lock_tab = create_lock_tab(data);
	data->lock_dead = create_lock();
	data->lock_time = create_lock();
	data->lock_write = create_lock();
	data->lock_eat = create_lock();
	if (!data->lock_tab || !data->lock_dead || !data->lock_time
		|| !data->lock_write || !data->lock_eat)
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5)
		return (printf("not enough args\n"), 0);
	if (!check_int_range(av[1]) || !check_int_range(av[2])
		|| !check_int_range(av[3]) || !check_int_range(av[4])
		|| (av[5] && !check_int_range(av[5])))
		return (printf("only int min or int max range\n"));
	if (ft_atoi(av[1]) < 1)
		return (printf("not enough philosophers\n"), 0);
	if (ft_atoi(av[2]) < 0 || ft_atoi(av[3]) < 0 || ft_atoi(av[4]) < 0)
		return (printf("latence can't be negative\n"), 0);
	if (av[5] && ft_atoi(av[5]) < 1)
		return (printf("number of meal can't be null or negative\n"), 0);
	if (data_init(&data, av) == 0)
		return (free_data(&data), 0);
	philo(&data);
	return (free_data(&data), 1);
}
