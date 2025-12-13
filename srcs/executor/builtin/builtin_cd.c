/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgagliar <kgagliar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:57:13 by kgagliar          #+#    #+#             */
/*   Updated: 2025/12/01 15:57:15 by kgagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_target_path(char **argv, t_shell *shell, int *should_free);
static void	update_working_dirs(t_shell *shell, char *old_cwd);

int	builtin_cd(char **argv, t_shell *shell)
{
	char	*path;
	char	*old_cwd;
	int		should_free;
	int		ret;

	if (argv[1] && argv[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (1);
	}
	should_free = 0;
	path = get_target_path(argv, shell, &should_free);
	if (!path)
		return (1);
	old_cwd = getcwd(NULL, 0);
	ret = chdir(path);
	if (ret == 0)
		update_working_dirs(shell, old_cwd);
	else
		perror("minishell: cd");
	if (should_free)
		free(path);
	free(old_cwd);
	return (ret != 0);
}

static char	*get_target_path(char **argv, t_shell *shell, int *should_free)
{
	char	*env_val;

	if (!argv[1] || ft_strcmp(argv[1], "~") == 0)
	{
		env_val = get_env_value("HOME", shell);
		if (!env_val)
			ft_putendl_fd("minishell: cd: HOME not set", 2);
		return (env_val);
	}
	if (ft_strcmp(argv[1], "-") == 0)
	{
		env_val = get_env_value("OLDPWD", shell);
		if (!env_val)
		{
			ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
			return (NULL);
		}
		ft_putendl_fd(env_val, 1);
		*should_free = 1;
		return (ft_strdup(env_val));
	}
	return (argv[1]);
}

static void	update_working_dirs(t_shell *shell, char *old_cwd)
{
	char	*new_cwd;

	new_cwd = getcwd(NULL, 0);
	if (!new_cwd)
	{
		ft_putendl_fd("cd: error retrieving current directory: "
			"getcwd: cannot access parent directories: "
			"No such file or directory", 2);
		new_cwd = ft_strdup("");
	}
	if (old_cwd)
		set_env_var(shell, "OLDPWD", old_cwd);
	set_env_var(shell, "PWD", new_cwd);
	free(new_cwd);
}
