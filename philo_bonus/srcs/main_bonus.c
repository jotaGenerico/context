#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
	{
		error_exit("Usage: ./philo_bonus nb_philos time_die time_eat "
			"time_sleep [must_eat]");
		return (1);
	}
	if (parse_args_bonus(ac, av, &data) != 0)
		return (1);
	if (start_simulation_bonus(&data) != 0)
		return (1);
	return (0);
}

void	error_exit(const char *msg)
{
	printf("Error: %s\n", msg);
}
