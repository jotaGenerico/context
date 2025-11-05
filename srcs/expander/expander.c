#include "minishell.h"

// Não há mais funções auxiliares aqui. A lógica de expansão e
// citação forte/fraca está totalmente encapsulada em expand_word.

void	expand_tokens(t_dlist *tokens, t_shell *shell)
{
	t_dlist	*current;
	t_token	*token;
	char	*expanded;

	current = tokens;
	while (current)
	{
		token = (t_token *)current->content;

		// Somente tokens do tipo WORD devem passar pela expansão.
		// A função expand_word agora lida com as aspas (simples e duplas)
		// e a expansão de variáveis de ambiente.
		if (token->type == TOKEN_WORD)
		{
			// Chamada corrigida: expand_word não precisa mais do bool 'in_quotes'.
			expanded = expand_word(token->value, shell);
			if (expanded)
			{
				free(token->value);
				token->value = expanded;
			}
		}

		// Atenção: Redireções (>, <) e Pipes (|) geralmente não são expandidos aqui,
		// e se forem, a lógica é tratada pelo token->type.

		current = current->next;
	}
}
