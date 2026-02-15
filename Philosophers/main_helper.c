#include "philo.h"

static void destroy_mutexes(t_data *data)
{
    int i;

    i = 0;
    while (i < data->nb_philo)
    {
        pthread_mutex_destroy(&data->forks[i]);
        i++;
    }
    pthread_mutex_destroy(&data->print_mutex);
    pthread_mutex_destroy(&data->stop_mutex);
    pthread_mutex_destroy(&data->meal_mutex);
}

void	cleanup(t_data *data, t_philo *philos)
{
	destroy_mutexes(data);
	free(data->forks);
	free(philos);
}

int	create_philos_threads(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&philos[i].thread, NULL,
				philo_routine, &philos[i]) != 0)
		{
			stop_simulation(data);
			while (--i >= 0)
				pthread_join(philos[i].thread, NULL);
			return (0);
		}
		i++;
	}
	return (1);
}

int	create_monitor_thread(t_data *data, t_philo *philos, pthread_t *monitor)
{
	int	i;

	if (pthread_create(monitor, NULL,
			monitor_routine, philos) != 0)
	{
		stop_simulation(data);
		i = 0;
		while (i < data->nb_philo)
		{
			pthread_join(philos[i].thread, NULL);
			i++;
		}
		//cleanup(data, philos);
		return (0);
	}
	return (1);
}

void	join_threads(t_data *data, t_philo *philos, pthread_t monitor)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
}
