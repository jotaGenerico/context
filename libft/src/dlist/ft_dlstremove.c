/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstremove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 21:36:46 by jose-cad          #+#    #+#             */
/*   Updated: 2025/11/01 23:35:10 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstremove(t_dlist **head, t_dlist *to_remove, void (*del)(void *))
{
	if (!head || !*head || !to_remove)
		return ;
	if (to_remove->next)
		to_remove->next->prev = to_remove->prev;
	if (to_remove->prev)
		to_remove->prev->next = to_remove->next;
	if (*head == to_remove)
		*head = to_remove->next;
	ft_dlstdelone(to_remove, del);
}
