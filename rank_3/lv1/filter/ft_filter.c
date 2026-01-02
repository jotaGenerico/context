#include <unistd.h>
#include <stdio.h>
#include <string.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10   // Define o tamanho do chunk de leitura
#endif

// Função que processa uma linha e substitui todas as ocorrências de str por '*'
void	ft_filter(char *line, char *str)
{
	int	len = strlen(str); // Comprimento da string a ser substituída
	int	i = 0;

	while (line[i]) // Percorre cada caractere da linha
	{
		int	h = 0;

		// Verifica se a substring a partir de i bate com str
		while (str[h] && line[i + h] == str[h])
			h++;

		if (h == len) // Encontrou a string inteira
		{
			int	l = 0;
			// Escreve '*' para cada caractere da substring encontrada
			while (l < len)
			{
				write(1, "*", 1); // Saída para stdout
				l++;
			}
			i += h; // Avança o índice para pular a substring substituída
		}
		else
		{
			// Se não bateu com str, escreve o caractere original
			write(1, &line[i], 1);
			i++;
		}
	}
}

// Função principal
int	main(int argc, char **argv)
{
	char	line[999999]; // Buffer grande para armazenar todo stdin
	int		ret = 1;      // Quantidade de bytes lidos a cada read
	int		i = 0;        // Índice para preencher o buffer

	// Verifica se o programa recebeu exatamente 1 argumento válido
	if (argc != 2 || !argv[1][0])
		return (1);

	// Loop de leitura de stdin em chunks de tamanho BUFFER_SIZE
	while (ret > 0)
	{
		ret = read(0, &line[i], BUFFER_SIZE); // Lê do stdin
		if (ret < 0) // Caso ocorra erro na leitura
		{
			perror("Error");
			return (1);
		}
		i += ret; // Atualiza o índice com a quantidade de bytes lidos
	}

	// Chama a função que substitui todas as ocorrências da string
	ft_filter(line, argv[1]);

	return (0); // Finaliza o programa
}
