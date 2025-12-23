#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac != 5 && ac != 6)
	{
		error_exit("Usage: ./philo nb_philos time_die time_eat "
			"time_sleep [must_eat]");
		return (1);
	}
	if (parse_args(ac, av, &table.data) != 0)
		return (1);
	if (init_table(&table) != 0)
		return (1);
	start_simulation(&table);
	cleanup(&table);
	return (0);
}
