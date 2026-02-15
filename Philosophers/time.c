#include "philo.h"

/* We convert everything to milliseconds */
long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

/* used everytime we print to print time */
long	elapsed_time(long start)
{
	return (get_time_ms() - start);
}

/* sleeping in chunks */
void	smart_sleep(long time, t_data *data)
{
	long	start;

	start = get_time_ms();
	while (!is_simulation_stopped(data))
	{
		if (elapsed_time(start) >= time)
        	break;
		if (get_time_ms() - start >= time)
			break ;
		usleep(500);
	}
}

