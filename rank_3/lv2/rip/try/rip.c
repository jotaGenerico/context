#include <stdio.h>

/**
 * Função de Backtracking para explorar as possibilidades de remoção.
 * @param str: String original recebida como argumento.
 * @param index: Posição atual que estamos processando na string.
 * @param open: Contador de parênteses abertos '(' mantidos até agora.
 * @param close: Contador de parênteses fechados ')' mantidos até agora.
 * @param removed: Quantos caracteres já substituímos por espaço ' '.
 * @param min_remove: O número exato de remoções necessárias (calculado no início).
 * @param buffer: Onde montamos a string resultante para impressão.
 */
void	print_solutions(char *str, int index, int open, int close, int removed, int min_remove, char *buffer)
{
	// CASO BASE: Chegou ao fim da string original
	if (str[index] == '\0')
	{
		// Verifica se está balanceado (open == close)
		// E se removeu exatamente o mínimo necessário
		if (open == close && removed == min_remove)
		{
			buffer[index] = '\0'; // Finaliza a string do buffer
			puts(buffer);        // Imprime a solução encontrada
		}
		return ;
	}

	char c = str[index];

	// DECISÃO 1: TENTAR MANTER O CARACTERE
	if (c == '(' || c == ')')
	{
		buffer[index] = c;
		if (c == '(')
			// Se for '(', sempre podemos manter e incrementar 'open'
			print_solutions(str, index + 1, open + 1, close, removed, min_remove, buffer);
		else if (open > close)
			// Se for ')', só mantemos se houver um '(' correspondente aberto antes (open > close)
			print_solutions(str, index + 1, open, close + 1, removed, min_remove, buffer);
	}
	else
	{
		// Se não for parêntese (outros caracteres), apenas mantemos
		buffer[index] = c;
		print_solutions(str, index + 1, open, close, removed, min_remove, buffer);
	}

	// DECISÃO 2: TENTAR REMOVER O CARACTERE (Substituir por espaço)
	if (c == '(' || c == ')')
	{
		// Só tentamos remover se ainda não ultrapassamos o limite mínimo de remoções
		if (removed < min_remove)
		{
			buffer[index] = ' '; // Substitui o parêntese por espaço
			// Chama a recursão incrementando o contador de 'removed'
			print_solutions(str, index + 1, open, close, removed + 1, min_remove, buffer);
		}
	}
}

/**
 * Calcula o número mínimo de parênteses que PRECISAM ser removidos para balancear.
 */
int	count(char *str)
{
	int open = 0;
	int close = 0;
	int	i = -1;

	while (str[++i])
	{
		if (str[i] == '(')
			open++;
		else if (str[i] == ')')
		{
			if (open > 0)
				open--; // Este ')' fecha um '(' que estava aberto
			else
				close++; // Este ')' não tem par, precisa ser removido
		}
	}
	// A soma dos que sobraram abertos e dos fechados sem par é o mínimo a remover
	return (open + close);
}

int	main(int ac, char *av[])
{
	// O exercício pede para não verificar se argv[1] está vazio,
	// apenas se o número de argumentos é diferente de 2.
	if (ac != 2)
		return (1);

	char *str = av[1];
	int	min_remove = count(str); // Passo 1: Descobrir o alvo de remoções
	char buffer[256];            // Buffer fixo para evitar malloc

	// Passo 2: Iniciar o backtracking do índice 0 com contadores zerados
	print_solutions(str, 0, 0, 0, 0, min_remove, buffer);

	return (0);
}
