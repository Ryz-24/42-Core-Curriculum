#include "philo.h"

static int	all_philos_ate_enough(t_philo *philos, t_data *data)
{
	int	i;

	if (data->nb_meals_required == -1)
		return (0);
	i = 0;
	while (i < data->nb_philo)
	{
		if (philos[i].meals_eaten < data->nb_meals_required)
			return (0);
		i++;
	}
	return (1);
}

static int	check_death(t_philo *philos, t_data *data)
{
	int		i;
	long	current_time;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&data->meal_mutex);
		current_time = get_time_ms();
		if (current_time - philos[i].last_meal_time
			>= data->time_to_die)
		{
			pthread_mutex_unlock(&data->meal_mutex);
			pthread_mutex_lock(&data->print_mutex);
			stop_simulation(data);
			printf("%ld %d died\n",
				current_time - data->start_time,
				philos[i].id);
			pthread_mutex_unlock(&data->print_mutex);
			return (1);
		}
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
	}
	return (0);
}

static int	check_meals(t_philo *philos, t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->meal_mutex);
	result = all_philos_ate_enough(philos, data);
	pthread_mutex_unlock(&data->meal_mutex);
	if (result)
	{
		stop_simulation(data);
		return (1);
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
