#include "philo.h"
//high level concers
void	eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;

	pthread_mutex_lock(&data->meal_mutex);
	philo->last_meal_time = get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&data->meal_mutex);

	print_state(philo, "is eating");

	smart_sleep(data->time_to_eat, data);
}

void    sleep_philo(t_philo *philo)
{
    print_state(philo, "is sleeping");
    smart_sleep(philo->data->time_to_sleep, philo->data);
}

void    think(t_philo *philo)
{
    print_state(philo, "is thinking");
}
