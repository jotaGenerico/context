/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgagliar <kgagliar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:02:12 by kgagliar          #+#    #+#             */
/*   Updated: 2025/12/01 16:02:14 by kgagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ast	*create_pipe_node(t_ast *left, t_dlist **tokens);

t_ast	*parse_pipeline(t_dlist **tokens)
{
	t_ast	*left;
	t_token	*token;

	left = parse_subshell(tokens);
	if (!left)
		return (NULL);
	while (*tokens)
	{
		token = (*tokens)->content;
		if (token->type == TOKEN_PIPE)
		{
			left = create_pipe_node(left, tokens);
			if (!left)
				return (NULL);
		}
		else
			break ;
	}
	return (left);
}

static t_ast	*create_pipe_node(t_ast *left, t_dlist **tokens)
{
	t_ast	*right;

	*tokens = (*tokens)->next;
	right = parse_subshell(tokens);
	if (!right)
	{
		ast_free(left);
		return (NULL);
	}
	left = ast_new_node(NODE_PIPE, left, right);
	if (!left)
		return (NULL);
	return (left);
}
