/* NOVO ARQUIVO: ast_free.c ou em parser_utils.c */

/**
 * Libera recursivamente todos os nós da AST.
 * Assume-se que 'content' do nó (ex: t_cmd, t_redir) também deve ser liberado,
 * mas para simplificar, a AST libera apenas a estrutura básica dos nós aqui.
 * É fundamental que a liberação do conteúdo (argv, filenames) ocorra em outro lugar.
 */
void	free_ast(t_ast *node)
{
	if (!node)
		return ;

	// Libera recursivamente sub-árvores
	free_ast(node->left);
	free_ast(node->right);

	// Libera o array de strings em comandos simples (se existir)
	if (node->type == NODE_SIMPLE_CMD && node->cmd && node->cmd->argv)
		free_char_array(node->cmd->argv); // ft_free_char_array ou equivalente

	// Libera a estrutura de comando (t_cmd) ou redirecionamento (t_redir)
	// **ATENÇÃO:** Esta parte depende de como você armazena os dados
	if (node->cmd)
	{
		// Se node->cmd->argv já foi liberado acima, apenas free o struct
		free(node->cmd);
	}
	// Se você tiver um struct separado para redirecionamentos no nó
	// Exemplo: if (node->redir) free(node->redir);

	// Finalmente, libera o próprio nó
	free(node);
}

// Nota: Você deve ter uma função para liberar arrays de strings (char **),
// por exemplo: void free_char_array(char **arr);

/* NOVO ARQUIVO: dlist_free.c ou em lexer_utils.c */

/**
 * Libera toda a lista duplamente encadeada de tokens.
 * O conteúdo do token (char *value) é liberado pela função 'del'.
 */
void	free_token_value(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	if (token)
	{
		if (token->value)
			free(token->value); // Libera o char *value do token
		free(token); // Libera o struct t_token
	}
}

void	ft_dlstclear(t_dlst **lst, void (*del)(void *))
{
	t_dlst	*current;
	t_dlst	*next;

	if (!lst || !*lst)
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		if (del)
			del(current->content); // Libera o t_token*
		free(current); // Libera o nó da lista
		current = next;
	}
	*lst = NULL;
}

// Chame assim: ft_dlstclear(&tokens, free_token_value);
