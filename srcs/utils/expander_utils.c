#include "minishell.h"

int	get_var_name_len(char *str)
{
	int	i;

	if (str[0] == '?')
		return (1);
	i = 0;
	while (str[i] && ft_isalnum_or_underscore(str[i]))
		i++;
	return (i);
}

char	**ft_lst_to_array(t_list *list)
{
	char	**array;
	int		len;
	int		i;
	t_list	*current;

	len = ft_lstsize(list);
	array = (char **)ft_calloc(len + 1, sizeof(char *));
	if (!array)
		return (NULL);
	current = list;
	i = 0;
	while (current)
	{
		array[i] = (char *)current->content;
		current->content = NULL;
		current = current->next;
		i++;
	}
	return (array);
}
