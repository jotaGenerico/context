#include "philo.h"

static void	think(t_philo *philo);
static void	philo_sleep(t_philo *philo);
static void	eat(t_philo *philo);
static void	take_forks(t_philo *philo);

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->index % 2 == 0)
		usleep(1000);
	while (!is_stopped(philo->data))
	{
		think(philo);
		take_forks(philo);
		eat(philo);
		if (is_stopped(philo->data))
			break ;
		if (philo->data->must_eat_count != -1
			&& philo->meals_eaten >= philo->data->must_eat_count)
			break ;
		philo_sleep(philo);
	}
	return (NULL);
}

static void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_msg(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_msg(philo, "has taken a fork");
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_time_us();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	print_msg(philo, "is eating");
	sleep_ms(philo->data->time_to_eat / 1000, philo->data);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static void	philo_sleep(t_philo *philo)
{
	print_msg(philo, "is sleeping");
	sleep_ms(philo->data->time_to_sleep / 1000, philo->data);
}

static void	think(t_philo *philo)
{
	print_msg(philo, "is thinking");
	usleep(1000);
}
