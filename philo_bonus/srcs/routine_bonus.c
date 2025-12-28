#include "philo_bonus.h"

static void	*death_monitor(void *arg)
{
	t_philo	*ph;
	long	now;

	ph = (t_philo *)arg;
	while (1)
	{
		sem_wait(ph->data->death);
		now = get_time_us() - ph->last_meal;
		sem_post(ph->data->death);
		if (now >= ph->data->time_to_die)
		{
			sem_wait(ph->data->print);
			if (!is_finished(ph->data))
			{
				printf("%ld %d died\n", (get_time_us() \
					- ph->data->start_time) / 1000, ph->id);
				sem_post(ph->data->finish);
			}
			exit(1);
		}
		if (is_finished(ph->data))
			exit(1);
		usleep(500);
	}
	return (NULL);
}

static void	take_forks_and_eat(t_philo *ph)
{
	sem_wait(ph->data->control);
	sem_wait(ph->data->forks);
	safe_print(ph->data, ph->id, "has taken a fork");
	sem_wait(ph->data->forks);
	safe_print(ph->data, ph->id, "has taken a fork");
	sem_wait(ph->data->death);
	ph->last_meal = get_time_us();
	ph->meals_eaten++;
	sem_post(ph->data->death);
	safe_print(ph->data, ph->id, "is eating");
	usleep(ph->data->time_to_eat);
	sem_post(ph->data->forks);
	sem_post(ph->data->forks);
	sem_post(ph->data->control);
}

void	philo_process(t_data *data, int id)
{
	t_philo		ph;
	pthread_t	monitor;

	ph.id = id;
	ph.meals_eaten = 0;
	ph.data = data;
	ph.last_meal = get_time_us();
	if (pthread_create(&monitor, NULL, death_monitor, &ph) != 0)
		exit(1);
	pthread_detach(monitor);
	if (ph.id % 2 == 0)
		usleep(data->time_to_eat / 2);
	while (1)
	{
		safe_print(ph.data, ph.id, "is thinking");
		take_forks_and_eat(&ph);
		if (ph.data->must_eat_count != -1 \
			&& ph.meals_eaten >= ph.data->must_eat_count)
			break ;
		safe_print(ph.data, ph.id, "is sleeping");
		usleep(ph.data->time_to_sleep);
	}
	while (!is_finished(ph.data))
		usleep(1000);
	exit(0);
}
