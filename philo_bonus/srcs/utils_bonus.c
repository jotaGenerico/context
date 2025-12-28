#include "philo_bonus.h"

static char	*get_color(const char *status);

void	safe_print(t_data *data, int id, const char *status)
{
	char	*color;
	long	ts;

	color = get_color(status);
	sem_wait(data->print);
	ts = (get_time_us() - data->start_time) / 1000;
	printf("%s%ld %d %s%s\n", color, ts, id, status, RESET);
	sem_post(data->print);
}

bool	is_finished(t_data *data)
{
	int	val;

	sem_getvalue(data->finish, &val);
	return (val > 0);
}

void	cleanup_semaphores(void)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_DEATH);
	sem_unlink(SEM_FINISH);
}

void	setup_semaphores(t_data *data)
{
	cleanup_semaphores();
	data->forks = sem_open(SEM_FORKS, O_CREAT | O_EXCL, 0644,
			data->nb_philos);
	if (data->forks == SEM_FAILED)
		return (error_exit("sem_open(forks) failed"), exit(1));
	data->print = sem_open(SEM_PRINT, O_CREAT | O_EXCL, 0644, 1);
	if (data->print == SEM_FAILED)
		return (sem_close(data->forks), cleanup_semaphores(),
			error_exit("sem_open(print) failed"), exit(1));
	data->death = sem_open(SEM_DEATH, O_CREAT | O_EXCL, 0644, 1);
	if (data->death == SEM_FAILED)
		return (sem_close(data->forks), sem_close(data->print),
			cleanup_semaphores(), error_exit("sem_open(death) failed"),
			exit(1));
	data->finish = sem_open(SEM_FINISH, O_CREAT | O_EXCL, 0644, 0);
	if (data->finish == SEM_FAILED)
		return (sem_close(data->forks), sem_close(data->print),
			sem_close(data->death), cleanup_semaphores(),
			error_exit("sem_open(finish) failed"), exit(1));
}

static char	*get_color(const char *status)
{
	if (status[0] == 'd')
		return (RED);
	if (status[0] == 'i' && status[3] == 't')
		return (GREEN);
	if (status[0] == 'i' && status[3] == 'e')
		return (YELLOW);
	if (status[0] == 'i' && status[3] == 's')
		return (BLUE);
	if (status[0] == 'h')
		return (MAGENTA);
	return (RESET);
}
