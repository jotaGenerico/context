#include "philo.h"

static void	init_philos(t_table *table);
static int	init_mutexes(t_table *table);
static void	assign_forks(t_philo *philo, pthread_mutex_t *forks, int i, int n);

int	init_table(t_table *table)
{
	table->philos = malloc(sizeof(t_philo) * table->data.nb_philos);
	if (!table->philos)
		return (error_exit("Malloc failed"), 1);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->data.nb_philos);
	if (!table->forks)
		return (free(table->philos), error_exit("Malloc failed"), 1);
	table->meal_locks = malloc(sizeof(pthread_mutex_t)
			* table->data.nb_philos);
	if (!table->meal_locks)
		return (free(table->philos), free(table->forks),
			error_exit("Malloc failed"), 1);
	if (init_mutexes(table) != 0)
		return (free(table->philos), free(table->forks),
			free(table->meal_locks), 1);
	init_philos(table);
	return (0);
}

static void	assign_forks(t_philo *philo, pthread_mutex_t *forks, int i, int n)
{
	if (i % 2 == 0)
	{
		philo->left_fork = &forks[(i + 1) % n];
		philo->right_fork = &forks[i];
	}
	else
	{
		philo->left_fork = &forks[i];
		philo->right_fork = &forks[(i + 1) % n];
	}
}

static void	init_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->data.nb_philos)
	{
		table->philos[i].index = i;
		table->philos[i].meals_eaten = 0;
		table->philos[i].last_meal = 0;
		table->philos[i].data = &table->data;
		table->philos[i].meal_lock = &table->meal_locks[i];
		assign_forks(&table->philos[i], table->forks, i,
			table->data.nb_philos);
		i++;
	}
}

static int	init_mutexes(t_table *table)
{
	int	i;

	if (pthread_mutex_init(&table->data.stop_lock, NULL) != 0)
		return (error_exit("Mutex init failed"), 1);
	if (pthread_mutex_init(&table->data.print_lock, NULL) != 0)
		return (error_exit("Mutex init failed"), 1);
	i = 0;
	while (i < table->data.nb_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (error_exit("Mutex init failed"), 1);
		if (pthread_mutex_init(&table->meal_locks[i], NULL) != 0)
			return (error_exit("Mutex init failed"), 1);
		i++;
	}
	return (0);
}
