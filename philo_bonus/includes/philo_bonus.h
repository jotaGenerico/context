#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

// cores
# define RESET   "\033[0m"
# define RED     "\033[1;31m"
# define GREEN   "\033[1;32m"
# define YELLOW  "\033[1;33m"
# define BLUE    "\033[1;34m"
# define MAGENTA "\033[1;35m"

# include <semaphore.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>
# include <signal.h>
# include <fcntl.h>

enum	e_print
{
	e_fork,
	e_eating,
	e_sleeping,
	e_thinking,
	e_dead,
};

typedef long long	t_msec;

typedef struct s_params
{
	int			num_philos;
	t_msec		time_to_die;
	t_msec		time_to_eat;
	t_msec		time_to_sleep;
	t_msec		start_time;
	int			must_eat_count;
}	t_params;

typedef struct s_state
{
	t_params		*p;
	int				index;
	t_msec			die_time;
	sem_t			*forks;
	sem_t			*finished;
	sem_t			*dead;
	sem_t			*times_eaten_s;
	int				meals_eaten;
	sem_t			*pr;
}	t_state;

pid_t	*alloc_pids(int count);
void	*check_death(void *m);
int		check_int(int sign, int *n);
int		check_ll(int sign, t_msec *n);
void	create_processes(t_state *states, t_params *params);
void	die(t_state *m);
void	eat(t_state *m);
int		ft_atoi(const char *str, int *n);
int		ft_atoll(const char *str, t_msec *n);
t_msec	get_time_ms(void);
void	init_and_run(t_state *states, t_params *params, int i, pid_t *p);
int		init_resources(t_state *state, t_params *params);
void	init_state(t_state *state, t_params *params, int i);
int		is_finished(t_state *m);
void	kill_all_processes(pid_t *pids, int count, int skip);
int		parse_args(int argc, char **argv, t_params *params);
void	*philo_routine(t_state *m);
void	print_status(t_state *m, enum e_print print);
void	print_usage(void);
void	sleep_action(t_state *m);
int		table_step(t_state *m);
void	think(t_state *m);
void	wait_processes(t_params *params, pid_t *pids);
void	wait_until(t_msec waiting_time);

#endif
