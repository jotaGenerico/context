#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# define RESET   "\033[0m"
# define RED     "\033[1;31m"
# define GREEN   "\033[1;32m"
# define YELLOW  "\033[1;33m"
# define BLUE    "\033[1;34m"
# define MAGENTA "\033[1;35m"

# define SEM_FORKS "/philo_forks"
# define SEM_PRINT "/philo_print"
# define SEM_DEATH "/philo_death"
# define SEM_FINISH "/philo_finish"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <semaphore.h>
# include <fcntl.h>
# include <stdbool.h>

typedef struct s_data
{
	int		nb_philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		must_eat_count;
	long	start_time;
	sem_t	*forks;
	sem_t	*print;
	sem_t	*death;
	sem_t	*finish;
	pid_t	*pids;
}	t_data;

typedef struct s_philo
{
	int		id;
	int		meals_eaten;
	long	last_meal;
	t_data	*data;
}	t_philo;

void	cleanup_semaphores(void);
void	error_exit(const char *msg);
int		ft_atoi(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
long	get_time_us(void);
bool	is_finished(t_data *data);
int		parse_args_bonus(int ac, char **av, t_data *data);
void	philo_process(t_data *data, int id);
void	safe_print(t_data *data, int id, const char *status);
void	setup_semaphores(t_data *data);
int		start_simulation_bonus(t_data *data);

#endif
