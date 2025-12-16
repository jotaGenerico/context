#include "../includes/philo.h"

bool	check_death(t_table *table)
{
	int		i;
	long	time_since_meal;
	long	current_time;

	i = 0;
	current_time = get_time();
	while (i < table->data.nb_philos)
	{
		pthread_mutex_lock(&table->data.meal_check);
		time_since_meal = current_time - table->philos[i].last_meal_time;
		pthread_mutex_unlock(&table->data.meal_check);

		if (time_since_meal >= table->data.time_to_die)
		{
			pthread_mutex_lock(&table->data.write_lock);
			// ✅ Adiciona cor vermelha para morte
			printf("%s%ld %d died%s\n",
				RED,
				get_time() - table->data.start_time,
				table->philos[i].id,
				RESET);
			pthread_mutex_unlock(&table->data.write_lock);

			pthread_mutex_lock(&table->data.death_lock);
			table->data.simulation_stop = true;
			pthread_mutex_unlock(&table->data.death_lock);
			return (true);
		}
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
	while (i < table->data.nb_philos)
	{
		pthread_mutex_lock(&table->data.meal_check);
		if (table->philos[i].meals_eaten >= table->data.must_eat_count)
			finished++;
		pthread_mutex_unlock(&table->data.meal_check);
		i++;
	}
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
		if (check_death(table))
			break ;
		if (check_all_ate(table))
			break ;
		usleep(1000);
	}
	return (NULL);
}
