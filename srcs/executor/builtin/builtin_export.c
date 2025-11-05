#include "minishell.h"

/* Encontra uma variável no env_list */
static t_env_var	*find_env_var(t_shell *shell, const char *key)
{
	t_dlist		*lst;
	t_env_var	*var;

	lst = shell->env_list;
	while (lst)
	{
		var = lst->content;
		if (ft_strcmp(var->key, key) == 0)
			return (var);
		lst = lst->next;
	}
	return (NULL);
}

/* Adiciona ou atualiza variável de ambiente */
static void	set_env_var(t_shell *shell, char *key, char *value)
{
	t_env_var	*var;

	var = find_env_var(shell, key);
	if (var)
	{
		free(var->value);
		var->value = ft_strdup(value);
	}
	else
	{
		t_env_var *new = malloc(sizeof(t_env_var));
		new->key = ft_strdup(key);
		new->value = ft_strdup(value);
		ft_dlstadd_back(&shell->env_list, ft_dlstnew(new));
	}
}

/* builtin_export: adiciona variáveis de ambiente */
int	builtin_export(char **argv, t_shell *shell)
{
	int		i;
	char	*eq;
	char	*key;
	char	*value;

	if (!argv[1])
	{
		t_dlist	*lst = shell->env_list;
		while (lst)
		{
			t_env_var *var = lst->content;
			ft_printf("declare -x %s=\"%s\"\n", var->key, var->value);
			lst = lst->next;
		}
		return (0);
	}
	i = 1;
	while (argv[i])
	{
		eq = ft_strchr(argv[i], '=');
		if (eq)
		{
			key = ft_substr(argv[i], 0, eq - argv[i]);
			value = ft_strdup(eq + 1);
			set_env_var(shell, key, value);
			free(key);
			free(value);
		}
		else
			set_env_var(shell, argv[i], "");
		i++;
	}
	return (0);
}
