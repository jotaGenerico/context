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

static char	*get_color(enum e_print print)
{
	if (print == e_dead)
		return (RED);
	if (print == e_thinking)
		return (GREEN);
	if (print == e_eating)
		return (YELLOW);
	if (print == e_sleeping)
		return (BLUE);
	if (print == e_fork)
		return (MAGENTA);
	return (RESET);
}

void	print_status(t_state *m, enum e_print print)
{
	const char	*msg[] = {
		"has taken a fork", "is eating", "is sleeping",
		"is thinking", "died"
	};
	char		*color;

	if (is_finished(m))
		return ;
	sem_wait(m->dead);
	if (print == e_dead)
		m->finished = sem_open("/finished", O_CREAT, 0644, 9999);
	sem_post(m->dead);
	color = get_color(print);
	sem_wait(m->pr);
	printf("%s%lld %d %s%s\n", color, get_time_ms() - m->p->start_time,
		m->index + 1, msg[(int)print], RESET);
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
