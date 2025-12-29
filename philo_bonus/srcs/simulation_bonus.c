#include "philo_bonus.h"

int	table_step(t_state *m)
{
	if (is_finished(m))
		return (0);
	sem_wait(m->forks);
	if (get_time_ms() <= m->die_time && (m->meals_eaten < m->p->must_eat_count
			|| m->p->must_eat_count == -1))
		eat(m);
	else
	{
		sem_post(m->forks);
		if (get_time_ms() + m->p->time_to_eat > m->die_time)
			die(m);
		return (0);
	}
	if (is_finished(m))
		return (0);
	if (get_time_ms() + m->p->time_to_sleep > m->die_time)
	{
		m->die_time -= m->p->time_to_eat;
		die(m);
		return (0);
	}
	else
		sleep_action(m);
	think(m);
	return (1);
}

void	*philo_routine(t_state *m)
{
	pthread_t	thread;
	int			cont;

	pthread_create(&thread, NULL, check_death, (void *)m);
	m->die_time = m->p->start_time + m->p->time_to_die;
	if (m->index % 2 == 0)
		wait_until(get_time_ms() + m->p->time_to_eat);
	cont = 1;
	while (cont)
		cont = table_step(m);
	pthread_join(thread, NULL);
	return (NULL);
}

void	create_processes(t_state *states, t_params *params)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < params->num_philos)
	{
		pid = fork();
		if (pid == 0)
		{
			init_state(states, params, i);
			philo_routine(states);
			return ;
		}
		if (pid != -1)
			i++;
	}
	if (pid != 0)
		wait_processes(params);
	sem_close(states->dead);
	sem_close(states->pr);
	sem_close(states->forks);
	sem_close(states->finished);
}

void	wait_processes(t_params *params)
{
	int	i;

	i = 0;
	while (i < params->num_philos)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
}

void	*check_death(void *m)
{
	t_state	*state;

	state = (t_state *)m;
	while (1)
	{
		if (is_finished(m))
		{
			sem_unlink("/finished");
			kill(0, SIGKILL);
			return (NULL);
		}
		else
		{
			sem_wait(state->times_eaten_s);
			if (state->meals_eaten == state->p->must_eat_count)
			{
				sem_post(state->times_eaten_s);
				return (NULL);
			}
			sem_post(state->times_eaten_s);
		}
	}
}
