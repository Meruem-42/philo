/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 23:44:03 by alex              #+#    #+#             */
/*   Updated: 2025/06/03 00:13:27 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void data_init(t_data *data, char **av)
{
    data->philo_lst = NULL;
    data->nb_philo = ft_atoi(av[1]);
    data->time_to_die = ft_atoi(av[2]);
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep = ft_atoi(av[4]);
    if(av[5])
        data->nb_meal = ft_atoi(av[5]);
    else
        data->nb_meal = -1;
    data->is_dead = 0;
}

int main(int ac, char **av)
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
    create_lst_philo(&data);
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