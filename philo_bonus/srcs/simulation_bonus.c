#include "philo_bonus.h"

static void	spawn_children(t_data *data);
static void	kill_all(t_data *data);
static int	wait_children(t_data *data);

int	start_simulation_bonus(t_data *data)
{
	data->start_time = get_time_us();
	if (data->nb_philos == 1)
	{
		printf("0 1 has taken a fork\n");
		usleep(data->time_to_die);
		printf("%s%ld 1 died%s\n", RED, data->time_to_die / 1000, RESET);
		return (0);
	}
	setup_semaphores(data);
	spawn_children(data);
	return (wait_children(data));
}

static int	wait_children(t_data *data)
{
	int		finished;
	int		status;
	pid_t	pid;

	finished = 0;
	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
		{
			finished++;
			if (data->must_eat_count != -1 && finished == data->nb_philos)
				break ;
		}
		else
			return (kill_all(data), 0);
		pid = waitpid(-1, &status, 0);
	}
	return (kill_all(data), 0);
}

static void	spawn_children(t_data *data)
{
	int		i;
	pid_t	pid;

	data->pids = malloc(sizeof(pid_t) * data->nb_philos);
	if (!data->pids)
		return (error_exit("Failed to allocate pids"), exit(1));
	i = 0;
	while (i < data->nb_philos)
	{
		pid = fork();
		if (pid < 0)
			return (error_exit("fork failed"), exit(1));
		else if (pid == 0)
			philo_process(data, i + 1);
		else
			data->pids[i] = pid;
		i++;
	}
}

static void	kill_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		if (data->pids[i] > 0)
			kill(data->pids[i], SIGTERM);
		i++;
	}
	i = 0;
	while (i < data->nb_philos)
	{
		if (data->pids[i] > 0)
			waitpid(data->pids[i], NULL, 0);
		i++;
	}
	sem_close(data->forks);
	sem_close(data->print);
	sem_close(data->limit);
	cleanup_semaphores();
	free(data->pids);
}
