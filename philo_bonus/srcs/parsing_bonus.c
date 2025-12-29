#include "philo_bonus.h"

int	check_int(int sign, int *n)
{
	if (!sign && *n == INT_MIN)
		return (2);
	if (*n < 0 && *n != INT_MIN)
		return (2);
	return (0);
}

int	ft_atoi(const char *str, int *n)
{
	int	sign;

	sign = 0;
	*n = 0;
	if (*str == '-')
		sign = 1;
	if (*str == '-' || *str == '+')
		str++;
	if (*str < '0' && *str > '9')
		return (-1);
	while (*str >= '0' && *str <= '9')
	{
		*n *= 10;
		*n += *str - '0';
		if (check_int(sign, n))
			return (2);
		str++;
	}
	if (sign)
		*n *= -1;
	if (*str == '\0')
		return (0);
	return (1);
}

int	check_ll(int sign, t_msec *n)
{
	if (!sign && *n == LLONG_MIN)
		return (2);
	if (*n < 0 && *n != LLONG_MIN)
		return (2);
	return (0);
}

int	ft_atoll(const char *str, t_msec *n)
{
	int	sign;

	sign = 0;
	*n = 0;
	if (*str == '+')
		str++;
	if (*str < '0' && *str > '9')
		return (-1);
	while (*str >= '0' && *str <= '9')
	{
		*n *= 10;
		*n += *str - '0';
		if (check_ll(sign, n))
			return (2);
		str++;
	}
	if (*str == '\0')
		return (0);
	return (1);
}

int	parse_args(int argc, char **argv, t_params *params)
{
	params->must_eat_count = -1;
	if (argc != 6 && argc != 5)
		return (1);
	if (ft_atoi(argv[1], &params->num_philos))
		return (1);
	if (ft_atoll(argv[2], &params->time_to_die))
		return (1);
	if (ft_atoll(argv[3], &params->time_to_eat))
		return (1);
	if (ft_atoll(argv[4], &params->time_to_sleep))
		return (1);
	if (argc == 6)
	{
		if (ft_atoi(argv[5], &params->must_eat_count))
			return (1);
	}
	if (params->num_philos == 0 || params->must_eat_count == 0)
		return (1);
	return (0);
}
