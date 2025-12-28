#include "philo_bonus.h"

static void	*death_monitor(void *arg);
static void	take_forks_and_eat(t_philo *ph);
static void	philo_routine(t_philo *ph);

void	philo_process(t_data *data, int id)
{
	t_philo		ph;
	pthread_t	monitor;

	ph.id = id;
	ph.meals_eaten = 0;
	ph.data = data;
	ph.last_meal = get_time_us();
	pthread_create(&monitor, NULL, death_monitor, &ph);
	pthread_detach(monitor);
	if (id % 2 == 0)
		usleep(100);
	philo_routine(&ph);
	exit(0);
}

static void	philo_routine(t_philo *ph)
{
	while (!is_finished(ph->data))
	{
		safe_print(ph->data, ph->id, "is thinking");
		if (is_finished(ph->data))
			break ;
		take_forks_and_eat(ph);
		if (is_finished(ph->data))
			break ;
		if (ph->data->must_eat_count != -1
			&& ph->meals_eaten >= ph->data->must_eat_count)
			break ;
		safe_print(ph->data, ph->id, "is sleeping");
		usleep(ph->data->time_to_sleep);
	}
}

static void	*death_monitor(void *arg)
{
	t_philo	*ph;
	long	time_since_meal;

	ph = (t_philo *)arg;
	while (1)
	{
		if (is_finished(ph->data))
		{
			kill(0, SIGKILL);
			exit(1);
		}
		sem_wait(ph->data->death);
		time_since_meal = get_time_us() - ph->last_meal;
		if (time_since_meal >= ph->data->time_to_die)
		{
			safe_print(ph->data, ph->id, "died");
			sem_post(ph->data->finish);
			sem_wait(ph->data->print);
			kill(0, SIGKILL);
			exit(1);
		}
		sem_post(ph->data->death);
		usleep(1000);
	}
	return (NULL);
}

static void	take_forks_and_eat(t_philo *ph)
{
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
}
