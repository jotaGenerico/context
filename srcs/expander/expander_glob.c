#include "minishell.h"

// ---------------------------------------------------------------- //
// I. UTILS DE ARRAY E LIBERAÇÃO (Adapte se já existirem)
// ---------------------------------------------------------------- //

// Converte t_list* para char** (transfere posse das strings)
static char	**ft_lst_to_array(t_list *list)
{
	char	**array;
	int		len;
	int		i;
	t_list	*current;

	len = ft_lstsize(list);
	array = (char **)ft_calloc(len + 1, sizeof(char *));
	if (!array)
		return (NULL);

	current = list;
	i = 0;
	while (current)
	{
		// Transfere a string da lista para o array
		array[i] = (char *)current->content;
		current->content = NULL; // Crucial: evita que o ft_lstclear libere a string
		current = current->next;
		i++;
	}
	return (array);
}

// ---------------------------------------------------------------- //
// II. CORE MATCHING LOGIC
// ---------------------------------------------------------------- //

// Função recursiva para checar o '*' (Wildcard)
int	is_glob_match(const char *pattern, const char *text)
{
	// 1. CASO BASE DE SUCESSO: Ambas as strings terminaram
	if (*pattern == '\0' && *text == '\0')
		return (1);

	// 2. LÓGICA DO CORINGA ('*')
	if (*pattern == '*')
	{
		// Tenta a primeira opção: '*' corresponde a ZERO caracteres (avança só no pattern)
		if (is_glob_match(pattern + 1, text))
			return (1);

		// Se o texto não terminou, tenta a segunda opção: '*' corresponde a UM ou mais caracteres
		// (Fica no pattern, avança no text)
		if (*text != '\0')
			return (is_glob_match(pattern, text + 1));

		// Se o texto terminou, e o 'zero match' falhou, não há mais chance de sucesso.
		return (0);
	}

	// 3. CASO GERAL: Caracteres normais (Devem ser iguais)
	// Se o pattern não é '*', mas o text terminou, falha.
	if (*text == '\0')
		return (0);

	if (*pattern == *text)
		return (is_glob_match(pattern + 1, text + 1));

	// 4. FALHA: Caracteres não batem
	return (0);
}

// Percorre o diretório e encontra correspondências
static t_list	*get_glob_matches(char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	t_list			*matches;

	matches = NULL;
	dir = opendir(".");
	if (!dir)
		return (NULL);

	while ((entry = readdir(dir)) != NULL)
	{
		// 1. Ignora '.' e '..' e arquivos ocultos (a menos que o padrão comece com '.')
		if (entry->d_name[0] == '.' && pattern[0] != '.')
			continue ;

		// 2. Checa a correspondência com a lógica recursiva
		if (is_glob_match(pattern, entry->d_name))
		{
			// Adiciona uma CÓPIA do nome do arquivo à lista
			ft_lstadd_back(&matches, ft_lstnew(ft_strdup(entry->d_name)));
		}
	}
	closedir(dir);
	return (matches);
}

// ---------------------------------------------------------------- //
// III. FUNÇÃO PRINCIPAL
// ---------------------------------------------------------------- //

/*
 * @brief Itera sobre argv, e substitui argumentos com '*' pela lista de arquivos.
 * @param argv_ptr O endereço do array de argumentos (cmd->argv).
 * @return int 0 se sucesso, 1 se falha (erro de alocação).
 */
int	expand_wildcards(char ***argv_ptr)
{
	char	**old_argv;
	t_list	*new_arg_list;
	t_list	*matches;
	t_list	*temp;
	int		i;

	old_argv = *argv_ptr;
	new_arg_list = NULL;
	i = 0;
	while (old_argv[i])
	{
		// 1. Checa se o argumento contém '*'
		if (ft_strchr(old_argv[i], '*') != NULL)
		{
			matches = get_glob_matches(old_argv[i]); // Pega lista de arquivos (já com strdup)
			if (matches)
			{
				// Transfere cada nó individualmente
				while (matches)
				{
					temp = matches;
					matches = matches->next;
					temp->next = NULL; // Isola o nó
					ft_lstadd_back(&new_arg_list, temp);
				}
				i++;
				continue ;
			}
		}

		// 2. Se não tem wildcard OU não encontrou matches, mantém o argumento original
		ft_lstadd_back(&new_arg_list, ft_lstnew(ft_strdup(old_argv[i])));
		i++;
	}

	// 3. Libera o array original (incluindo o conteúdo)
	free_char_array(old_argv);

	// 4. Cria o novo array (char**) e substitui o antigo
	*argv_ptr = ft_lst_to_array(new_arg_list);

	// 5. Libera a estrutura da lista ligada (apenas os nós)
	// CORREÇÃO CRÍTICA APLICADA: Liberação manual para evitar leak do nó
	while (new_arg_list)
	{
		temp = new_arg_list;
		new_arg_list = new_arg_list->next;
		free(temp); // Libera apenas o nó, o conteúdo já foi transferido
	}

	if (!*argv_ptr)
	{
		// ft_putstr_fd("minishell: erro de alocação na expansão de wildcard\n", 2);
		return (1);
	}
	return (0);
} // <--- A chave final estava faltando.
