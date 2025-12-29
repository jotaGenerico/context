#include "philo_bonus.h"

t_msec	get_time_ms(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL))
		return (-1);
	return (((long long)t.tv_sec * 1000) + ((long long)t.tv_usec / 1000));
}

void	wait_until(t_msec waiting_time)
{
	t_msec	t;

	t = get_time_ms();
	while (waiting_time - t > 5)
	{
		usleep(1000 * (waiting_time - t - 5));
		t = get_time_ms();
	}
	while (waiting_time > t)
		t = get_time_ms();
}
