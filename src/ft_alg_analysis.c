#include "ft_push_swap.h"

void	ft_current_index(t_stack *stack)
{
	t_node	*node;
	int		i;
	int		median;

	i = 0;
	if (!stack->top)
		return ;
	median = stack->size / 2;
	node = stack->top;
	while (node)
	{
		node->index = i;
		if (i <= median)
			node->above_median = 1;
		else
			node->above_median = 0;
		node = node->next;
		++i;
	}
}

void	ft_cost_analysis_a(t_stack *a, t_stack *b)
{
	t_node	*node;

	node = b->top;
	while (node)
	{
		node->push_cost = node->index;
		if (!(node->above_median))
			node->push_cost = b->size - (node->index);
		if (node->target_node->above_median)
			node->push_cost += node->target_node->index;
		else
			node->push_cost += a->size - (node->target_node->index);
		node = node->next;
	}
}

void	ft_set_cheapest(t_stack *stack)
{
	long	cheapest_value;
	t_node	*cheapest_node;
	t_node	*node;

	if (!stack->top)
		return ;
	cheapest_value = LONG_MAX;
	node = stack->top;
	while (node)
	{
		node->cheapest = 0;
		node = node->next;
	}
	node = stack->top;
	while (node)
	{
		if (node->push_cost < cheapest_value)
		{
			cheapest_value = node->push_cost;
			cheapest_node = node;
		}
		node = node->next;
	}
	cheapest_node->cheapest = 1;
}

void	ft_cost_analysis_b(t_stack *a, t_stack *b)
{
	t_node	*node;

	node = a->top;
	while (node)
	{
		node->push_cost = node->index;
		if (!(node->above_median))
			node->push_cost = a->size - (node->index);
		if (node->target_node && node->target_node->above_median)
			node->push_cost += node->target_node->index;
		else if (node->target_node)
			node->push_cost += b->size - (node->target_node->index);
		node = node->next;
	}
}
