#include "philo_bonus.h"

static int	is_valid_number(char *str);

int	ft_atoi(const char *str)
{
	int	result;

	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result);
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

int	parse_args_bonus(int ac, char **av, t_data *data)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!is_valid_number(av[i]))
			return (error_exit("Invalid argument"), 1);
		i++;
	}
	data->nb_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]) * 1000;
	data->time_to_eat = ft_atoi(av[3]) * 1000;
	data->time_to_sleep = ft_atoi(av[4]) * 1000;
	if (ac == 6)
		data->must_eat_count = ft_atoi(av[5]);
	else
		data->must_eat_count = -1;
	data->start_time = 0;
	data->pids = NULL;
	if (data->nb_philos < 1 || data->nb_philos > 200)
		return (error_exit("Invalid number of philosophers"), 1);
	if (data->time_to_die < 60000 || data->time_to_eat < 60000
		|| data->time_to_sleep < 60000)
		return (error_exit("Time values must be >= 60ms"), 1);
	return (0);
}

static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
