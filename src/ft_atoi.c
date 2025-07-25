/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:05:29 by lflayeux          #+#    #+#             */
/*   Updated: 2025/07/22 17:38:22 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_int_range(const char *str)
{
	const char	*p = str;
	int			i;
	long		acc;
	int			sign;

	acc = 0;
	sign = 1;
	i = 0;
	if (p[i] == '+' || p[i] == '-')
	{
		if (p[i] == '-')
			sign = -1;
		i++;
	}
	while (p[i])
	{
		acc = acc * 10 + (p[i] - '0');
		if (sign == 1 && acc > (long)INT_MAX)
			return (0);
		if (sign == -1 && acc > (long)INT_MAX + 1)
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	sign;

	sign = 1;
	i = 0;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
