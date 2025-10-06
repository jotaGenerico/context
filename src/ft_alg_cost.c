#include "ft_push_swap.h"

void	ft_init_nodes_a(t_stack *a, t_stack *b)
{
	ft_current_index(a);
	ft_current_index(b);
	ft_set_target_a(a, b);
	ft_cost_analysis_a(a, b);
	ft_set_cheapest(b);
}

void	ft_init_nodes_b(t_stack *a, t_stack *b)
{
	ft_current_index(a);
	ft_current_index(b);
	ft_set_target_b(a, b);
	ft_cost_analysis_b(a, b);
	ft_set_cheapest(a);
}
