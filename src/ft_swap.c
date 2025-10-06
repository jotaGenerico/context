/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 22:58:32 by jose-cad          #+#    #+#             */
/*   Updated: 2025/09/08 22:58:34 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap(t_dlist **stack)
{
	t_content	*first;
	t_content	*second;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	first = (t_content *)(*stack)->content;
	second = (t_content *)(*stack)->next->content;
	if (!first || !second)
		return ;
	first->value ^= second->value;
	second->value ^= first->value;
	first->value ^= second->value;
	first->index ^= second->index;
	second->index ^= first->index;
	first->index ^= second->index;
}

void	sa(t_dlist **stack_a)
{
	swap(stack_a);
	ft_printf("sa\n");
}

void	sb(t_dlist **stack_b)
{
	swap(stack_b);
	ft_printf("sb\n");
}

void	ss(t_dlist **stack_a, t_dlist **stack_b)
{
	swap(stack_a);
	swap(stack_b);
	ft_printf("ss\n");
}
