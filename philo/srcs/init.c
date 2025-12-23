#include "../includes/philo.h"

static void	assign_forks(t_philo *philo, pthread_mutex_t *forks, int i, int nb)
{
	if (philo->id % 2 == 0)
	{
		philo->left_fork = &forks[i];
		philo->right_fork = &forks[(i + 1) % nb];
	}
	else
	{
		philo->left_fork = &forks[(i + 1) % nb];
		philo->right_fork = &forks[i];
	}
}

void	init_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->data.nb_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals_eaten = 0;
		table->philos[i].last_meal_time = 0;
		table->philos[i].data = &table->data;
		assign_forks(&table->philos[i], table->forks, i, table->data.nb_philos);
		i++;
	}
}

static int	init_mutexes(t_table *table)
{
	int	i;

	if (pthread_mutex_init(&table->data.write_lock, NULL) != 0)
		return (error_exit("Failed to initialize write_lock"), 1);
	if (pthread_mutex_init(&table->data.death_lock, NULL) != 0)
		return (error_exit("Failed to initialize death_lock"), 1);
	if (pthread_mutex_init(&table->data.meal_check, NULL) != 0)
		return (error_exit("Failed to initialize meal_check"), 1);
	i = 0;
	while (i < table->data.nb_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (error_exit("Failed to initialize fork mutex"), 1);
		i++;
	}
	return (0);
}

int	init_table(t_table *table)
{
	table->philos = malloc(sizeof(t_philo) * table->data.nb_philos);
	if (!table->philos)
		return (error_exit("Failed to allocate memory for philosophers"), 1);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->data.nb_philos);
	if (!table->forks)
	{
		free(table->philos);
		return (error_exit("Failed to allocate memory for forks"), 1);
	}
	if (init_mutexes(table) != 0)
	{
		free(table->philos);
		free(table->forks);
		return (1);
	}
	init_philos(table);
	return (0);
}
