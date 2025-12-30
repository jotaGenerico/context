#include "philo_bonus.h"

static void	*death_monitor(void *arg);
static int	should_exit_meal(t_state *m);
static void	philo_eat_cycle(t_state *m);

void	*philo_routine(t_state *m)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, death_monitor, (void *)m);
	pthread_detach(thread);
	m->die_time = m->p->start_time + m->p->time_to_die;
	if (m->index % 2 == 0)
		usleep(1000);
	while (!is_finished(m))
	{
		think(m);
		philo_eat_cycle(m);
		if (should_exit_meal(m))
			break ;
		sleep_action(m);
	}
	return (NULL);
}

void	create_processes(t_state *states, t_params *params)
{
	int		i;
	pid_t	pid;
	pid_t	*pids;

	pids = alloc_pids(params->num_philos);
	if (!pids)
		return ;
	i = 0;
	while (i < params->num_philos)
	{
		pid = fork();
		if (pid == 0)
			init_and_run(states, params, i, pids);
		pids[i] = pid;
		if (pid != -1)
			i++;
	}
	if (pid != 0)
		wait_processes(params, pids);
	free(pids);
	sem_close(states->dead);
	sem_close(states->pr);
	sem_close(states->forks);
	sem_close(states->finished);
	sem_close(states->times_eaten_s);
}

static void	philo_eat_cycle(t_state *m)
{
	sem_wait(m->forks);
	print_status(m, e_fork);
	sem_wait(m->forks);
	print_status(m, e_fork);
	print_status(m, e_eating);
	m->die_time = get_time_ms() + m->p->time_to_die;
	wait_until(get_time_ms() + m->p->time_to_eat);
	sem_wait(m->times_eaten_s);
	if (m->p->must_eat_count != -1)
		m->meals_eaten += 1;
	sem_post(m->times_eaten_s);
	sem_post(m->forks);
	sem_post(m->forks);
}

static int	should_exit_meal(t_state *m)
{
	if (m->p->must_eat_count != -1
		&& m->meals_eaten >= m->p->must_eat_count)
		return (1);
	return (0);
}

static void	*death_monitor(void *arg)
{
	t_state	*m;

	m = (t_state *)arg;
	while (1)
	{
		usleep(1000);
		if (get_time_ms() >= m->die_time)
		{
			die(m);
			exit(1);
		}
		sem_wait(m->times_eaten_s);
		if (m->meals_eaten >= m->p->must_eat_count
			&& m->p->must_eat_count != -1)
		{
			sem_post(m->times_eaten_s);
			exit(0);
		}
		sem_post(m->times_eaten_s);
	}
	return (NULL);
}
