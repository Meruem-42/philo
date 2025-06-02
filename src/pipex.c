/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:44:37 by alex              #+#    #+#             */
/*   Updated: 2025/06/02 16:35:19 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void philo(int ac, char **av)
{
    (void)ac;
    (void)av;
    
}

int main(int ac, char **av)
{
    if(ac < 5)
        return (printf("not enough arguments\n"));
    if(ft_atoi(av[1]) < 1)
        return (printf("not enough philosophers\n"));
    if(ft_atoi(av[2]) < 0 || ft_atoi(av[3]) < 0 || ft_atoi(av[4]) < 0)
        return (printf("latence can't be negative\n"));
    if(av[3] && ft_atoi(av[3]) < 0)
        return (printf("Can't be negative\n"));
    philo(ac, av);
}