#include "../includes/philo_bonus.h"

static void spawn_children(t_data *data)
{
    int i = 0;
    data->pids = calloc(data->nb_philos, sizeof(pid_t));
    if (!data->pids) {
        error_exit("Failed to allocate pids");
        exit(1);
    }
    while (i < data->nb_philos) {
        pid_t pid = fork();
        if (pid < 0) {
            error_exit("fork failed");
            exit(1);
        } else if (pid == 0) {
            philo_process(data, i + 1);
        } else {
            data->pids[i] = pid;
        }
        i++;
    }
}

static void kill_all(t_data *data)
{
    for (int i = 0; i < data->nb_philos; i++) {
        if (data->pids[i] > 0)
            kill(data->pids[i], SIGTERM);
    }
}

int start_simulation_bonus(t_data *data)
{
    int finished = 0;
    int status;
    pid_t pid;

    data->start_time = get_time();

    if (data->nb_philos == 1)
    {
        printf("0 1 has taken a fork\n");
        usleep(data->time_to_die * 1000);
        printf("%d 1 died\n", data->time_to_die);
        return (0);
    }

    setup_semaphores(data);
    spawn_children(data);

    while ((pid = waitpid(-1, &status, 0)) > 0) {
        if (WIFEXITED(status)) {
            int code = WEXITSTATUS(status);
            if (code == 0) {
                finished++;
                if (data->must_eat_count != -1 && finished == data->nb_philos)
                    break;
            } else {
                kill_all(data);
                break;
            }
        } else if (WIFSIGNALED(status)) {
            kill_all(data);
            break;
        }
    }

    for (int i = 0; i < data->nb_philos; i++) {
        if (data->pids[i] > 0)
            waitpid(data->pids[i], NULL, 0);
    }
    sem_close(data->forks);
    sem_close(data->print);
    sem_close(data->limit);
    cleanup_semaphores();
    free(data->pids);
    return 0;
}
