#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

/* All philosophires see */
typedef struct s_data
{
	int				nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nb_meals_required;

	long			start_time;
	int				simulation_stopped;

	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	meal_mutex;
}	t_data;

/* Only one philosopher owns */
typedef struct s_philo
{
	int				id;
	pthread_t		thread;

	int				left_fork;
	int				right_fork;

	long			last_meal_time;
	int				meals_eaten;

	t_data			*data;
}	t_philo;

int		init_data(t_data *data, int argc, char **argv);
int		init_philos(t_philo **philos, t_data *data);
int		init_mutexes(t_data *data);

void	*philo_routine(void *arg);
void	*monitor_routine(void *arg);

void	take_forks(t_philo *philo);
void	eat(t_philo *philo);
void	sleep_philo(t_philo *philo);
void	think(t_philo *philo);
void	put_forks(t_philo *philo);

long	get_time_ms(void);
long	elapsed_time(long start);
void	smart_sleep(long time, t_data *data);

void	print_state(t_philo *philo, char *msg);

int		ft_atoi(const char *str);
int		is_simulation_stopped(t_data *data);
void	stop_simulation(t_data *data);

void	cleanup(t_data *data, t_philo *philos);
int	create_philos_threads(t_data *data, t_philo *philos);
int	create_monitor_thread(t_data *data, t_philo *philos, pthread_t *monitor);
void	join_threads(t_data *data, t_philo *philos, pthread_t monitor);

#endif
