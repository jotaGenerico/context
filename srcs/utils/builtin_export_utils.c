#include "minishell.h"

static void	export_key_value(char *arg, t_shell *shell)
{
	char	*eq;
	char	*key;
	char	*value;

	eq = ft_strchr(arg, '=');
	key = ft_substr(arg, 0, eq - arg);
	value = ft_strdup(eq + 1);
	set_env_var(shell, key, value);
	free(key);
	free(value);
}

int	process_exports(char **argv, t_shell *shell)
{
	int		i;
	char	*eq;

	i = 1;
	while (argv[i])
	{
		eq = ft_strchr(argv[i], '=');
		if (eq)
			export_key_value(argv[i], shell);
		else
			set_env_var(shell, argv[i], "");
		i++;
	}
	return (0);
}

int	builtin_export(char **argv, t_shell *shell)
{
	if (!argv[1])
		return (print_all_env(shell));
	return (process_exports(argv, shell));
}
