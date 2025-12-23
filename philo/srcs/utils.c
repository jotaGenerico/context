#include "philo.h"

void	print_status(t_philo *philo, char *status)
{
	long	timestamp;
	char	*color;

	if (!ft_strncmp(status, "died", 4))
		color = RED;
	else if (!ft_strncmp(status, "is thinking", 11))
		color = GREEN;
	else if (!ft_strncmp(status, "is eating", 9))
		color = YELLOW;
	else if (!ft_strncmp(status, "is sleeping", 11))
		color = BLUE;
	else if (!ft_strncmp(status, "has taken a fork", 16))
		color = MAGENTA;
	else
		color = RESET;
	pthread_mutex_lock(&philo->data->write_lock);
	if (!is_simulation_stopped(philo->data))
	{
		timestamp = get_time() - philo->data->start_time;
		printf("%s%ld %d %s%s\n", color, timestamp, philo->id, status, RESET);
	}
	pthread_mutex_unlock(&philo->data->write_lock);
}

bool	is_simulation_stopped(t_data *data)
{
	bool	stopped;

	pthread_mutex_lock(&data->death_lock);
	stopped = data->simulation_stop;
	pthread_mutex_unlock(&data->death_lock);
	return (stopped);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

void	error_exit(char *msg)
{
	printf("%sError: %s%s\n", RED, msg, RESET);
}
