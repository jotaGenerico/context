#include "../includes/philo_bonus.h"

long get_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

long get_elapsed_time(long start_time)
{
    return get_time() - start_time;
}

void precise_usleep(long ms)
{
    long start = get_time();
    while (get_time() - start < ms)
        usleep(100);
}
