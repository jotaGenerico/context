#include "../includes/philo.h"
#include <signal.h>

/* Global pointer so the signal handler can access the table */
static t_table *g_table = NULL;

/* Signal handler: clean up resources then exit */
static void sig_handler(int signum)
{
    (void)signum;
    if (g_table)
        cleanup(g_table);
    _exit(0);
}

int main(int ac, char **av)
{
    t_table table;

    if (ac != 5 && ac != 6)
    {
        error_exit("Usage: ./philo nb_philos time_die time_eat time_sleep [must_eat]");
        return (1);
    }
    if (parse_args(ac, av, &table.data) != 0)
        return (1);
    if (init_table(&table) != 0)
        return (1);
    /* Store pointer for the handler and install it */
    g_table = &table;
    signal(SIGINT, sig_handler);
    signal(SIGTERM, sig_handler);
    start_simulation(&table);
    cleanup(&table);
    return (0);
}
