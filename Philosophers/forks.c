#include "philo.h"

void    take_forks(t_philo *philo)
{
    t_data  *data;

    data = philo->data;

    if (philo->id % 2 == 0)
    {
        /* Even philosophers take right fork first */
        pthread_mutex_lock(&data->forks[philo->right_fork]);
        print_state(philo, "has taken a fork");
        pthread_mutex_lock(&data->forks[philo->left_fork]);
        print_state(philo, "has taken a fork");
    }
    else
    {
        /* Odd philosophers take left fork first */
        pthread_mutex_lock(&data->forks[philo->left_fork]);
        print_state(philo, "has taken a fork");
        pthread_mutex_lock(&data->forks[philo->right_fork]);
        print_state(philo, "has taken a fork");
    }
}

void    put_forks(t_philo *philo)
{
    t_data  *data;

    data = philo->data;

    pthread_mutex_unlock(&data->forks[philo->left_fork]);
    pthread_mutex_unlock(&data->forks[philo->right_fork]);
}
