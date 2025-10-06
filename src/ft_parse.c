#include "ft_push_swap.h"

void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

int	ft_count_split(char **split)
{
	int	count;

	count = 0;
	while (split[count])
		count++;
	return (count);
}

int	ft_parse_string_args(char *str, t_stack *a)
{
	char	**split;
	int		split_count;
	int		result;

	split = ft_split(str, ' ');
	if (!split)
		ft_error_exit();
	split_count = ft_count_split(split);
	result = ft_parse_arguments(split_count + 1, split - 1, a);
	if (!result)
	{
		ft_free_split(split);
		ft_stack_free(a);
		ft_error_exit();
	}
	ft_free_split(split);
	return (result);
}

int	ft_parse_normal_args(int argc, char **argv, t_stack *a)
{
	int	result;

	result = ft_parse_arguments(argc, argv, a);
	if (!result)
	{
		ft_stack_free(a);
		ft_error_exit();
	}
	return (result);
}
