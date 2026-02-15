#include "philo.h"

static int check_args(int argc, char **argv)
{
    int i;
    int j;

    if (argc != 5 && argc != 6)
        return (0);
    i = 1;
    while (i < argc)
    {
        j = 0;
        if (argv[i][0] == '\0')
            return (0);
        while (argv[i][j])
        {
            if (argv[i][j] < '0' || argv[i][j] > '9')
                return (0);
            j++;
        }
        if (ft_atoi(argv[i]) <= 0)
            return (0);
        i++;
    }
    return (1);
}

int	init_data(t_data *data, int argc, char **argv)
{
	if (!check_args(argc, argv))
		return (0);
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->nb_meals_required = ft_atoi(argv[5]);
	else
		data->nb_meals_required = -1;
	data->simulation_stopped = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (0);
	return (1);
}

int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			return (0);
		}
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->stop_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_mutex);
		return (0);
	}
	if (pthread_mutex_init(&data->meal_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_mutex);
		pthread_mutex_destroy(&data->stop_mutex);
		return (0);
	}
	/*
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
	{
		free(data->forks);
		return (0);
	}
	if (pthread_mutex_init(&data->stop_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_mutex);
		free(data->forks);
		return (0);
	}
	if (pthread_mutex_init(&data->meal_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_mutex);
		pthread_mutex_destroy(&data->stop_mutex);
		free(data->forks);
		return (0);
	}
	*/
	return (1);
}


int	init_philos(t_philo **philos, t_data *data)
{
	int	i;

	*philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!*philos)
		return (0);

	i = 0;
	while (i < data->nb_philo)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].left_fork = i;
		(*philos)[i].right_fork = (i + 1) % data->nb_philo;
		(*philos)[i].last_meal_time = data->start_time;
		(*philos)[i].meals_eaten = 0;
		(*philos)[i].data = data;
		i++;
	}
	return (1);
}
