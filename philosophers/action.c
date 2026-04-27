/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <rzaatreh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 13:27:53 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/04/27 14:29:55 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	print_state(philo, "is eating");
	pthread_mutex_lock(&data->meal_mutex);
	philo->last_meal_time = get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&data->meal_mutex);
	smart_sleep(data->time_to_eat, data);
}

void	sleep_philo(t_philo *philo)
{
	print_state(philo, "is sleeping");
	smart_sleep(philo->data->time_to_sleep, philo->data);
}

void	think(t_philo *philo)
{
	print_state(philo, "is thinking");
}
