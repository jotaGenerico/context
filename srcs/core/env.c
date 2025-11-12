#include "minishell.h"

static void	env_array_cleanup(char **envp, int i);
static int	convert_node_to_string(t_dlist *curr, char **envp, int i);

char	**env_list_to_array(t_dlist *env_list)
{
	char	**envp;
	t_dlist	*curr;
	int		count;
	int		i;

	count = ft_dlstsize(env_list);
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	curr = env_list;
	i = 0;
	while (curr)
	{
		if (convert_node_to_string(curr, envp, i) != 0)
			return (NULL);
		curr = curr->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

static void	env_array_cleanup(char **envp, int i)
{
	while (i > 0)
		free(envp[--i]);
	free(envp);
}

static int	convert_node_to_string(t_dlist *curr, char **envp, int i)
{
	t_env_var	*var;
	char		*temp;

	var = curr->content;
	temp = ft_strjoin3(var->key, "=", var->value);
	if (!temp)
	{
		env_array_cleanup(envp, i);
		return (1);
	}
	envp[i] = temp;
	return (0);
}
