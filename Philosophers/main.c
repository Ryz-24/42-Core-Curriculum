#include "philo.h"

static int	print_error(void)
{
	printf("Error\n");
	return (1);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philos;
	pthread_t	monitor;

	if (!init_data(&data, argc, argv))
		return (print_error());
	if (!init_mutexes(&data))
	{
		free(data.forks);
		return (print_error());
	}
	data.start_time = get_time_ms();
	if (!init_philos(&philos, &data))
	{
		free(data.forks);
		return (print_error());
	}
	/*
	// Initialize last_meal_time AFTER start_time is set
	for (int i = 0; i < data.nb_philo; i++)
		philos[i].last_meal_time = data.start_time;
	*/
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

