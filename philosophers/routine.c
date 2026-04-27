/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <rzaatreh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 13:29:52 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/04/27 14:32:40 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nb_philo == 1)
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_state(philo, "has taken a fork");
		smart_sleep(philo->data->time_to_die, philo->data);
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!is_simulation_stopped(philo->data))
	{
		if (!take_forks(philo))
			break ;
		eat(philo);
		put_forks(philo);
		sleep_philo(philo);
		think(philo);
	}
	return (NULL);
}
