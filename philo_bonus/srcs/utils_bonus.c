#include "../includes/philo_bonus.h"

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define MAGENTA "\033[1;35m"

void error_exit(const char *msg)
{
    fprintf(stderr, "Error: %s\n", msg);
}

void safe_print(t_data *data, int id, const char *status)
{
    char *color;

    if (!ft_strncmp(status, "died", 4))
        color = RED;
    else if (!ft_strncmp(status, "is thinking", 11))
        color = GREEN;
    else if (!ft_strncmp(status, "is eating", 9))
        color = YELLOW;
    else if (!ft_strncmp(status, "is sleeping", 11))
        color = BLUE;
    else if (!ft_strncmp(status, "has taken a fork", 16))
        color = MAGENTA;
    else
        color = RESET;

    sem_wait(data->print);
    long ts = get_time() - data->start_time;
    printf("%s%ld %d %s%s\n", color, ts, id, status, RESET);
    sem_post(data->print);
}

void cleanup_semaphores(void)
{
    sem_unlink(SEM_FORKS);
    sem_unlink(SEM_PRINT);
    sem_unlink(SEM_LIMIT);
}

void setup_semaphores(t_data *data)
{
    cleanup_semaphores();
    data->forks = sem_open(SEM_FORKS, O_CREAT | O_EXCL, 0644, data->nb_philos);
    if (data->forks == SEM_FAILED) {
        error_exit("sem_open(forks) failed");
        exit(1);
    }
    data->print = sem_open(SEM_PRINT, O_CREAT | O_EXCL, 0644, 1);
    if (data->print == SEM_FAILED) {
        error_exit("sem_open(print) failed");
        sem_close(data->forks);
        cleanup_semaphores();
        exit(1);
    }
    data->limit = sem_open(SEM_LIMIT, O_CREAT | O_EXCL, 0644, data->nb_philos - 1);
    if (data->limit == SEM_FAILED) {
        error_exit("sem_open(limit) failed");
        sem_close(data->forks);
        sem_close(data->print);
        cleanup_semaphores();
        exit(1);
    }
}

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i = 0;
    while (i < n && (s1[i] || s2[i])) {
        if (s1[i] != s2[i])
            return ((unsigned char)s1[i] - (unsigned char)s2[i]);
        i++;
    }
    return 0;
}
