/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgagliar <kgagliar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:00:00 by kgagliar          #+#    #+#             */
/*   Updated: 2025/12/01 16:00:03 by kgagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*return_path_and_free(char **path_dirs, char *path);
static char	*search_path_dirs(char **path_dirs, const char *cmd);
int			is_directory(const char *path);

char	*find_command_path(const char *cmd, t_shell *shell)
{
	char	*path_var;
	char	**path_dirs;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_var = get_env_value("PATH", shell);
	if (!path_var)
		return (NULL);
	path_dirs = ft_split(path_var, ':');
	if (!path_dirs)
		return (NULL);
	return (search_path_dirs(path_dirs, cmd));
}

int	is_directory(const char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
		return (1);
	return (0);
}

static char	*return_path_and_free(char **path_dirs, char *path)
{
	free_char_array(path_dirs);
	return (path);
}

static char	*search_path_dirs(char **path_dirs, const char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (path_dirs[i])
	{
		full_path = ft_strjoin3(path_dirs[i], "/", cmd);
		if (!full_path)
			return (return_path_and_free(path_dirs, NULL));
		if (access(full_path, X_OK) == 0 && !is_directory(full_path))
			return (return_path_and_free(path_dirs, full_path));
		free(full_path);
		i++;
	}
	return (return_path_and_free(path_dirs, NULL));
}
