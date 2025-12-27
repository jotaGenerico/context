#include "philo_bonus.h"

long	get_time_us(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}

void	sleep_ms(long ms)
{
	long	start;
	long	target;

	start = get_time_us();
	target = ms * 1000;
	while (get_time_us() - start < target)
		usleep(1000);
}
