#include "philo.h"

int is_simulation_stopped(t_data *data)
{
    int stopped;

    pthread_mutex_lock(&data->stop_mutex);
    stopped = data->simulation_stopped;
    pthread_mutex_unlock(&data->stop_mutex);
    return (stopped);
}

void    stop_simulation(t_data *data)
{
    pthread_mutex_lock(&data->stop_mutex);
    data->simulation_stopped = 1;
    pthread_mutex_unlock(&data->stop_mutex);
}

void    print_state(t_philo *philo, char *msg)
{
    t_data  *data;

    data = philo->data;

    pthread_mutex_lock(&data->print_mutex);

    /* Check stop flag WITHOUT calling is_simulation_stopped()
       to avoid lock inversion (print_mutex → stop_mutex) */
    pthread_mutex_lock(&data->stop_mutex);
    if (!data->simulation_stopped)
    {
        printf("%ld %d %s\n",
            get_time_ms() - data->start_time,
            philo->id,
            msg);
    }
    pthread_mutex_unlock(&data->stop_mutex);

    pthread_mutex_unlock(&data->print_mutex);
}

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	num;

	sign = 1;
	num = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		num = (num * 10) + (*nptr - '0');
		nptr++;
	}
	return (num * sign);
}
