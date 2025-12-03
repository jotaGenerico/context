/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgagliar <kgagliar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:03:32 by kgagliar          #+#    #+#             */
/*   Updated: 2025/12/01 16:03:34 by kgagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_var_name_len(char *str)
{
	int	i;

	if (str[0] == '?')
		return (1);
	i = 0;
	while (str[i] && ft_isalnum_or_underscore(str[i]))
		i++;
	return (i);
}

char	**ft_lst_to_array(t_list *list)
{
	char	**array;
	int		len;
	int		i;
	t_list	*current;

	len = ft_lstsize(list);
	array = (char **)ft_calloc(len + 1, sizeof(char *));
	if (!array)
		return (NULL);
	current = list;
	i = 0;
	while (current)
	{
		array[i] = (char *)current->content;
		current->content = NULL;
		current = current->next;
		i++;
	}
	return (array);
}

int	should_expand_wildcards(char **argv, int *argv_quoted)
{
	int	i;

	if (!argv || !argv_quoted)
		return (0);
	i = 0;
	while (argv[i])
	{
		if (ft_strchr(argv[i], '*') && !argv_quoted[i])
			return (1);
		i++;
	}
	return (0);
}
