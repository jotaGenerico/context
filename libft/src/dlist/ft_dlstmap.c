/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 00:12:00 by jose-cad          #+#    #+#             */
/*   Updated: 2025/09/09 00:12:00 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlstmap(t_dlist *lst, void *(*f)(void *), void (*del)(void *))
{
	t_dlist	*new_list;
	t_dlist	*new_node;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new_node = ft_dlstnew(f(lst->content));
		if (!new_node)
		{
			ft_dlstclear(&new_list, del);
			return (NULL);
		}
		ft_dlstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}
