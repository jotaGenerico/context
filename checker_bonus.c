#include "./include/ft_push_swap.h"
#include "./libft/include/libft.h"

static int	ft_exec_swap_push(char *line, t_stack *a, t_stack *b);
static int	ft_exec_rotate(char *line, t_stack *a, t_stack *b);
static int	ft_exec_rev_rotate(char *line, t_stack *a, t_stack *b);
static void	ft_read_and_execute_operations(t_stack *a, t_stack *b);

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
	ft_read_and_execute_operations(&a, &b);
	if (ft_stack_is_sorted(&a) && b.size == 0)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	ft_stack_free(&a);
	ft_stack_free(&b);
	return (0);
}

static void	ft_read_and_execute_operations(t_stack *a, t_stack *b)
{
	char	*line;

	line = get_next_line(0);
	while (line != NULL)
	{
		if (!ft_exec_swap_push(line, a, b) && !ft_exec_rotate(line, a, b)
			&& !ft_exec_rev_rotate(line, a, b))
		{
			free(line);
			ft_error_exit();
		}
		free(line);
		line = get_next_line(0);
	}
}

static int	ft_exec_swap_push(char *line, t_stack *a, t_stack *b)
{
	if (ft_strncmp(line, "sa\n", 3) == 0)
		sa(a, 0);
	else if (ft_strncmp(line, "sb\n", 3) == 0)
		sb(b, 0);
	else if (ft_strncmp(line, "ss\n", 3) == 0)
		ss(a, b, 0);
	else if (ft_strncmp(line, "pa\n", 3) == 0)
		pa(a, b, 0);
	else if (ft_strncmp(line, "pb\n", 3) == 0)
		pb(a, b, 0);
	else
		return (0);
	return (1);
}

static int	ft_exec_rotate(char *line, t_stack *a, t_stack *b)
{
	if (ft_strncmp(line, "ra\n", 3) == 0)
		ra(a, 0);
	else if (ft_strncmp(line, "rb\n", 3) == 0)
		rb(b, 0);
	else if (ft_strncmp(line, "rr\n", 3) == 0)
		rr(a, b, 0);
	else
		return (0);
	return (1);
}

static int	ft_exec_rev_rotate(char *line, t_stack *a, t_stack *b)
{
	if (ft_strncmp(line, "rra\n", 4) == 0)
		rra(a, 0);
	else if (ft_strncmp(line, "rrb\n", 4) == 0)
		rrb(b, 0);
	else if (ft_strncmp(line, "rrr\n", 4) == 0)
		rrr(a, b, 0);
	else
		return (0);
	return (1);
}
