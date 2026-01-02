// main.c
#include "gnl.h"
#include <fcntl.h>

int main(void)
{
	int		fd;
	char	*line;
	int		i;

	printf("=== TESTE 1: Arquivo com várias linhas ===\n");
	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("❌ Erro ao abrir test.txt\n");
		return (1);
	}
	i = 1;
	while ((line = get_next_line(fd)))
	{
		printf("Linha %d: %s", i, line);
		free(line);
		i++;
	}
	close(fd);
	printf("\n");

	printf("=== TESTE 2: Arquivo vazio ===\n");
	fd = open("empty.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("❌ Erro ao abrir empty.txt\n");
		return (1);
	}
	line = get_next_line(fd);
	if (line == NULL)
		printf("✅ Retornou NULL (correto)\n");
	else
	{
		printf("❌ Deveria retornar NULL mas retornou: %s\n", line);
		free(line);
	}
	close(fd);
	printf("\n");

	printf("=== TESTE 3: Linha sem \\n no final ===\n");
	fd = open("no_newline.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("❌ Erro ao abrir no_newline.txt\n");
		return (1);
	}
	i = 1;
	while ((line = get_next_line(fd)))
	{
		printf("Linha %d: %s\n", i, line);
		free(line);
		i++;
	}
	close(fd);
	printf("\n");

	printf("=== TESTE 4: Linhas muito longas ===\n");
	fd = open("long.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("❌ Erro ao abrir long.txt\n");
		return (1);
	}
	i = 1;
	while ((line = get_next_line(fd)))
	{
		printf("Linha %d (tamanho %zu): %.50s...\n", i, ft_strlen(line), line);
		free(line);
		i++;
	}
	close(fd);
	printf("\n");

	printf("=== TESTE 5: FD inválido ===\n");
	line = get_next_line(-1);
	if (line == NULL)
		printf("✅ Retornou NULL para FD inválido (correto)\n");
	else
	{
		printf("❌ Deveria retornar NULL\n");
		free(line);
	}
	printf("\n");

	printf("=== TESTE 6: Múltiplas chamadas em arquivo pequeno ===\n");
	fd = open("small.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("❌ Erro ao abrir small.txt\n");
		return (1);
	}
	for (i = 1; i <= 5; i++)
	{
		line = get_next_line(fd);
		if (line)
		{
			printf("Chamada %d: %s", i, line);
			free(line);
		}
		else
			printf("Chamada %d: NULL (fim do arquivo)\n", i);
	}
	close(fd);

	printf("\n=== ✅ TODOS OS TESTES CONCLUÍDOS ===\n");
	return (0);
}
