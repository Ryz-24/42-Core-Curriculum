#include "philo.h"

void    *philo_routine(void *arg)
{
    t_philo    *philo;

    philo = (t_philo *)arg;

    /* Special case: only 1 philosopher */
    if (philo->data->nb_philo == 1)
    {
        pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
        print_state(philo, "has taken a fork");
        smart_sleep(philo->data->time_to_die, philo->data);
        pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
        return (NULL);
    }

    /* Small stagger to reduce fork contention */
    if (philo->id % 2 == 0)
        usleep(1000);
    while (!is_simulation_stopped(philo->data))
    {
        take_forks(philo);
        eat(philo);
        put_forks(philo);
        sleep_philo(philo);
        think(philo);
    }
    return (NULL);
}
