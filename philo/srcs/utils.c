#include "philo.h"

void	error_exit(char *msg)
{
	printf("Error: %s\n", msg);
}

bool	is_stopped(t_data *data)
{
	bool	stopped;

	pthread_mutex_lock(&data->stop_lock);
	stopped = data->stop;
	pthread_mutex_unlock(&data->stop_lock);
	return (stopped);
}

void	print_msg(t_philo *philo, char *msg)
{
	long	timestamp;

	pthread_mutex_lock(&philo->data->print_lock);
	if (!is_stopped(philo->data))
	{
		timestamp = (get_time_us() - philo->data->start_time) / 1000;
		printf("%ld %d %s\n", timestamp, philo->index + 1, msg);
	}
	pthread_mutex_unlock(&philo->data->print_lock);
}
