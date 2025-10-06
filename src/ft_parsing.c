#include "ft_push_swap.h"

int	ft_parse_arguments(int argc, char **argv, t_stack *a)
{
	int		i;
	long	num;

	i = argc - 1;
	while (i >= 1)
	{
		if (!ft_is_valid_number(argv[i]))
			return (0);
		num = ft_atol(argv[i]);
		if (num > INT_MAX || num < INT_MIN)
			return (0);
		ft_stack_push(a, (int)num);
		i--;
	}
	if (ft_has_duplicates(a))
		return (0);
	return (1);
}

int	ft_is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_has_duplicates(t_stack *a)
{
	t_node	*current;
	t_node	*check;

	current = a->top;
	while (current)
	{
		check = current->next;
		while (check)
		{
			if (current->value == check->value)
				return (1);
			check = check->next;
		}
		current = current->next;
	}
	return (0);
}
