#include "ft_push_swap.h"

t_node	*ft_find_target_node(t_stack *a, t_node *current_b)
{
	t_node	*target;
	t_node	*current_a;
	long	best_match_value;

	best_match_value = LONG_MAX;
	target = NULL;
	current_a = a->top;
	while (current_a)
	{
		if (current_a->value > current_b->value
			&& current_a->value < best_match_value)
		{
			best_match_value = current_a->value;
			target = current_a;
		}
		current_a = current_a->next;
	}
	if (target)
		return (target);
	return (ft_find_min(a));
}

void	ft_set_target_a(t_stack *a, t_stack *b)
{
	t_node	*current_b;

	current_b = b->top;
	while (current_b)
	{
		current_b->target_node = ft_find_target_node(a, current_b);
		current_b = current_b->next;
	}
}

t_node	*ft_find_target_node_b(t_stack *b, t_node *current_a)
{
	t_node	*target;
	t_node	*current_b;
	long	best_match_value;

	best_match_value = LONG_MIN;
	target = NULL;
	current_b = b->top;
	while (current_b)
	{
		if (current_b->value < current_a->value
			&& current_b->value > best_match_value)
		{
			best_match_value = current_b->value;
			target = current_b;
		}
		current_b = current_b->next;
	}
	if (target)
		return (target);
	return (ft_find_max(b));
}

void	ft_set_target_b(t_stack *a, t_stack *b)
{
	t_node	*current_a;

	current_a = a->top;
	while (current_a)
	{
		current_a->target_node = ft_find_target_node_b(b, current_a);
		current_a = current_a->next;
	}
}
