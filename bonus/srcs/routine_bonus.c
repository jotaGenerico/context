#include "../includes/philo_bonus.h"

static void smart_sleep_child(t_philo *ph, long ms)
{
    long start = get_time();
    while (get_time() - start < ms) {
        if (get_time() - ph->last_meal_time >= ph->data->time_to_die) {
            safe_print(ph->data, ph->id, "died");
            _exit(1);
        }
        usleep(100);
    }
}

static void take_forks_and_eat(t_philo *ph)
{
    // Limit concurrent philosophers attempting to take forks
    sem_wait(ph->data->limit);
    sem_wait(ph->data->forks);
    safe_print(ph->data, ph->id, "has taken a fork");
    sem_wait(ph->data->forks);
    safe_print(ph->data, ph->id, "has taken a fork");

    ph->last_meal_time = get_time();
    ph->meals_eaten++;
    safe_print(ph->data, ph->id, "is eating");
    smart_sleep_child(ph, ph->data->time_to_eat);

    sem_post(ph->data->forks);
    sem_post(ph->data->forks);
    sem_post(ph->data->limit);
}

void philo_process(t_data *data, int id)
{
    t_philo ph;
    ph.id = id;
    ph.meals_eaten = 0;
    ph.data = data;
    ph.last_meal_time = get_time();
    ph.done = 0;

    // odd stagger to reduce contention
    if (id % 2 != 0)
        usleep(1000);

    while (1) {
        take_forks_and_eat(&ph);
        if (data->must_eat_count != -1 && ph.meals_eaten >= data->must_eat_count)
            break;
        safe_print(data, id, "is sleeping");
        smart_sleep_child(&ph, data->time_to_sleep);
        safe_print(data, id, "is thinking");
    }
    // done eating required times: exit success (parent counts)
    _exit(0);
}
