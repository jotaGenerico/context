#ifndef PHILO_BONUS_H
#define PHILO_BONUS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <semaphore.h>
#include <fcntl.h>
#include <stdbool.h>

// Names for POSIX named semaphores
#define SEM_FORKS "/philo_forks"
#define SEM_PRINT "/philo_print"
#define SEM_LIMIT "/philo_limit"

typedef struct s_data {
    int   nb_philos;
    int   time_to_die;
    int   time_to_eat;
    int   time_to_sleep;
    int   must_eat_count; // -1 if not provided
    long  start_time;
    sem_t *forks;
    sem_t *print;
    sem_t *limit;
    pid_t *pids;
} t_data;

// Child-local state
typedef struct s_philo {
    int   id;
    int   meals_eaten;
    long  last_meal_time;
    int   done;
    t_data *data;
} t_philo;

// parsing_bonus.c
int  parse_args_bonus(int ac, char **av, t_data *data);
int  ft_atoi(const char *str);
int  ft_strncmp(const char *s1, const char *s2, size_t n);

// time_bonus.c
long get_time(void);
long get_elapsed_time(long start_time);
void precise_usleep(long ms);

// utils_bonus.c
void safe_print(t_data *data, int id, const char *status);
void error_exit(const char *msg);
void setup_semaphores(t_data *data);
void cleanup_semaphores(void);

// routine_bonus.c
void philo_process(t_data *data, int id);
// death monitor via inline checks in sleep

// simulation_bonus.c
int  start_simulation_bonus(t_data *data);

#endif
