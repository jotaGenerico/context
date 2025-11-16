#include "minishell.h"

static char		**argv_add(char **argv, char *new_word);
static t_ast	*parse_redirection(t_dlist **tokens, t_token *redir_token);
static int		handle_redirection_token(t_dlist **tokens,
					t_ast **cmd_node_ptr);
static int		process_next_command_token(t_dlist **tokens,
					t_ast **cmd_node_ptr);

t_ast	*parse_command(t_dlist **tokens)
{
	t_ast	*cmd_node;
	int		status;

	cmd_node = ast_new_node(NODE_COMMAND, NULL, NULL);
	if (!cmd_node)
		return (NULL);
	while (*tokens)
	{
		status = process_next_command_token(tokens, &cmd_node);
		if (status == -1)
		{
			ast_free(cmd_node);
			return (NULL);
		}
		if (status == 0)
			break ;
	}
	if (!cmd_node->argv && !cmd_node->filename)
	{
		ast_free(cmd_node);
		return (NULL);
	}
	return (cmd_node);
}

static int	handle_redirection_token(t_dlist **tokens, t_ast **cmd_node_ptr)
{
	t_ast	*redir_node;
	t_token	*redir_token;

	redir_token = (*tokens)->content;
	*tokens = (*tokens)->next;
	redir_node = parse_redirection(tokens, redir_token);
	if (!redir_node)
		return (-1);
	redir_node->left = *cmd_node_ptr;
	*cmd_node_ptr = redir_node;
	*tokens = (*tokens)->next;
	return (1);
}

static int	process_next_command_token(t_dlist **tokens, t_ast **cmd_node_ptr)
{
	t_token	*token;

	token = (*tokens)->content;
	if (token->type == TOKEN_WORD)
	{
		(*cmd_node_ptr)->argv = argv_add((*cmd_node_ptr)->argv, token->value);
		if (!(*cmd_node_ptr)->argv)
			return (-1);
		*tokens = (*tokens)->next;
		return (1);
	}
	else if (token->type >= TOKEN_REDIR_IN && token->type <= TOKEN_HEREDOC)
		return (handle_redirection_token(tokens, cmd_node_ptr));
	else
		return (0);
}

static char	**argv_add(char **argv, char *new_word)
{
	int		count;
	int		i;
	char	**new_argv;

	count = 0;
	i = 0;
	while (argv && argv[count])
		count++;
	new_argv = malloc(sizeof(char *) * (count + 2));
	if (!new_argv)
		return (NULL);
	while (i < count)
	{
		new_argv[i] = argv[i];
		i++;
	}
	new_argv[count] = ft_strdup(new_word);
	new_argv[count + 1] = NULL;
	free(argv);
	return (new_argv);
}

static t_ast	*parse_redirection(t_dlist **tokens, t_token *redir_token)
{
	t_ast		*redir_node;
	t_token		*file_token;

	if (!(*tokens) || ((t_token *)(*tokens)->content)->type != TOKEN_WORD)
		return (NULL);
	file_token = (*tokens)->content;
	if (redir_token->type == TOKEN_REDIR_IN)
		redir_node = ast_new_node(NODE_REDIR_IN, NULL, NULL);
	else if (redir_token->type == TOKEN_REDIR_OUT)
		redir_node = ast_new_node(NODE_REDIR_OUT, NULL, NULL);
	else if (redir_token->type == TOKEN_REDIR_APPEND)
		redir_node = ast_new_node(NODE_REDIR_APPEND, NULL, NULL);
	else
		redir_node = ast_new_node(NODE_HEREDOC, NULL, NULL);
	if (!redir_node)
		return (NULL);
	redir_node->filename = ft_strdup(file_token->value);
	return (redir_node);
}
