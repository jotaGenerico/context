#include "philo_bonus.h"

static void	spawn_children(t_data *data);
static void	kill_all(t_data *data);
static void	wait_all(t_data *data);

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
	wait_all(data);
	return (0);
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

static void	wait_all(t_data *data)
{
	int		i;
	int		status;
	pid_t	pid;

	i = 0;
	while (i < data->nb_philos)
	{
		pid = waitpid(-1, &status, 0);
		if (pid > 0 && WIFEXITED(status) && WEXITSTATUS(status) == 1)
		{
			kill_all(data);
			return ;
		}
		i++;
	}
	kill_all(data);
}

static void	kill_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		if (data->pids[i] > 0)
			kill(data->pids[i], SIGKILL);
		i++;
	}
	i = 0;
	while (i < data->nb_philos)
	{
		if (data->pids[i] > 0)
			waitpid(data->pids[i], NULL, WNOHANG);
		i++;
	}
	sem_close(data->forks);
	sem_close(data->print);
	sem_close(data->death);
	sem_close(data->finish);
	sem_close(data->control);
	cleanup_semaphores();
	if (data->pids)
		free(data->pids);
}
