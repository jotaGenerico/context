#include "philo.h"

int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
	return (0);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_check);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_check);
	print_status(philo, "is eating");
	precise_usleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	precise_usleep(philo->data->time_to_sleep, philo->data);
}

void	think(t_philo *philo)
{
	print_status(philo, "is thinking");
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!is_simulation_stopped(philo->data))
	{
		take_forks(philo);
		eat(philo);
		if (philo->data->must_eat_count != -1
			&& philo->meals_eaten >= philo->data->must_eat_count)
			break ;
		philo_sleep(philo);
		think(philo);
	}
	return (NULL);
}
