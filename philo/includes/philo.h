#ifndef PHILO_H
# define PHILO_H

// cores
# define RESET   "\033[0m"
# define RED     "\033[1;31m"
# define GREEN   "\033[1;32m"
# define YELLOW  "\033[1;33m"
# define BLUE    "\033[1;34m"
# define MAGENTA "\033[1;35m"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_data
{
	int				nb_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat_count;
	long			start_time;
	bool			stop;
	pthread_mutex_t	stop_lock;
	pthread_mutex_t	print_lock;
}	t_data;

typedef struct s_philo
{
	int				index;
	int				meals_eaten;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*meal_lock;
	t_data			*data;
}	t_philo;

typedef struct s_table
{
	t_data			data;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*meal_locks;
	pthread_t		monitor;
}	t_table;

// parsing.c
int		parse_args(int ac, char **av, t_data *data);
int		ft_atoi(const char *str);

// init.c
int		init_table(t_table *table);

// simulation.c
void	start_simulation(t_table *table);
void	cleanup(t_table *table);

// routine.c
void	*philo_routine(void *arg);

// monitor.c
void	*monitor_routine(void *arg);

// time.c
long	get_time_us(void);
void	sleep_ms(long ms, t_data *data);

// utils.c
void	print_msg(t_philo *philo, char *msg);
bool	is_stopped(t_data *data);
void	error_exit(char *msg);

#endif
