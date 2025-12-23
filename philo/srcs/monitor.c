#include "philo.h"

static bool	handle_death(t_table *table, int i, long death_time);
static void	print_death(t_table *table, int i, long death_time);

bool	check_death(t_table *table)
{
	int		i;
	long	time_since_meal;
	long	current_time;
	long	death_time;

	i = 0;
	current_time = get_time();
	while (i < table->data.nb_philos)
	{
		pthread_mutex_lock(&table->data.meal_check);
		time_since_meal = current_time - table->philos[i].last_meal_time;
		if (time_since_meal >= table->data.time_to_die)
		{
			death_time = table->philos[i].last_meal_time
				+ table->data.time_to_die;
			pthread_mutex_unlock(&table->data.meal_check);
			return (handle_death(table, i, death_time));
		}
		pthread_mutex_unlock(&table->data.meal_check);
		i++;
	}
	return (false);
}

bool	check_all_ate(t_table *table)
{
	int	i;
	int	finished;

	if (table->data.must_eat_count == -1)
		return (false);
	i = 0;
	finished = 0;
	pthread_mutex_lock(&table->data.meal_check);
	while (i < table->data.nb_philos)
	{
		if (table->philos[i].meals_eaten >= table->data.must_eat_count)
			finished++;
		i++;
	}
	pthread_mutex_unlock(&table->data.meal_check);
	if (finished == table->data.nb_philos)
	{
		pthread_mutex_lock(&table->data.death_lock);
		table->data.simulation_stop = true;
		pthread_mutex_unlock(&table->data.death_lock);
		return (true);
	}
	return (false);
}

void	*monitor_routine(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (!is_simulation_stopped(&table->data))
	{
		if (check_all_ate(table))
			break ;
		if (check_death(table))
			break ;
		usleep(1000);
	}
	return (NULL);
}

static void	print_death(t_table *table, int i, long death_time)
{
	pthread_mutex_lock(&table->data.write_lock);
	printf("%s%ld %d died%s\n", RED,
		death_time - table->data.start_time,
		table->philos[i].id, RESET);
	pthread_mutex_unlock(&table->data.write_lock);
}

static bool	handle_death(t_table *table, int i, long death_time)
{
	pthread_mutex_lock(&table->data.death_lock);
	if (!table->data.simulation_stop)
	{
		table->data.simulation_stop = true;
		pthread_mutex_unlock(&table->data.death_lock);
		print_death(table, i, death_time);
		return (true);
	}
	pthread_mutex_unlock(&table->data.death_lock);
	return (true);
}
