#include "philo.h"

static void	join_threads(t_table *table);
static int	create_threads(t_table *table);

void	start_simulation(t_table *table)
{
	table->data.start_time = get_time();
	if (table->data.nb_philos == 1)
	{
		printf("0 1 has taken a fork\n");
		usleep(table->data.time_to_die * 1000);
		printf("%d 1 died\n", table->data.time_to_die);
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
		i++;
	}
	pthread_mutex_destroy(&table->data.write_lock);
	pthread_mutex_destroy(&table->data.death_lock);
	pthread_mutex_destroy(&table->data.meal_check);
	free(table->philos);
	free(table->forks);
}

static int	create_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->data.nb_philos)
	{
		pthread_mutex_lock(&table->data.meal_check);
		table->philos[i].last_meal_time = table->data.start_time;
		pthread_mutex_unlock(&table->data.meal_check);
		i++;
	}
	i = 0;
	while (i < table->data.nb_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL,
				philosopher_routine, &table->philos[i]) != 0)
			return (error_exit("Failed to create philosopher thread"), 1);
		i++;
	}
	if (pthread_create(&table->monitor_thread, NULL,
			monitor_routine, table) != 0)
		return (error_exit("Failed to create monitor thread"), 1);
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
	pthread_join(table->monitor_thread, NULL);
}
