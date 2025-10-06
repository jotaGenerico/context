#include "push_swap.h"

static void	ft_push(t_stack *src, t_stack *dest)
{
	t_node	*temp;

	if (!src || !src->top)
		return ;
	temp = src->top;
	src->top = src->top->next;
	if (src->top)
		src->top->prev = NULL;
	else
		src->bottom = NULL;
	src->size--;
	if (!dest->top)
	{
		dest->top = temp;
		dest->bottom = temp;
		temp->next = NULL;
	}
	else
	{
		temp->next = dest->top;
		dest->top->prev = temp;
		dest->top = temp;
	}
	temp->prev = NULL;
	dest->size++;
}

void	pa(t_stack *a, t_stack *b)
{
	ft_push(b, a);
	write(1, "pa\n", 3);
}

void	pb(t_stack *a, t_stack *b)
{
	ft_push(a, b);
	write(1, "pb\n", 3);
}
