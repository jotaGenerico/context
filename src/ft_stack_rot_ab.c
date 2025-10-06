#include "ft_push_swap.h"

void	ra(t_stack *a, int print)
{
	t_node	*first;
	t_node	*last;

	if (a->size < 2)
		return ;
	first = a->top;
	a->top = first->next;
	a->top->prev = NULL;
	last = a->top;
	while (last->next)
		last = last->next;
	last->next = first;
	first->prev = last;
	first->next = NULL;
	if (print)
		write(1, "ra\n", 3);
}

void	rb(t_stack *b, int print)
{
	t_node	*first;
	t_node	*last;

	if (b->size < 2)
		return ;
	first = b->top;
	b->top = first->next;
	b->top->prev = NULL;
	last = b->top;
	while (last->next)
		last = last->next;
	last->next = first;
	first->prev = last;
	first->next = NULL;
	if (print)
		write(1, "rb\n", 3);
}

void	rra(t_stack *a, int print)
{
	t_node	*last;
	t_node	*second_last;

	if (a->size < 2)
		return ;
	last = a->top;
	while (last->next)
		last = last->next;
	second_last = last->prev;
	second_last->next = NULL;
	last->prev = NULL;
	last->next = a->top;
	a->top->prev = last;
	a->top = last;
	if (print)
		write(1, "rra\n", 4);
}

void	rrb(t_stack *b, int print)
{
	t_node	*last;
	t_node	*second_last;

	if (b->size < 2)
		return ;
	last = b->top;
	while (last->next)
		last = last->next;
	second_last = last->prev;
	second_last->next = NULL;
	last->prev = NULL;
	last->next = b->top;
	b->top->prev = last;
	b->top = last;
	if (print)
		write(1, "rrb\n", 4);
}
