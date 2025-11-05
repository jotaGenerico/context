/* ************************************************************************** */
/* env_utils.c                               */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/* ENVIRONMENT UTILITIES                              */
/* ************************************************************************** */

// FUNÇÃO 1/5: Converte a lista encadeada do ambiente para um array de char **
char	**env_list_to_array(t_dlist *env_list)
{
	char	**envp;
	t_dlist	*curr;
	int		count;
	int		i;
	t_env_var	*var;

	count = ft_dlstsize(env_list);
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	curr = env_list;
	i = 0;
	while (curr)
	{
		var = curr->content;
		// ft_strjoin3(str1, str2, str3) deve ser sua função libft
		envp[i] = ft_strjoin3(var->key, "=", var->value);
		if (!envp[i])
		{
			while (i > 0)
				free(envp[--i]);
			free(envp);
			return (NULL);
		}
		curr = curr->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

// FUNÇÃO 2/5: Libera a memória de um array de strings
void	free_char_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

// FUNÇÃO 3/5: Busca o valor de uma variável de ambiente pelo nome
char	*get_env_value(char *key, t_shell *shell)
{
	t_dlist		*curr;
	t_env_var	*var;

	curr = shell->env_list;
	while (curr)
	{
		var = curr->content;
		if (ft_strcmp(var->key, key) == 0)
			return (var->value);
		curr = curr->next;
	}
	return (NULL);
}

static t_dlist	*find_env_var(t_dlist *list, char *key)
{
	t_dlist		*curr;
	t_env_var	*var;

	curr = list;
	while (curr)
	{
		var = (t_env_var *)curr->content;
		// ft_strcmp da libft
		if (ft_strcmp(var->key, key) == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

/*
 * FUNÇÃO COMPLETA: env_list_set_var (INCLUI CORREÇÃO DE LEAK)
 * Adiciona ou atualiza uma variável de ambiente na lista.
 * Retorna 0 em caso de sucesso, 1 em caso de falha de alocação.
 */
int	env_list_set_var(t_dlist **env_list, char *assignment)
{
	char		*equal_sign;
	char		*key;
	t_dlist		*node;
	t_env_var	*var_to_update;
	t_env_var	*new_var;

	// 1. Extrai a KEY
	equal_sign = ft_strchr(assignment, '=');
	if (!equal_sign)
		return (1);

	key = ft_substr(assignment, 0, equal_sign - assignment);
	if (!key)
		return (1);

	// 2. Busca a variável
	node = find_env_var(*env_list, key);
	free(key);

	if (node)
	{
		// 3. UPDATE: Variável existente (CORREÇÃO CRÍTICA DE LEAK AQUI)
		var_to_update = (t_env_var *)node->content;

		char *old_value = var_to_update->value;

		// Tenta alocar o novo valor
		var_to_update->value = ft_strdup(equal_sign + 1);
		if (!var_to_update->value)
		{
			// Falha de malloc: Restaura o valor antigo para evitar perda
			var_to_update->value = old_value;
			return (1);
		}
		// Sucesso: Libera o valor antigo
		if (old_value)
			free(old_value);
	}
	else
	{
		// 4. ADD: Nova variável (create_env_var deve estar no init.c)
		new_var = create_env_var(assignment);
		if (!new_var)
			return (1);

		ft_dlstadd_back(env_list, ft_dlstnew(new_var));
	}

	return (0);
}
