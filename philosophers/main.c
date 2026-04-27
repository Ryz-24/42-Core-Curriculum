/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <rzaatreh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 13:28:51 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/04/27 14:30:07 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	print_error(void)
{
	printf("Error\n");
	return (1);
}

static int	init_all(t_data *data, t_philo **philos, int ac, char **av)
{
	if (!init_data(data, ac, av))
		return (0);
	if (!init_mutexes(data))
	{
		free(data->forks);
		return (0);
	}
	data->start_time = get_time_ms();
	if (!init_philos(philos, data))
	{
		free(data->forks);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philos;
	pthread_t	monitor;

	if (!init_all(&data, &philos, argc, argv))
		return (print_error());
	if (!create_philos_threads(&data, philos))
	{
		cleanup(&data, philos);
		return (print_error());
	}
	if (!create_monitor_thread(&data, philos, &monitor))
	{
		cleanup(&data, philos);
		return (print_error());
	}
	join_threads(&data, philos, monitor);
	cleanup(&data, philos);
	return (0);
}
