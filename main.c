#include "ft_push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	a;
	t_stack	b;

	if (argc < 2)
		return (0);
	ft_stack_init(&a);
	ft_stack_init(&b);
	if (argc == 2 && ft_strchr(argv[1], ' '))
		ft_parse_string_args(argv[1], &a);
	else
		ft_parse_normal_args(argc, argv, &a);
	if (!ft_stack_is_sorted(&a))
		ft_push_swap(&a, &b);
	ft_stack_free(&a);
	ft_stack_free(&b);
	return (0);
}

