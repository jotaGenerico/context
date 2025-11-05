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
