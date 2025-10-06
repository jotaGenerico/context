#include "ft_push_swap.h"

void	ft_stack_init(t_stack *stack)
{
	stack->top = NULL;
	stack->size = 0;
}

void	ft_stack_push(t_stack *stack, int value)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		ft_error_exit();
	new_node->value = value;
	new_node->index = 0;
	new_node->push_cost = 0;
	new_node->above_median = 0;
	new_node->target_node = NULL;
	new_node->next = stack->top;
	new_node->prev = NULL;
	if (stack->top)
		stack->top->prev = new_node;
	stack->top = new_node;
	stack->size++;
}

int	ft_stack_pop(t_stack *stack)
{
	t_node	*node;
	int		value;

	if (!stack->top)
		ft_error_exit();
	node = stack->top;
	value = node->value;
	stack->top = node->next;
	if (stack->top)
		stack->top->prev = NULL;
	free(node);
	stack->size--;
	return (value);
}

void	ft_stack_free(t_stack *stack)
{
	t_node	*current;
	t_node	*next;

	current = stack->top;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	stack->top = NULL;
	stack->size = 0;
}
