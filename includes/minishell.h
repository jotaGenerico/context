#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <stdbool.h>
# include <stdarg.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <dirent.h>

/* Libft */
# include "libft.h"

/* ************************************************************************** */
/*                                DEFINES                                     */
/* ************************************************************************** */

extern volatile sig_atomic_t	g_signal;


/* ************************************************************************** */
/*                                TOKEN TYPES                                 */
/* ************************************************************************** */

typedef enum e_token_type
{
	TOKEN_ERROR,
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_SEMICOLON
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

/* ************************************************************************** */
/*                                PARSER TYPES                                */
/* ************************************************************************** */

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_SEQUENCE,
	NODE_REDIR_IN,
	NODE_REDIR_OUT,
	NODE_REDIR_APPEND,
	NODE_HEREDOC,
	NODE_SUBSHELL
}	t_node_type;

typedef struct s_ast
{
	t_node_type		type;
	char			**argv;
	char			*filename;
	int				heredoc_fd;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

/* ************************************************************************** */
/*                               ENVIRONMENT                                  */
/* ************************************************************************** */

typedef struct s_env_var
{
	char	*key;
	char	*value;
}	t_env_var;

/* ************************************************************************** */
/*                                SHELL STATE                                 */
/* ************************************************************************** */

typedef struct s_shell
{
	t_dlist	*env_list;
	t_dlist	*token_list;
	int		exit_status;
}	t_shell;

/* ************************************************************************** */
/*                               PROTOTYPES                                   */
/* ************************************************************************** */

/* ----------------------------- CORE ----------------------------- */
void		init_shell(t_shell *shell, char **envp);
void		cleanup_shell(t_shell *shell);
t_env_var	*create_env_var(char *key_value_pair);
void		free_env_var(void *content);
void		setup_signals(void);
char		*ft_strjoin3(char const *s1, char const *s2, char const *s3);

/* ----------------------------- LEXER ----------------------------- */
t_dlist		*lexer(char *line);
void		free_tokens(void *content);
t_token		*create_token(t_token_type type, char *value);
void		print_tokens(t_dlist *tokens);
char		*extract_quoted_word(char *line, int *i);
bool		is_quote(char c);
bool		is_operator(char *line, int i);
t_token		*create_operator_token(char *line, int *i);

/* ----------------------------- EXPANDER ----------------------------- */
void		expand_tokens(t_dlist *tokens, t_shell *shell);
char 		*expand_word(char *word, t_shell *shell);
char		*get_env_value(char *key, t_shell *shell);
int			get_var_name_len(char *str);
int			is_glob_match(const char *pattern, const char *text);
void		expand_variables(char **argv, t_shell *shell);
int			expand_wildcards(char ***argv_ptr);

/* ----------------------------- PARSER ----------------------------- */
t_ast		*parse_tokens(t_dlist *tokens);
t_ast		*parse_and_or(t_dlist **tokens);
t_ast		*parse_list(t_dlist **tokens);
t_ast		*parse_command(t_dlist **tokens);
t_ast		*parse_pipeline(t_dlist **tokens);
t_ast		*parse_subshell(t_dlist **tokens);
t_ast		*ast_new_node(t_node_type type, t_ast *left, t_ast *right);
void		ast_free(t_ast *node);
void		print_ast(t_ast *node, int depth);
t_ast		*parse_list(t_dlist **tokens);

/* ----------------------------- EXECUTOR ----------------------------- */
int			execute_ast(t_ast *node, t_shell *shell);
int			exec_simple_cmd(t_ast *node, t_shell *shell);
int			exec_pipeline(t_ast *node, t_shell *shell);
int			exec_and_or(t_ast *node, t_shell *shell);
int			exec_subshell(t_ast *node, t_shell *shell);
int			env_list_set_var(t_dlist **env_list, char *assignment);

/* ------------------------- EXECUTOR UTILS -------------------------- */
int			save_std_fds(int *sv_in, int *sv_out, int *sv_err);
void		restore_std_fds(int sv_in, int sv_out, int sv_err);
bool		has_redirections(t_ast *node);
char		*find_command_path(const char *cmd, t_shell *shell);
int			apply_redirections(t_ast *node, t_shell *shell);
int			handle_heredocs(t_ast *node, t_shell *shell);
int			handle_assignment_only(t_ast *node, t_shell *shell);
bool		is_directory(const char *path);

/* Em seu minishell.h (ou arquivo de cabeçalho pertinente) */

// Para redirections_utils.c
void	safe_close(int fd); // CORREÇÃO 3

// Para exec_pipeline.c
int	exec_pipeline(t_ast *node, t_shell *shell); // Deve estar na interface pública
int	exec_pipe(t_ast *left, t_ast *right, t_shell *shell); // CORREÇÃO 3

/* ------------------------- ENVIRONMENT UTILS ----------------------- */
char		**env_list_to_array(t_dlist *env_list);
void		free_char_array(char **arr);

/* ------------------------- PIPE UTILS -------------------------- */
int			*alloc_pipes(int n_pipes);
void		free_pipes(int *pipes, int n_pipes);
void		close_all_pipes(int *pipes, int n_pipes);
pid_t		*alloc_pids(int n);
int			wait_for_children(pid_t *pids, int n, t_shell *shell);

/* ---------------------------- BUILTINS ----------------------------- */
int			is_builtin(t_ast *node);
int			exec_builtin(t_ast *node, t_shell *shell);
int			exec_builtin_child(t_ast *node, t_shell *shell);

/* Builtins individuais */
int			builtin_cd(char **argv, t_shell *shell);
int			builtin_echo(char **argv);
int			builtin_env(t_shell *shell);
int			builtin_exit(char **argv, t_shell *shell);
int			builtin_export(char **argv, t_shell *shell);
int			builtin_pwd(void);
int			builtin_unset(char **argv, t_shell *shell);

/* ---------------------------- UTILS ------------------------------ */
int		ft_dprintf(int fd, const char *format, ...);

#endif
