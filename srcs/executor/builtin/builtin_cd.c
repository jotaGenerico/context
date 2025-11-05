#include "minishell.h"

/* Atualiza a variável PWD e OLDPWD no env_list */
static void	update_pwd_vars(t_shell *shell, char *oldpwd)
{
	char	cwd[4096];
	t_dlist	*lst;
	t_env_var *var;

	if (!getcwd(cwd, sizeof(cwd)))
		return ;

	lst = shell->env_list;
	while (lst)
	{
		var = lst->content;
		if (ft_strcmp(var->key, "OLDPWD") == 0)
		{
			free(var->value);
			var->value = ft_strdup(oldpwd);
		}
		else if (ft_strcmp(var->key, "PWD") == 0)
		{
			free(var->value);
			var->value = ft_strdup(cwd);
		}
		lst = lst->next;
	}
}

/* builtin_cd: muda diretório e atualiza env */
int	builtin_cd(char **argv, t_shell *shell)
{
	char	*path;
	char	oldpwd[4096];

	if (!argv[1] || ft_strcmp(argv[1], "~") == 0)
		path = get_env_value("HOME", shell);
	else
		path = argv[1];

	if (getcwd(oldpwd, sizeof(oldpwd)) == NULL)
		ft_strlcpy(oldpwd, "", sizeof(oldpwd));

	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	update_pwd_vars(shell, oldpwd);
	return (0);
}
