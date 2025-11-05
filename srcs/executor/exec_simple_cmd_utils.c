#include "minishell.h"

static int	validate_key(char *assignment);
static int	is_valid_key_char(char c);

int	handle_assignment_only(t_ast *node, t_shell *shell)
{
	char	*assignment;

	// 1. Checagem de Estrutura: Deve haver exatamente UM argumento.
	if (!node->argv || node->argv[1] != NULL)
		return (0);

	assignment = node->argv[0];

	// 2. Checagem de Sintaxe: Deve conter um '='.
	if (ft_strchr(assignment, '=') == NULL)
		return (0);

	// 3. Checagem de Validação da Chave: Verifica regras de nomenclatura.
	if (validate_key(assignment) == 0)
		return (0);

	// 4. APLICAÇÃO: Atualiza/Adiciona a variável no env_list do shell.
	// Esta função DEVE retornar 0 em caso de SUCESSO.
	if (env_list_set_var(&(shell->env_list), assignment) == 0)
	{
		shell->exit_status = 0; // Atribuição isolada é sucesso (exit status 0)
		return (1); // Comando tratado com sucesso
	}

	// Se falhar (erro de malloc em env_list_set_var), retorna 0 e o executor
	// continuará tentando tratar como comando externo, o que é aceitável.
	return (0);
}

static int	is_valid_key_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

static int	validate_key(char *assignment)
{
	int	i;

	i = 0;
	// O primeiro caractere deve ser letra ou '_'
	if (!ft_isalpha(assignment[i]) && assignment[i] != '_')
		return (0);
	i++;

	// Os caracteres seguintes (até o '=') devem ser alfanuméricos ou '_'
	while (assignment[i] && assignment[i] != '=')
	{
		if (!is_valid_key_char(assignment[i]))
			return (0);
		i++;
	}
	return (1);
}
