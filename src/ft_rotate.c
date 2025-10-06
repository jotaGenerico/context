#include "push_swap.h"

static void	ft_rotate(t_stack *stack)
{
	t_node	*temp;

	if (!stack || !stack->top || stack->size < 2)
		return ;
	temp = stack->top;
	stack->top = stack->top->next;
	stack->top->prev = NULL;
	temp->next = NULL;
	temp->prev = stack->bottom;
	stack->bottom->next = temp;
	stack->bottom = temp;
}

void	ra(t_stack *a)
{
	ft_rotate(a);
	write(1, "ra\n", 3);
}

void	rb(t_stack *b)
{
	ft_rotate(b);
	write(1, "rb\n", 3);
}

void	rr(t_stack *a, t_stack *b)
{
	ft_rotate(a);
	ft_rotate(b);
	write(1, "rr\n", 3);
}
