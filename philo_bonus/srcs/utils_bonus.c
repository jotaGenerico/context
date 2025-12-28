#include "philo_bonus.h"

static sem_t	*_open_sem(const char *name, int val)
{
	sem_t	*sem;

	sem_unlink(name);
	sem = sem_open(name, O_CREAT | O_EXCL, 0644, val);
	if (sem == SEM_FAILED)
		exit(1);
	return (sem);
}

void	setup_semaphores(t_data *data)
{
	int	limit;

	cleanup_semaphores();
	if (data->nb_philos > 1)
		limit = (data->nb_philos + 1) / 2;
	else
		limit = 1;
	data->forks = _open_sem(SEM_FORKS, data->nb_philos);
	data->print = _open_sem(SEM_PRINT, 1);
	data->death = _open_sem(SEM_DEATH, 1);
	data->finish = _open_sem(SEM_FINISH, 0);
	data->control = _open_sem(SEM_CONTROL, limit);
}

void	cleanup_semaphores(void)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_DEATH);
	sem_unlink(SEM_FINISH);
	sem_unlink(SEM_CONTROL);
}

void	safe_print(t_data *data, int id, const char *status)
{
	long	ts;

	sem_wait(data->print);
	if (is_finished(data))
	{
		sem_post(data->print);
		return ;
	}
	ts = (get_time_us() - data->start_time) / 1000;
	printf("%ld %d %s\n", ts, id, status);
	sem_post(data->print);
}

bool	is_finished(t_data *data)
{
	int	val;

	if (sem_getvalue(data->finish, &val) == -1)
		return (true);
	return (val > 0);
}
