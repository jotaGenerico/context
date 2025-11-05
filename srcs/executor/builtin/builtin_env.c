#include "minishell.h"

int	builtin_env(t_shell *shell)
{
	t_dlist	*lst;
	t_env_var *var;

	lst = shell->env_list;
	while (lst)
	{
		var = lst->content;
		if (var->value)
			ft_printf("%s=%s\n", var->key, var->value);
		lst = lst->next;
	}
	return (0);
}
