#include "ft_push_swap.h"

t_node	*ft_get_cheapest(t_stack *stack)
{
	t_node	*node;

	if (!stack->top)
		return (NULL);
	node = stack->top;
	while (node)
	{
		if (node->cheapest)
			return (node);
		node = node->next;
	}
	return (stack->top);
}

void	ft_prep_for_push(t_stack *stack, t_node *top_node, char stack_name)
{
	while (stack->top != top_node)
	{
		if (stack_name == 'a')
		{
			if (top_node->above_median)
				ra(stack, 1);
			else
				rra(stack, 1);
		}
		else if (stack_name == 'b')
		{
			if (top_node->above_median)
				rb(stack, 1);
			else
				rrb(stack, 1);
		}
	}
}

void	ft_move_a_to_b(t_stack *a, t_stack *b)
{
	t_node	*cheapest_node;

	cheapest_node = ft_get_cheapest(a);
	if (cheapest_node && cheapest_node->target_node)
		ft_rotate_both(a, b, cheapest_node, cheapest_node->target_node);
	ft_prep_for_push(a, cheapest_node, 'a');
	if (cheapest_node && cheapest_node->target_node)
		ft_prep_for_push(b, cheapest_node->target_node, 'b');
	pb(a, b, 1);
}

void	ft_move_b_to_a(t_stack *a, t_stack *b)
{
	t_node	*cheapest_node;

	cheapest_node = ft_get_cheapest(b);
	if (cheapest_node && cheapest_node->target_node)
		ft_rotate_both(a, b, cheapest_node->target_node, cheapest_node);
	ft_prep_for_push(b, cheapest_node, 'b');
	ft_prep_for_push(a, cheapest_node->target_node, 'a');
	pa(a, b, 1);
}

void	ft_min_on_top(t_stack *a)
{
	while (a->top != ft_find_min(a))
	{
		if (ft_find_min(a)->above_median)
			ra(a, 1);
		else
			rra(a, 1);
	}
}
