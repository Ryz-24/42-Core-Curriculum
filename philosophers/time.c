/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <rzaatreh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 13:29:59 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/04/27 14:34:21 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	smart_sleep(long time, t_data *data)
{
	long	start;

	start = get_time_ms();
	while (!is_simulation_stopped(data))
	{
		if (get_time_ms() - start >= time)
			break ;
		usleep(500);
	}
}
