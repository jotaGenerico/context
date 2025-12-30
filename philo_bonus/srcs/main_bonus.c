#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_params	params;
	t_state		state;

	if (parse_args(argc, argv, &params))
	{
		print_usage();
		return (0);
	}
	params.start_time = get_time_ms();
	init_resources(&state, &params);
	if (params.num_philos == 1)
	{
		printf("%s%lld %d %s%s\n", MAGENTA, (long long)0, 1,
			"has taken a fork", RESET);
		wait_until(params.start_time + params.time_to_die);
		printf("%s%lld %d died%s\n", RED,
			get_time_ms() - params.start_time, 1, RESET);
		return (0);
	}
	create_processes(&state, &params);
	sem_unlink("/forks");
	sem_unlink("/pr");
	sem_unlink("/dead");
	sem_unlink("/finished");
	return (0);
}

void	print_usage(void)
{
	printf("Invalid Argument\nUsage: program_name number_of_philosophers "
		"time_to_die time_to_eat time_to_sleep"
		" [number_of_times_each_philosopher_must_eat]\n");
}
