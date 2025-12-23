#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

// ========== CORES ANSI ==========
# define RESET   "\033[0m"
# define RED     "\033[1;31m"      // Morreu (vermelho forte)
# define GREEN   "\033[1;32m"      // Pensando (verde)
# define YELLOW  "\033[1;33m"      // Comendo (amarelo)
# define BLUE    "\033[1;34m"      // Dormindo (azul)
# define MAGENTA "\033[1;35m"      // Pegou garfo (magenta)
# define CYAN    "\033[1;36m"      // Info (ciano)

// ========== ESTRUTURAS ==========
typedef struct s_data
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	long			start_time;
	bool			simulation_stop;
	bool			all_ate_enough;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	meal_check;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

typedef struct s_table
{
	t_data			data;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_t		monitor_thread;
}	t_table;

// ========== PROTÓTIPOS ==========

// parsing.c
int		parse_args(int ac, char **av, t_data *data);

// init.c
int		init_table(t_table *table);
void	init_philos(t_table *table);

// simulation.c
void	start_simulation(t_table *table);
void	cleanup(t_table *table);

// routine.c
void	*philosopher_routine(void *arg);
void	take_forks(t_philo *philo);
void	eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	think(t_philo *philo);

// monitor.c
void	*monitor_routine(void *arg);
bool	check_death(t_table *table);
bool	check_all_ate(t_table *table);

// time.c
long	get_time(void);
long	get_elapsed_time(long start_time);
void	precise_usleep(long milliseconds, t_data *data);

// utils.c
void	print_status(t_philo *philo, char *status);
bool	is_simulation_stopped(t_data *data);
int		ft_atoi(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	error_exit(char *msg);

#endif
