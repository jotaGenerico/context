#include "minishell.h"

/* ========================================================================== */
/* Protótipos auxiliares locais                         */
/* ========================================================================== */

static int	    exec_builtin_parent(t_ast *node, t_shell *shell);
static void	    child_process(t_ast *node, t_shell *shell);
static t_ast	*get_command_node(t_ast *node);

/* ========================================================================== */
/* Funções auxiliares locais                            */
/* ========================================================================== */

/* * get_command_node:
 * Percorre a sub-árvore de redireção (esquerda) para encontrar o
 * nó do tipo NODE_COMMAND, que contém o argv.
 */
static t_ast	*get_command_node(t_ast *node)
{
	while (node && node->type != NODE_COMMAND)
		node = node->left;
	return (node);
}

/* * child_process:
 * Prepara e executa comandos externos no processo filho.
 * É usado para comandos externos e para builtins em pipes.
 */
static void	child_process(t_ast *node, t_shell *shell)
{
	char	**envp;
	char	*path;
	t_ast	*cmd_node;

	/* CORREÇÃO CRÍTICA DO SINAL NO FILHO (RESET PARA PADRÃO) */
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);

	/* Aplica redireções (o nó de redireção é o topo da sub-árvore) */
	if (apply_redirections(node, shell) != 0)
		exit(EXIT_FAILURE);

	/* Obtém o nó de comando real */
	cmd_node = get_command_node(node);

	/* Execução do builtin no filho, se for o caso (usado em pipes) */
	if (is_builtin(cmd_node))
		exec_builtin_child(cmd_node, shell);

	/* Execução de comando externo */
	if (!cmd_node || !cmd_node->argv || !cmd_node->argv[0])
		exit(EXIT_FAILURE);

	envp = env_list_to_array(shell->env_list);
	if (!envp)
		exit(EXIT_FAILURE);

	path = find_command_path(cmd_node->argv[0], shell);
	if (!path)
	{
		ft_dprintf(2, "minishell: %s: command not found\n", cmd_node->argv[0]);
		free_char_array(envp);
		exit(127);
	}

	execve(path, cmd_node->argv, envp);

	/* Se retornar, houve erro */
	perror("execve");
	free_char_array(envp);
	free(path);
	exit(126);
}

/* * exec_builtin_parent:
 * Executa um builtin no processo pai (para alterar o ambiente) com redireções.
 */
static int	exec_builtin_parent(t_ast *node, t_shell *shell)
{
	int	    sv_in;
	int	    sv_out;
	int	    sv_err;
	int	    status;
	t_ast	*cmd_node;

	/* 1. Salva FDs originais */
	if (save_std_fds(&sv_in, &sv_out, &sv_err) == -1)
		return (1);

	/* 2. Aplica redireções */
	if (apply_redirections(node, shell) != 0)
	{
		restore_std_fds(sv_in, sv_out, sv_err);
		return (1);
	}

	/* 3. CORREÇÃO CRÍTICA: Obtém o nó de comando real para o builtin */
	cmd_node = get_command_node(node);
	if (!cmd_node)
	{
		restore_std_fds(sv_in, sv_out, sv_err);
		return (1);
	}

	/* 4. Executa o builtin com o nó de comando correto (contém o argv) */
	status = exec_builtin(cmd_node, shell);

	/* 5. Restaura FDs */
	restore_std_fds(sv_in, sv_out, sv_err);

	return (status);
}


/* ========================================================================== */
/* Função principal                                */
/* ========================================================================== */

int	exec_simple_cmd(t_ast *node, t_shell *shell)
{
	pid_t	pid;
	int	    status;
	t_ast	*cmd_node;

	if (!node)
		return (1);

	// 1. Pega o nó de comando (percorre redirecionamentos)
	cmd_node = get_command_node(node);

	// Se o comando for vazio (ex: `< file`), retorna 0.
	if (!cmd_node || !cmd_node->argv || !cmd_node->argv[0])
		return (0);

	// 2. Checa e executa a atribuição de variável local (ex: VAR=VALOR)
	if (handle_assignment_only(cmd_node, shell))
		return (shell->exit_status);

	/* BUILTIN */
	if (is_builtin(cmd_node))
	{
		/* se não há redireções, executa diretamente no pai */
		if (!has_redirections(node))
			return (exec_builtin(cmd_node, shell));
		/* se há redireções, aplica temporariamente e executa no pai */
		return (exec_builtin_parent(node, shell));
	}

	/* Comando externo: precisa fork + execve */
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
		child_process(node, shell);

	/* pai espera o filho */
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		// Não altere o exit_status se o waitpid falhar.
	}
	setup_signals(); // Restaura signals

	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);

	return (shell->exit_status);
}
