/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <rzaatreh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 13:29:17 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/04/27 14:34:50 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	all_philos_ate_enough(t_philo *philos, t_data *data)
{
	int	i;

	if (data->nb_meals_required == -1)
		return (0);
	pthread_mutex_lock(&data->meal_mutex);
	i = 0;
	while (i < data->nb_philo)
	{
		if (philos[i].meals_eaten < data->nb_meals_required)
		{
			pthread_mutex_unlock(&data->meal_mutex);
			return (0);
		}
		i++;
	}
	pthread_mutex_unlock(&data->meal_mutex);
	return (1);
}

static int	check_meals(t_philo *philos, t_data *data)
{
	if (all_philos_ate_enough(philos, data))
	{
		stop_simulation(data);
		return (1);
	}
	return (0);
}

static void	print_death(t_philo *philos, t_data *data, int i)
{
	pthread_mutex_lock(&data->stop_mutex);
	if (!data->simulation_stopped)
	{
		data->simulation_stopped = 1;
		pthread_mutex_unlock(&data->stop_mutex);
		pthread_mutex_lock(&data->print_mutex);
		printf("%ld %d died\n",
			get_time_ms() - data->start_time,
			philos[i].id);
		pthread_mutex_unlock(&data->print_mutex);
		return ;
	}
	pthread_mutex_unlock(&data->stop_mutex);
}

static int	check_death(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&data->meal_mutex);
		if (get_time_ms() - philos[i].last_meal_time >= data->time_to_die)
		{
			pthread_mutex_unlock(&data->meal_mutex);
			print_death(philos, data, i);
			return (1);
		}
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philos;
	t_data	*data;

	philos = (t_philo *)arg;
	data = philos[0].data;
	while (!is_simulation_stopped(data))
	{
		if (check_meals(philos, data))
			return (NULL);
		if (check_death(philos, data))
			return (NULL);
		usleep(100);
	}
	return (NULL);
}
