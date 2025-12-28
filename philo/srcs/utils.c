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

static char	*get_color(char *msg)
{
	if (msg[0] == 'd')
		return (RED);
	if (msg[0] == 'i' && msg[3] == 't')
		return (GREEN);
	if (msg[0] == 'i' && msg[3] == 'e')
		return (YELLOW);
	if (msg[0] == 'i' && msg[3] == 's')
		return (BLUE);
	if (msg[0] == 'h')
		return (MAGENTA);
	return (RESET);
}

void	print_msg(t_philo *philo, char *msg)
{
	long	timestamp;
	char	*color;

	color = get_color(msg);
	pthread_mutex_lock(&philo->data->print_lock);
	if (!is_stopped(philo->data))
	{
		timestamp = (get_time_us() - philo->data->start_time) / 1000;
		printf("%s%ld %d %s%s\n", color, timestamp, philo->index + 1,
			msg, RESET);
	}
	pthread_mutex_unlock(&philo->data->print_lock);
}
