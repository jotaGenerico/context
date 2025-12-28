#include "philo.h"

static void	join_threads(t_table *table);
static int	create_threads(t_table *table);

void	start_simulation(t_table *table)
{
	table->data.start_time = get_time_us();
	if (table->data.nb_philos == 1)
	{
		printf("0 1 has taken a fork\n");
		usleep(table->data.time_to_die);
		printf("%s%ld 1 died%s\n", RED, table->data.time_to_die / 1000, RESET);
		return ;
	}
	if (create_threads(table) != 0)
		return ;
	join_threads(table);
}

void	cleanup(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->data.nb_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->meal_locks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->data.stop_lock);
	pthread_mutex_destroy(&table->data.print_lock);
	free(table->philos);
	free(table->forks);
	free(table->meal_locks);
}

static int	create_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->data.nb_philos)
	{
		pthread_mutex_lock(&table->meal_locks[i]);
		table->philos[i].last_meal = table->data.start_time;
		pthread_mutex_unlock(&table->meal_locks[i]);
		i++;
	}
	i = 0;
	while (i < table->data.nb_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL,
				philo_routine, &table->philos[i]) != 0)
			return (error_exit("Thread creation failed"), 1);
		i++;
	}
	if (pthread_create(&table->monitor, NULL, monitor_routine, table) != 0)
		return (error_exit("Thread creation failed"), 1);
	return (0);
}

static void	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->data.nb_philos)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
	pthread_join(table->monitor, NULL);
}
