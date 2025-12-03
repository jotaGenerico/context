/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_glob_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgagliar <kgagliar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:03:27 by kgagliar          #+#    #+#             */
/*   Updated: 2025/12/01 16:03:28 by kgagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_glob_match(const char *pattern, const char *text)
{
	if (*pattern == '\0' && *text == '\0')
		return (1);
	if (*pattern == '*')
	{
		if (is_glob_match(pattern + 1, text))
			return (1);
		if (*text != '\0')
			return (is_glob_match(pattern, text + 1));
		return (0);
	}
	if (*text == '\0')
		return (0);
	if (*pattern == *text)
		return (is_glob_match(pattern + 1, text + 1));
	return (0);
}

t_list	*get_glob_matches(char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	t_list			*matches;

	matches = NULL;
	dir = opendir(".");
	if (!dir)
		return (NULL);
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (entry->d_name[0] == '.' && pattern[0] != '.')
			continue ;
		if (is_glob_match(pattern, entry->d_name))
			ft_lstadd_back(&matches, ft_lstnew(ft_strdup(entry->d_name)));
	}
	closedir(dir);
	return (matches);
}
