#include <stdlib.h> // Necessário para malloc e free
#include <stdio.h>  // Necessário para fprintf (stdout) e printf, e atoi (conversão de argumento)

// Função auxiliar para calcular o valor absoluto (módulo) de um inteiro.
// É essencial para a verificação de ataque diagonal (Delta).
int	ft_abs(int n)
{
	if (n < 0)
		return (-n); // Se for negativo, retorna o valor positivo.
	return (n); // Se for positivo ou zero, retorna o próprio valor.
}

// Verifica se é seguro colocar uma rainha na posição (col, row)
// em relação a todas as rainhas já colocadas nas colunas anteriores (prev).
// O tabuleiro é representado pelo vetor 'board'.
// col: A coluna atual que estamos tentando preencher.
// row: A linha que estamos testando na coluna atual.
int	is_safe(int *board, int col, int row)
{
	int	prev = 0; // Iterador para as colunas ANTERIORES.

	// Percorre todas as colunas já preenchidas (prev de 0 até col - 1).
	while (prev < col)
	{
		// 1. Verificação de Ataque Horizontal (Mesma Linha)
		// O valor em board[prev] é a linha onde a rainha anterior está.
		// Se a linha anterior for igual à linha atual (row), há ataque.
		if (board[prev] == row)
			return (0); // Não é seguro.

		// 2. Verificação de Ataque Diagonal (Lógica do Delta)
		// Verifica se a distância vertical é igual à distância horizontal.
		// Distância Vertical (Delta Y): ft_abs(linha_anterior - linha_atual)
		// Distância Horizontal (Delta X): coluna_atual (col) - coluna_anterior (prev)
		if (ft_abs(board[prev] - row) == col - prev)
			return (0); // Não é seguro.

		prev++; // Próxima coluna anterior a ser verificada.
	}
	return (1); // É seguro colocar a rainha aqui.
}

// Imprime uma solução válida encontrada, seguindo o formato esperado.
// board: O vetor que armazena a posição da rainha em cada coluna.
// n: O tamanho do tabuleiro (N).
void	print_solution(int *board, int n)
{
	int	i = 0;

	// Percorre o vetor de posicionamento de 0 a N-1.
	while (i < n)
	{
		// Imprime a linha (posição vertical) da rainha na coluna 'i'.
		fprintf(stdout, "%d", board[i]);

		// Imprime um espaço entre os números, exceto após o último.
		if (i < n - 1)
			fprintf(stdout, " ");
		i++;
	}
	fprintf(stdout, "\n"); // Pula uma linha após a solução completa.
}

// Função principal de Backtracking (Retrocesso).
// board: O vetor para armazenar as posições (Solução em construção).
// col: A coluna que estamos tentando preencher nesta chamada recursiva.
// n: O tamanho do tabuleiro (N).
void	solve(int *board, int col, int n)
{
	int	row = 0; // Iterador para testar todas as linhas (0 a N-1) na coluna atual (col).

	// CASO BASE (Condição de Parada e Sucesso):
	// Se a coluna atual (col) for igual a N, significa que preenchemos com sucesso
	// N rainhas em N colunas diferentes sem ataque. Encontramos uma solução!
	if (col == n)
	{
		print_solution(board, n);
		return ; // Volta para a chamada anterior para tentar outras combinações.
	}

	// ITERAÇÃO E RECURSÃO (Tentativa e Erro)
	// Tenta colocar a rainha em cada linha da coluna atual.
	while (row < n)
	{
		// 1. TENTATIVA (Chamada ao is_safe)
		// Se for seguro colocar a rainha na posição (coluna, linha)
		if (is_safe(board, col, row))
		{
			// 2. COLOCAR
			// Define a linha (row) da rainha na coluna atual (col).
			board[col] = row;

			// 3. RECURSÃO (Busca em Profundidade)
			// Chama solve para a próxima coluna (col + 1).
			solve(board, col + 1, n);

			// 4. RETROCESSO (BACKTRACKING)
			// Não precisamos de um código explícito para "remover" a rainha.
			// Quando o loop continua (row++), o próximo 'board[col] = row;' irá
			// sobrescrever o valor, e se a recursão voltar aqui sem sucesso,
			// a rainha colocada em 'col' será implicitamente desconsiderada
			// para a próxima iteração do loop 'while (row < n)'.
		}
		row++; // Tenta a próxima linha.
	}
}

// Função principal do programa.
int	main(int ac, char **av)
{
	int	n;
	int	*board;

	// Deve receber exatamente um argumento (o N do tabuleiro N x N).
	if (ac != 2)
		return (1);

	// Converte o argumento da linha de comando para inteiro (N).
	n = atoi(av[1]);

	// Aloca memória para o vetor de posicionamento (board) de tamanho N.
	// Este vetor armazenará a linha da rainha em cada coluna.
	board = malloc(sizeof(int) * n);
	if (!board)
		return (1); // Erro de alocação de memória.

	// Inicia o processo de solução, começando na coluna 0.
	solve(board, 0, n);

	// Libera a memória alocada antes de sair.
	free(board);
	return (0);
}
