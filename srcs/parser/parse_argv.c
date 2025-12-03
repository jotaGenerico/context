/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgagliar <kgagliar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:01:56 by kgagliar          #+#    #+#             */
/*   Updated: 2025/12/01 16:01:58 by kgagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_argv(char **argv);
static int	*alloc_quoted_array(int size, char **argv);
static void	copy_argv_data(char **new_argv, int *new_quoted,
				char **argv, int *quoted);

char	**argv_add(char **argv, char *new_word)
{
	int		count;
	char	**new_argv;

	count = count_argv(argv);
	new_argv = malloc(sizeof(char *) * (count + 2));
	if (!new_argv)
		return (NULL);
	copy_argv_data(new_argv, NULL, argv, NULL);
	new_argv[count] = ft_strdup(new_word);
	new_argv[count + 1] = NULL;
	free(argv);
	return (new_argv);
}

char	**argv_add_quoted(char **argv, char *new_word,
			int **quoted, int is_quoted)
{
	int		count;
	char	**new_argv;
	int		*new_quoted;

	count = count_argv(argv);
	new_argv = malloc(sizeof(char *) * (count + 2));
	if (!new_argv)
		return (NULL);
	new_quoted = alloc_quoted_array(count, new_argv);
	if (!new_quoted)
		return (NULL);
	copy_argv_data(new_argv, new_quoted, argv, *quoted);
	new_argv[count] = ft_strdup(new_word);
	new_quoted[count] = is_quoted;
	new_argv[count + 1] = NULL;
	new_quoted[count + 1] = 0;
	free(argv);
	free(*quoted);
	*quoted = new_quoted;
	return (new_argv);
}

static int	count_argv(char **argv)
{
	int	count;

	count = 0;
	while (argv && argv[count])
		count++;
	return (count);
}

static void	copy_argv_data(char **new_argv, int *new_quoted,
				char **argv, int *quoted)
{
	int	i;

	i = 0;
	while (argv && argv[i])
	{
		new_argv[i] = argv[i];
		if (quoted)
			new_quoted[i] = quoted[i];
		i++;
	}
}

static int	*alloc_quoted_array(int size, char **argv)
{
	int	*new_quoted;

	new_quoted = malloc(sizeof(int) * (size + 2));
	if (!new_quoted)
	{
		free(argv);
		return (NULL);
	}
	return (new_quoted);
}
