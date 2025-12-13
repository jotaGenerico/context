/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:02:42 by jose-cad          #+#    #+#             */
/*   Updated: 2025/12/01 16:02:43 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dlstclear(t_dlist **lst, void (*del)(void *))
{
	t_dlist	*current;
	t_dlist	*next;

	if (!lst || !*lst)
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		if (del)
			del(current->content);
		free(current);
		current = next;
	}
	*lst = NULL;
}

void	free_tokens(void *content)
{
	t_token	*token;

	if (!content)
		return ;
	token = (t_token *)content;
	free(token->value);
	free(token);
}
