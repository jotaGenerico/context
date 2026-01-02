#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

// Tamanho fixo do buffer para a chamada read (pode ser qualquer valor razoável)
#define READ_BUFFER_SIZE 4096

// --- Funcoes Auxiliares ---

/**
 * @brief Implementacao simplificada do ft_strlen para uso interno.
 */
static size_t ft_strlen(const char *s)
{
	size_t len = 0;
	while (s && s[len])
		len++;
	return (len);
}

/**
 * @brief Imprime uma mensagem de erro formatada no stderr e libera a memoria.
 * @param msg A mensagem de erro especifica.
 * @param buffer O ponteiro de buffer a ser liberado (pode ser NULL).
 * @return 1 (para retorno de erro).
 */
static int handle_error(const char *msg, char *buffer)
{
	fprintf(stderr, "Error: %s\n", msg);
	if (buffer)
		free(buffer);
	return (1);
}

/**
 * @brief Le toda a entrada padrao (stdin) para um buffer alocado dinamicamente.
 * @param total_size Ponteiro para armazenar o tamanho total lido.
 * @return O buffer de string completo ou NULL em caso de erro.
 */
static char *read_all_stdin(size_t *total_size)
{
	char	temp_buf[READ_BUFFER_SIZE];
	char	*res = NULL;
	size_t	current_size = 0;
	ssize_t	bytes_read;

	while ((bytes_read = read(STDIN_FILENO, temp_buf, READ_BUFFER_SIZE)) > 0)
	{
		// 1. Tenta realocar para o novo tamanho + 1 para o terminador nulo
		char *new_res = realloc(res, current_size + bytes_read + 1);
		if (!new_res)
		{
			handle_error(strerror(errno), res);
			return (NULL);
		}
		res = new_res;

		// 2. Copia os novos dados
		memcpy(res + current_size, temp_buf, bytes_read);
		current_size += bytes_read;

		// 3. Garante o terminador nulo no final
		res[current_size] = '\0';
	}

	// Verifica se o loop terminou devido a um erro de read
	if (bytes_read < 0)
	{
		handle_error(strerror(errno), res);
		return (NULL);
	}

	*total_size = current_size;
	// Retorna NULL se a entrada estava vazia (current_size == 0)
	// Mas o enunciado permite entrada vazia, apenas deve retornar o buffer
	return (res);
}

/**
 * @brief Substitui todas as ocorrencias da substring 's' por asteriscos '*'.
 * Ocorre in-place (modifica o buffer de entrada).
 * @param buffer O buffer de entrada/saida.
 * @param s A substring a ser substituida.
 * @param s_len O comprimento da substring.
 */
static void replace_in_place(char *buffer, const char *s, size_t s_len)
{
	char	*current;

	// Equivalente ao man 3 memmem, porem usando strstr no buffer ja como string
	current = buffer;
	while ((current = strstr(current, s)) != NULL)
	{
		// Encontrou uma ocorrencia. Substitui por '*'
		for (size_t i = 0; i < s_len; i++)
			current[i] = '*';

		// Avanca o ponteiro para apos a substituicao
		current += s_len;
	}
}

// --- Funcao Principal ---

int main(int argc, char **argv)
{
	char	*filter_str;
	size_t	filter_len;
	size_t	content_size = 0;
	char	*content = NULL;

	// 1. Verificacao de argumentos
	if (argc != 2 || (filter_len = ft_strlen(argv[1])) == 0)
	{
		fprintf(stderr, "Error: Invalid number of arguments or empty argument.\n");
		return (1);
	}
	filter_str = argv[1];

	// 2. Leitura da entrada padrao
	content = read_all_stdin(&content_size);
	if (!content && content_size > 0) // read_all_stdin ja trata o erro
		return (1);

	// Se a leitura foi bem sucedida (content pode ser NULL se stdin estava vazio)
	if (content)
	{
		// 3. Processamento (substituicao)
		replace_in_place(content, filter_str, filter_len);

		// 4. Escrita da saida (stdout)
		if (write(STDOUT_FILENO, content, content_size) < 0)
		{
			// Erro na escrita tambem deve ser tratado
			return (handle_error(strerror(errno), content));
		}
	}
	// Se content == NULL e content_size == 0, nao faz nada (entrada vazia).

	// 5. Limpeza e retorno
	if (content)
		free(content);
	return (0);
}
