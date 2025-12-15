/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_or.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:01:51 by jose-cad          #+#    #+#             */
/*   Updated: 2025/12/01 16:01:52 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_node_type	get_operator_type(t_token *token);
static t_ast		*create_operator_node(t_ast *left, t_dlist **tokens);

t_ast	*parse_and_or(t_dlist **tokens)
{
	t_ast	*left;
	t_ast	*new_node;
	t_token	*token;

	left = parse_pipeline(tokens);
	if (!left)
		return (NULL);
	while (*tokens)
	{
		token = (*tokens)->content;
		if (token->type != TOKEN_AND && token->type != TOKEN_OR)
			break ;
		new_node = create_operator_node(left, tokens);
		if (!new_node)
			return (NULL);
		left = new_node;
	}
	return (left);
}

static t_node_type	get_operator_type(t_token *token)
{
	if (token->type == TOKEN_AND)
		return (NODE_AND);
	return (NODE_OR);
}

static t_ast	*create_operator_node(t_ast *left, t_dlist **tokens)
{
	t_ast		*right;
	t_node_type	type;
	t_token		*token;

	token = (*tokens)->content;
	type = get_operator_type(token);
	*tokens = (*tokens)->next;
	right = parse_pipeline(tokens);
	if (!right)
	{
		ast_free(left);
		return (NULL);
	}
	return (ast_new_node(type, left, right));
}
