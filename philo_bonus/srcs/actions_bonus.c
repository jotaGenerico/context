#include "philo_bonus.h"

void	sleep_action(t_state *m)
{
	print_status(m, e_sleeping);
	wait_until(get_time_ms() + m->p->time_to_sleep);
}

void	think(t_state *m)
{
	print_status(m, e_thinking);
}

void	die(t_state *m)
{
	print_status(m, e_dead);
}
