#include "ft_push_swap.h"

void	sa(t_stack *a, int print)
{
	t_node	*first;
	t_node	*second;

	if (a->size < 2)
		return ;
	first = a->top;
	second = first->next;
	first->next = second->next;
	if (second->next)
		second->next->prev = first;
	second->prev = NULL;
	second->next = first;
	first->prev = second;
	a->top = second;
	if (print)
		write(1, "sa\n", 3);
}

void	sb(t_stack *b, int print)
{
	t_node	*first;
	t_node	*second;

	if (b->size < 2)
		return ;
	first = b->top;
	second = first->next;
	first->next = second->next;
	if (second->next)
		second->next->prev = first;
	second->prev = NULL;
	second->next = first;
	first->prev = second;
	b->top = second;
	if (print)
		write(1, "sb\n", 3);
}

void	ss(t_stack *a, t_stack *b, int print)
{
	sa(a, 0);
	sb(b, 0);
	if (print)
		write(1, "ss\n", 3);
}

void	pa(t_stack *a, t_stack *b, int print)
{
	t_node	*node;

	if (b->size == 0)
		return ;
	node = b->top;
	b->top = node->next;
	if (b->top)
		b->top->prev = NULL;
	b->size--;
	node->next = a->top;
	if (a->top)
		a->top->prev = node;
	node->prev = NULL;
	a->top = node;
	a->size++;
	if (print)
		write(1, "pa\n", 3);
}

void	pb(t_stack *a, t_stack *b, int print)
{
	t_node	*node;

	if (a->size == 0)
		return ;
	node = a->top;
	a->top = node->next;
	if (a->top)
		a->top->prev = NULL;
	a->size--;
	node->next = b->top;
	if (b->top)
		b->top->prev = node;
	node->prev = NULL;
	b->top = node;
	b->size++;
	if (print)
		write(1, "pb\n", 3);
}
