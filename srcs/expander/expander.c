/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:01:14 by jose-cad          #+#    #+#             */
/*   Updated: 2025/12/01 16:01:16 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_variables(char **argv, t_shell *shell)
{
	int		i;
	char	*expanded_word;

	i = 0;
	while (argv[i])
	{
		expanded_word = expand_word(argv[i], shell);
		if (!expanded_word)
			return ;
		free(argv[i]);
		argv[i] = expanded_word;
		i++;
	}
}
