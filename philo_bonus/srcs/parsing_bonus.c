#include "../includes/philo_bonus.h"

static int is_valid_number(char *str)
{
    int i = 0;
    if (str[i] == '+') i++;
    if (!str[i]) return 0;
    while (str[i]) {
        if (str[i] < '0' || str[i] > '9') return 0;
        i++;
    }
    return 1;
}

static int validate_args(t_data *data)
{
    if (data->nb_philos < 1 || data->nb_philos > 200)
        return error_exit("Number of philosophers must be between 1 and 200"), 1;
    if (data->time_to_die < 60)
        return error_exit("time_to_die must be at least 60ms"), 1;
    if (data->time_to_eat < 60)
        return error_exit("time_to_eat must be at least 60ms"), 1;
    if (data->time_to_sleep < 60)
        return error_exit("time_to_sleep must be at least 60ms"), 1;
    if (data->must_eat_count == 0)
        return error_exit("must_eat_count must be positive or omitted"), 1;
    return 0;
}

int parse_args_bonus(int ac, char **av, t_data *data)
{
    int i = 1;
    while (i < ac) {
        if (!is_valid_number(av[i]))
            return error_exit("Invalid argument: must be positive number"), 1;
        i++;
    }
    data->nb_philos = ft_atoi(av[1]);
    data->time_to_die = ft_atoi(av[2]);
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep = ft_atoi(av[4]);
    data->must_eat_count = (ac == 6) ? ft_atoi(av[5]) : -1;
    data->start_time = 0;
    data->pids = NULL;
    if (validate_args(data) != 0)
        return 1;
    return 0;
}

int ft_atoi(const char *str)
{
    int result = 0;
    int sign = 1;
    while (*str == ' ' || (*str >= 9 && *str <= 13)) str++;
    if (*str == '-' || *str == '+') {
        if (*str == '-') sign = -1;
        str++;
    }
    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }
    return result * sign;
}
