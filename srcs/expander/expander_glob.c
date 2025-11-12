#include "minishell.h"

static void		transfer_matches_to_list(t_list **new_arg_list,
					t_list **matches);
static char		**finalize_wildcard_expansion(char **old_argv,
					t_list *new_arg_list);
static void		process_wildcard_arg(char *arg, t_list **new_arg_list);

int	expand_wildcards(char ***argv_ptr)
{
	char	**old_argv;
	t_list	*new_arg_list;
	int		i;

	old_argv = *argv_ptr;
	new_arg_list = NULL;
	i = 0;
	while (old_argv[i])
	{
		process_wildcard_arg(old_argv[i], &new_arg_list);
		i++;
	}
	*argv_ptr = finalize_wildcard_expansion(old_argv, new_arg_list);
	if (!*argv_ptr)
		return (1);
	return (0);
}

static void	process_wildcard_arg(char *arg, t_list **new_arg_list)
{
	t_list	*matches;

	matches = NULL;
	if (ft_strchr(arg, '*') != NULL)
	{
		matches = get_glob_matches(arg);
		if (matches)
		{
			transfer_matches_to_list(new_arg_list, &matches);
			return ;
		}
	}
	ft_lstadd_back(new_arg_list, ft_lstnew(ft_strdup(arg)));
}

static void	transfer_matches_to_list(t_list **new_arg_list, t_list **matches)
{
	t_list	*temp;

	while (*matches)
	{
		temp = *matches;
		*matches = (*matches)->next;
		temp->next = NULL;
		ft_lstadd_back(new_arg_list, temp);
	}
}

static char	**finalize_wildcard_expansion(char **old_argv, t_list *new_arg_list)
{
	t_list	*temp;
	char	**new_argv;

	free_char_array(old_argv);
	new_argv = ft_lst_to_array(new_arg_list);
	while (new_arg_list)
	{
		temp = new_arg_list;
		new_arg_list = new_arg_list->next;
		free(temp);
	}
	return (new_argv);
}
