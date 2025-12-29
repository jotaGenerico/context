#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5 && argc != 6)
	{
		error_exit("Usage: ./philo nb_philos time_die time_eat "
			"time_sleep [must_eat]");
		return (1);
	}
	if (parse_args(argc, argv, &table.data) != 0)
		return (1);
	if (init_table(&table) != 0)
		return (1);
	start_simulation(&table);
	cleanup(&table);
	return (0);
}
