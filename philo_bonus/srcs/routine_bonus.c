#include "philo_bonus.h"

static void	check_death(t_philo *ph);
static void	smart_sleep(t_philo *ph, long ms);
static void	take_forks_and_eat(t_philo *ph);

void	philo_process(t_data *data, int id)
{
	t_philo	ph;

	ph.id = id;
	ph.meals_eaten = 0;
	ph.data = data;
	ph.last_meal = get_time_us();
	if (id % 2 != 0)
		usleep(100);
	while (1)
	{
		safe_print(data, id, "is thinking");
		take_forks_and_eat(&ph);
		if (data->must_eat_count != -1
			&& ph.meals_eaten >= data->must_eat_count)
			exit(0);
		safe_print(data, id, "is sleeping");
		smart_sleep(&ph, data->time_to_sleep / 1000);
	}
}

static void	check_death(t_philo *ph)
{
	long	time_since_meal;

	time_since_meal = get_time_us() - ph->last_meal;
	if (time_since_meal >= ph->data->time_to_die)
	{
		safe_print(ph->data, ph->id, "died");
		exit(1);
	}
}

static void	smart_sleep(t_philo *ph, long ms)
{
	long	start;
	long	target;

	start = get_time_us();
	target = ms * 1000;
	while (get_time_us() - start < target)
	{
		check_death(ph);
		usleep(100);
	}
}

static void	take_forks_and_eat(t_philo *ph)
{
	check_death(ph);
	sem_wait(ph->data->limit);
	check_death(ph);
	sem_wait(ph->data->forks);
	safe_print(ph->data, ph->id, "has taken a fork");
	check_death(ph);
	sem_wait(ph->data->forks);
	safe_print(ph->data, ph->id, "has taken a fork");
	ph->last_meal = get_time_us();
	ph->meals_eaten++;
	safe_print(ph->data, ph->id, "is eating");
	smart_sleep(ph, ph->data->time_to_eat / 1000);
	sem_post(ph->data->forks);
	sem_post(ph->data->forks);
	sem_post(ph->data->limit);
}
