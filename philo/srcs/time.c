#include "../includes/philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long	get_elapsed_time(long start_time)
{
	return (get_time() - start_time);
}

void	precise_usleep(long milliseconds, t_data *data)
{
	long	start;
	long	elapsed;

	start = get_time();
	while (1)
	{
		elapsed = get_time() - start;
		if (elapsed >= milliseconds)
			break ;
		if (is_simulation_stopped(data))
			break ;
		usleep(100);
	}
}
