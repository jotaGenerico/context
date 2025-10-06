#include "ft_push_swap.h"

void	ft_push_swap(t_stack *a, t_stack *b)
{
	if (a->size == 2)
		sa(a, 1);
	else if (a->size == 3)
		ft_sort_three(a);
	else
		ft_sort_stacks(a, b);
}

void	ft_sort_three(t_stack *a)
{
	t_node	*biggest;

	biggest = ft_find_max(a);
	if (biggest == a->top)
		ra(a, 1);
	else if (biggest == a->top->next)
		rra(a, 1);
	if (a->top->value > a->top->next->value)
		sa(a, 1);
}

void	ft_sort_stacks(t_stack *a, t_stack *b)
{
	if (a->size > 3 && !ft_stack_is_sorted(a))
		pb(a, b, 1);
	if (a->size > 3 && !ft_stack_is_sorted(a))
		pb(a, b, 1);
	while (a->size > 3 && !ft_stack_is_sorted(a))
	{
		ft_init_nodes_b(a, b);
		ft_move_a_to_b(a, b);
	}
	ft_sort_three(a);
	while (b->size > 0)
	{
		ft_init_nodes_a(a, b);
		ft_move_b_to_a(a, b);
	}
	ft_current_index(a);
	ft_min_on_top(a);
}

void	ft_error_exit(void)
{
	write(2, "Error\n", 6);
	exit(1);
}
