/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:44:37 by alex              #+#    #+#             */
/*   Updated: 2025/06/02 14:12:53 by alex             ###   ########.fr       */
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
        return (write(1, "not enough arguments\n", 21));
    if(ft_atoi(av[1]) < 1)
        return (write(1, "not enough philosophers\n", 24));
    if(ft_atoi(av[2]) < 0 || ft_atoi(av[3]) < 0 || ft_atoi(av[4]) < 0)
        return (write(1, "latence can't be negative\n", 26));
    if(av[3] && ft_atoi(av[3]) < 0)
        return (write(1, "Can't be negative\n", 18));
    philo(ac, av);
}