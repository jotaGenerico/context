#include "../includes/philo_bonus.h"

void error_exit(const char *msg)
{
    fprintf(stderr, "Error: %s\n", msg);
}

void safe_print(t_data *data, int id, const char *status)
{
    sem_wait(data->print);
    long ts = get_time() - data->start_time;
    printf("%ld %d %s\n", ts, id, status);
#ifdef DEBUG_PRINT
    // Linha extra em stderr com colunas alinhadas (sem cores)
    // No bônus não temos meals_eaten aqui; focamos em timestamp/id/ação
    fprintf(stderr, "[%6ld] P%-2d %-12s\n", ts, id, status);
#endif
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
    cleanup_semaphores(); // ensure clean state
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
