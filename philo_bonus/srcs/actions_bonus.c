#include "philo_bonus.h"

void	eat(t_state *m)
{
	print_status(m, e_fork);
	{
		sem_wait(m->forks);
		print_status(m, e_fork);
		print_status(m, e_eating);
		if (get_time_ms() + m->p->time_to_eat > m->die_time)
		{
			die(m);
			sem_post(m->forks);
			sem_post(m->forks);
			return ;
		}
		m->die_time = get_time_ms() + m->p->time_to_die + m->p->time_to_eat;
		wait_until(get_time_ms() + m->p->time_to_eat);
		{
			sem_wait(m->times_eaten_s);
			if (m->p->must_eat_count != -1)
				m->meals_eaten += 1;
			sem_post(m->times_eaten_s);
		}
		sem_post(m->forks);
	}
	sem_post(m->forks);
}

void	sleep_action(t_state *m)
{
	print_status(m, e_sleeping);
	wait_until(get_time_ms() + m->p->time_to_sleep);
}

void	think(t_state *m)
{
	print_status(m, e_thinking);
}

void	die(t_state *m)
{
	wait_until(m->die_time);
	print_status(m, e_dead);
}
