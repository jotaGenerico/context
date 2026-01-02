// Question graded by Moulinette: 100

#include <unistd.h>
#include <stdio.h>
#include <string.h>

// Define o tamanho do buffer de leitura.
// A Molinette pode testar com valores diferentes.
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

/**
 * Função que processa a string lida e imprime o resultado.
 * 'line' contém todo o conteúdo lido do stdin.
 * 'str' é o padrão (argumento) que deve ser substituído por '*'.
 */
void	ft_filter(char *line, char *str)
{
	int	len = strlen(str); // Tamanho do padrão a ser buscado
	int	i = 0;             // Índice para percorrer a string 'line'

	// Percorre cada caractere da entrada total
	while (line[i])
	{
		int	h = 0;
		// Verifica se o padrão 'str' começa na posição atual 'i'
		// Compara caractere por caractere enquanto 'str' não acabar
		while (str[h] && line[i + h] == str[h])
			h++;

		// Se 'h' atingiu o tamanho de 'len', significa que o padrão completo foi encontrado
		if (h == len)
		{
			int	l = 0;
			// Imprime um asterisco para cada caractere do padrão encontrado
			while (l < len)
			{
				write (1, "*", 1);
				l++;
			}
			// Salta o índice 'i' para depois do padrão já processado
			i += h;
		}
		else
		{
			// Se o padrão não foi encontrado nesta posição, imprime o caractere atual
			write (1, &line[i], 1);
			i++; // Avança apenas um caractere
		}
	}
}

int	main(int argc, char **argv)
{
	// Buffer estático grande para armazenar a entrada (stdin)
	// Declarado na stack, comporta quase 1MB.
	char	line[999999];
	int		ret = 1; // Armazena a quantidade de bytes lidos em cada chamada
	int		i = 0;   // Índice acumulador para o buffer 'line'

	// Validação: Exatamente 1 argumento e ele não pode ser uma string vazia
	if (argc != 2 || !argv[1][0])
		return (1);

	// Loop de leitura: continua enquanto o read retornar mais de 0 bytes
	while (ret > 0)
	{
		// Lê do stdin (fd 0) para a posição atual do índice 'i' no buffer
		ret = read(0, &line[i], BUFFER_SIZE);

		// Se o retorno for negativo, houve um erro na leitura do sistema
		if (ret < 0)
		{
			perror("Error"); // Imprime "Error: " seguido da descrição do erro
			return (1);
		}
		// Incrementa o índice total baseado em quantos bytes foram lidos nesta rodada
		i += ret;
	}

	// Finaliza a sequência lida como uma string válida para uso do strlen/while
	line[i] = '\0';

	// Chama a função para filtrar e imprimir o resultado no stdout
	ft_filter(line, argv[1]);

	return (0);
}
