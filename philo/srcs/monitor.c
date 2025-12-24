#include "philo.h"

static bool	check_all_ate(t_table *table);
static bool	check_death(t_table *table);

void	*monitor_routine(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (!is_stopped(&table->data))
	{
		if (check_all_ate(table))
			break ;
		if (check_death(table))
			break ;
		usleep(1000);
	}
	return (NULL);
}

static bool	check_death(t_table *table)
{
	int		i;
	long	time_since_meal;
	long	current;

	i = 0;
	current = get_time_us();
	while (i < table->data.nb_philos)
	{
		pthread_mutex_lock(&table->meal_locks[i]);
		if (table->philos[i].last_meal == 0)
			time_since_meal = current - table->data.start_time;
		else
			time_since_meal = current - table->philos[i].last_meal;
		pthread_mutex_unlock(&table->meal_locks[i]);
		if (time_since_meal >= table->data.time_to_die)
		{
			pthread_mutex_lock(&table->data.stop_lock);
			table->data.stop = true;
			pthread_mutex_unlock(&table->data.stop_lock);
			pthread_mutex_lock(&table->data.print_lock);
			printf("%ld %d died\n",
				(current - table->data.start_time) / 1000, i + 1);
			pthread_mutex_unlock(&table->data.print_lock);
			return (true);
		}
		i++;
	}
	return (false);
}

static bool	check_all_ate(t_table *table)
{
	int	i;
	int	finished;

	if (table->data.must_eat_count == -1)
		return (false);
	i = 0;
	finished = 0;
	while (i < table->data.nb_philos)
	{
		pthread_mutex_lock(&table->meal_locks[i]);
		if (table->philos[i].meals_eaten >= table->data.must_eat_count)
			finished++;
		pthread_mutex_unlock(&table->meal_locks[i]);
		i++;
	}
	if (finished == table->data.nb_philos)
	{
		pthread_mutex_lock(&table->data.stop_lock);
		table->data.stop = true;
		pthread_mutex_unlock(&table->data.stop_lock);
		return (true);
	}
	return (false);
}
