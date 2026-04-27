/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <rzaatreh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 13:28:08 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/04/27 14:30:46 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_forks_even(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->forks[philo->right_fork]);
	print_state(philo, "has taken a fork");
	if (is_simulation_stopped(data))
	{
		pthread_mutex_unlock(&data->forks[philo->right_fork]);
		return (0);
	}
	pthread_mutex_lock(&data->forks[philo->left_fork]);
	print_state(philo, "has taken a fork");
	return (1);
}

static int	take_forks_odd(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->forks[philo->left_fork]);
	print_state(philo, "has taken a fork");
	if (is_simulation_stopped(data))
	{
		pthread_mutex_unlock(&data->forks[philo->left_fork]);
		return (0);
	}
	pthread_mutex_lock(&data->forks[philo->right_fork]);
	print_state(philo, "has taken a fork");
	return (1);
}

int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
		return (take_forks_even(philo));
	return (take_forks_odd(philo));
}

void	put_forks(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_unlock(&data->forks[philo->right_fork]);
	pthread_mutex_unlock(&data->forks[philo->left_fork]);
}
