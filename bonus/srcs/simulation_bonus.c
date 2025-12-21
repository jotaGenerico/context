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
            // child process
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
    setup_semaphores(data);
    spawn_children(data);

    // Wait for any child to exit; non-zero => death
    while ((pid = waitpid(-1, &status, 0)) > 0) {
        if (WIFEXITED(status)) {
            int code = WEXITSTATUS(status);
            if (code == 0) {
                finished++;
                if (data->must_eat_count != -1 && finished == data->nb_philos)
                    break;
            } else {
                // child died
                kill_all(data);
                break;
            }
        } else if (WIFSIGNALED(status)) {
            // treat as death
            kill_all(data);
            break;
        }
    }

    // cleanup
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
