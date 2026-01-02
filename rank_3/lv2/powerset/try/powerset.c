#include <stdio.h>
#include <stdlib.h>

/**
 * Função recursiva para encontrar subconjuntos cuja soma seja igual ao alvo (target).
 * @param set: O conjunto original de números passados como argumento.
 * @param size: Quantidade total de números no conjunto.
 * @param target: O valor da soma que estamos buscando.
 * @param index: O índice atual no conjunto original (para evitar repetir elementos).
 * @param subset: Array temporário para armazenar o subconjunto que está sendo formado.
 * @param subset_size: Quantidade de elementos atualmente no subconjunto temporário.
 * @param current_sum: A soma acumulada dos elementos presentes no subconjunto atual.
 */
void find_subsets(int *set, int size, int target, int index, int *subset, int subset_size, int current_sum)
{
	// CASO BASE: Se a soma acumulada atingiu exatamente o valor alvo
	if (current_sum == target)
	{
		// Percorre e imprime os elementos do subconjunto encontrado
		for (int i = 0; i < subset_size; i++)
		{
			if (i > 0)
				printf(" "); // Adiciona espaço entre os números
			printf("%d", subset[i]);
		}
		printf("\n");
		// Nota: Não colocamos 'return' aqui porque pode haver combinações com o número '0'
		// que ainda manteriam a soma igual ao target.
	}

	// Loop para explorar as próximas possibilidades a partir do índice atual
	for (int i = index; i < size; i++)
	{
		// 1. INCLUIR: Adiciona o número atual no subconjunto temporário
		subset[subset_size] = set[i];

		// 2. RECURSÃO: Chama a função para o próximo índice (i + 1),
		// atualizando a soma e o tamanho do subconjunto.
		find_subsets(set, size, target, i + 1, subset, subset_size + 1, current_sum + set[i]);

		// 3. BACKTRACKING: Ao retornar da recursão, o loop avança para o próximo 'i'.
		// O valor em subset[subset_size] será sobrescrito na próxima iteração,
		// o que remove o elemento atual da tentativa e testa o próximo.
	}
}

int main(int argc, char **argv)
{
	// Validação: precisa de pelo menos o target e um número no conjunto
	if (argc < 2)
		return (0);

	// O primeiro argumento é o valor alvo da soma
	int target = atoi(argv[1]);
	// O tamanho do conjunto é o total de argumentos menos o nome do programa e o target
	int size = argc - 2;

	// Alocação do conjunto original
	int *set = malloc(sizeof(int) * size);
	if (!set)
		return (1);

	// Preenche o conjunto transformando os argumentos de string para int
	for (int i = 0; i < size; i++)
		set[i] = atoi(argv[i + 2]);

	// Alocação de um buffer para armazenar o subconjunto atual durante a recursão
	int *subset = malloc(sizeof(int) * size);
	if (!subset)
	{
		free(set);
		return (1);
	}

	// Inicia a busca a partir do índice 0 e soma 0
	find_subsets(set, size, target, 0, subset, 0, 0);

	// Liberação de memória obrigatória
	free(set);
	free(subset);
	return (0);
}
