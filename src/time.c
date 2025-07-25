/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:46:31 by aherlaud          #+#    #+#             */
/*   Updated: 2025/07/25 18:26:56 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

time_t	tv_to_ms(struct timeval time)
{
	time_t	time_full;

	time_full = time.tv_sec;
	time_full = time_full * 1000;
	time_full = time_full + (time.tv_usec / 1000);
	return (time_full);
}

time_t	time_diff(struct timeval start, struct timeval end)
{
	time_t	start_full;
	time_t	end_full;

	start_full = tv_to_ms(start);
	end_full = tv_to_ms(end);
	return (end_full - start_full);
}
