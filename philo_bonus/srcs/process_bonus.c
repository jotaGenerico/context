#include "philo_bonus.h"

void	kill_all_processes(pid_t *pids, int count, int skip)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (i != skip && pids[i] > 0)
			kill(pids[i], SIGKILL);
		i++;
	}
}

pid_t	*alloc_pids(int count)
{
	pid_t	*pids;

	pids = malloc(sizeof(pid_t) * count);
	return (pids);
}

void	init_and_run(t_state *states, t_params *params, int i, pid_t *p)
{
	init_state(states, params, i);
	free(p);
	philo_routine(states);
	exit(0);
}

void	wait_processes(t_params *params, pid_t *pids)
{
	int	i;
	int	status;

	i = 0;
	while (i < params->num_philos)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		{
			kill_all_processes(pids, params->num_philos, -1);
			break ;
		}
		i++;
	}
}
