#ifndef FT_PUSH_SWAP_H
# define FT_PUSH_SWAP_H

# include "../libft/include/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_node
{
	int				value;
	int				index;
	int				push_cost;
	int				above_median;
	int				cheapest;
	struct s_node	*target_node;
	struct s_node	*next;
	struct s_node	*prev;
}					t_node;

typedef struct s_stack
{
	t_node	*top;
	int		size;
}			t_stack;

// Stack operations
void	sa(t_stack *a, int print);
void	sb(t_stack *b, int print);
void	ss(t_stack *a, t_stack *b, int print);
void	pa(t_stack *a, t_stack *b, int print);
void	pb(t_stack *a, t_stack *b, int print);
void	ra(t_stack *a, int print);
void	rb(t_stack *b, int print);
void	rr(t_stack *a, t_stack *b, int print);
void	rra(t_stack *a, int print);
void	rrb(t_stack *b, int print);
void	rrr(t_stack *a, t_stack *b, int print);

// Stack utils
void	ft_stack_init(t_stack *stack);
void	ft_stack_push(t_stack *stack, int value);
int		ft_stack_pop(t_stack *stack);
void	ft_stack_free(t_stack *stack);
int		ft_stack_is_sorted(t_stack *a);
t_node	*ft_find_min(t_stack *stack);
t_node	*ft_find_max(t_stack *stack);

// Parsing
int		ft_count_split(char **split);
void	ft_free_split(char **split);
int		ft_has_duplicates(t_stack *a);
int		ft_is_valid_number(char *str);
int		ft_parse_arguments(int argc, char **argv, t_stack *a);
int		ft_parse_normal_args(int argc, char **argv, t_stack *a);
int		ft_parse_string_args(char *str, t_stack *a);

// Algorithm
void	ft_push_swap(t_stack *a, t_stack *b);
void	ft_sort_three(t_stack *a);
void	ft_sort_stacks(t_stack *a, t_stack *b);
void	ft_init_nodes_a(t_stack *a, t_stack *b);
void	ft_init_nodes_b(t_stack *a, t_stack *b);
void	ft_current_index(t_stack *stack);
void	ft_set_target_a(t_stack *a, t_stack *b);
t_node	*ft_find_target_node(t_stack *a, t_node *current_b);
void	ft_set_target_b(t_stack *a, t_stack *b);
void	ft_cost_analysis_a(t_stack *a, t_stack *b);
void	ft_cost_analysis_b(t_stack *a, t_stack *b);
void	ft_set_cheapest(t_stack *stack);
t_node	*ft_get_cheapest(t_stack *stack);
void	ft_prep_for_push(t_stack *stack, t_node *top_node, char stack_name);
void	ft_move_a_to_b(t_stack *a, t_stack *b);
void	ft_move_b_to_a(t_stack *a, t_stack *b);
void	ft_min_on_top(t_stack *a);
void	ft_set_target_b(t_stack *a, t_stack *b);
void	ft_init_nodes_b(t_stack *a, t_stack *b);
t_node	*ft_find_target_node_b(t_stack *b, t_node *current_a);
void	ft_cost_analysis_b(t_stack *a, t_stack *b);
void	ft_rotate_both(t_stack *a, t_stack *b, t_node *cheapest_a,
			t_node *cheapest_b);

void	ft_error_exit(void);

#endif
