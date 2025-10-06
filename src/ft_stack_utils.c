#include "libft.h"

t_node	*ft_create_node(int	value)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->value = value;
	new_node->index = -1;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	ft_add_node_back(t_stack *stack, t_node *new_node)
{
	if (!stack || !new_node)
		return ;
	if (stack->size == 0)
	{
		stack->top = new_node;
		stack->base = new_node;
	}
	else
	{
		stack->base->next = new_node;
		new_node->prev = stack->base;
		stack->base = new_node;
	}
	stack->size++;
}
