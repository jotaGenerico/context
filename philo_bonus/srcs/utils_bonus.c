#include "philo_bonus.h"

void	init_state(t_state *state, t_params *params, int i)
{
	state->index = i;
	state->meals_eaten = 0;
	state->p = params;
}

int	init_resources(t_state *state, t_params *params)
{
	sem_unlink("/forks");
	sem_unlink("/pr");
	sem_unlink("/dead");
	sem_unlink("/times_eaten_s");
	sem_unlink("/finished");
	state->forks = sem_open("/forks", O_CREAT, 0644, params->num_philos);
	state->times_eaten_s = sem_open("/times_eaten_s", O_CREAT, 0644, 1);
	state->dead = sem_open("/dead", O_CREAT, 0644, 1);
	state->pr = sem_open("/pr", O_CREAT, 0644, 1);
	sem_unlink("/forks");
	sem_unlink("/pr");
	sem_unlink("/dead");
	sem_unlink("/times_eaten_s");
	return (0);
}

void	print_status(t_state *m, enum e_print print)
{
	const char	*msg[] = {
		"has taken a fork", "is eating", "is sleeping",
		"is thinking", "died"
	};

	if (is_finished(m))
		return ;
	sem_wait(m->dead);
	if (print == e_dead)
		m->finished = sem_open("/finished", O_CREAT, 0644, 9999);
	sem_post(m->dead);
	sem_wait(m->pr);
	printf("%lld %d %s\n", get_time_ms() - m->p->start_time, m->index + 1,
		msg[(int)print]);
	sem_post(m->pr);
}

int	is_finished(t_state *m)
{
	sem_t	*finished;

	sem_wait(m->dead);
	finished = sem_open("/finished", 0);
	if (finished == SEM_FAILED)
	{
		sem_post(m->dead);
		return (0);
	}
	sem_close(finished);
	sem_post(m->dead);
	return (1);
}
