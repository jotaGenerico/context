#include "ft_push_swap.h"

int	ft_stack_is_sorted(t_stack *a)
{
	t_node	*node;

	if (!a->top)
		return (1);
	node = a->top;
	while (node->next)
	{
		if (node->value > node->next->value)
			return (0);
		node = node->next;
	}
	return (1);
}

t_node	*ft_find_min(t_stack *stack)
{
	t_node	*min;
	t_node	*node;

	if (!stack->top)
		return (NULL);
	min = stack->top;
	node = stack->top;
	while (node)
	{
		if (node->value < min->value)
			min = node;
		node = node->next;
	}
	return (min);
}

t_node	*ft_find_max(t_stack *stack)
{
	t_node	*max;
	t_node	*node;

	if (!stack->top)
		return (NULL);
	max = stack->top;
	node = stack->top;
	while (node)
	{
		if (node->value > max->value)
			max = node;
		node = node->next;
	}
	return (max);
}
