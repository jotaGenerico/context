/* ************************************************************************** */
/* executor_utils.c                              */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/* FD SAVE / RESTORE                              */
/* ************************************************************************** */

int	save_std_fds(int *sv_in, int *sv_out, int *sv_err)
{
	*sv_in = dup(STDIN_FILENO);
	*sv_out = dup(STDOUT_FILENO);
	*sv_err = dup(STDERR_FILENO);
	if (*sv_in == -1 || *sv_out == -1 || *sv_err == -1)
	{
		perror("dup");
		if (*sv_in >= 0)
			close(*sv_in);
		if (*sv_out >= 0)
			close(*sv_out);
		if (*sv_err >= 0)
			close(*sv_err);
		return (-1);
	}
	return (0);
}

void	restore_std_fds(int sv_in, int sv_out, int sv_err)
{
	if (sv_in >= 0)
	{
		dup2(sv_in, STDIN_FILENO);
		close(sv_in);
	}
	if (sv_out >= 0)
	{
		dup2(sv_out, STDOUT_FILENO);
		close(sv_out);
	}
	if (sv_err >= 0)
	{
		dup2(sv_err, STDERR_FILENO);
		close(sv_err);
	}
}

/* ************************************************************************** */
/* COMMAND PATH FINDER                                                        */
/* ************************************************************************** */

/* Helper global — mantém */
bool	is_directory(const char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
		return (true);
	return (false);
}

/* -------------------------------------------------------------------------- */
/* Encontra o caminho completo de um comando                                 */
/* -------------------------------------------------------------------------- */
char	*find_command_path(const char *cmd, t_shell *shell)
{
	char	*path_var;
	char	**path_dirs;
	char	*full_path;
	int		i;

	/* Caso contenha '/', verifica diretamente */
	if (ft_strchr(cmd, '/'))
	{
		/* ⚠️ NÃO BLOQUEIA DIRETÓRIO AQUI — child_exec decide */
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}

	/* Busca no PATH */
	path_var = get_env_value("PATH", shell);
	if (!path_var)
		return (NULL);
	path_dirs = ft_split(path_var, ':');
	if (!path_dirs)
		return (NULL);

	i = 0;
	while (path_dirs[i])
	{
		full_path = ft_strjoin3(path_dirs[i], "/", cmd);
		if (!full_path)
			return (free_char_array(path_dirs), NULL);
		if (access(full_path, X_OK) == 0 && !is_directory(full_path))
			return (free_char_array(path_dirs), full_path);
		free(full_path);
		i++;
	}
	free_char_array(path_dirs);
	return (NULL);
}
