#include <stdio.h>
#include <stdlib.h>
#include <math.h>   // Para sqrtf
#include <float.h>  // Para FLT_MAX

// Estrutura para armazenar as coordenadas de uma cidade
typedef struct {
    float x;
    float y;
} City;

/**
 * Calcula a distância euclidiana entre duas cidades.
 * Usa o teorema de Pitágoras: hipotenusa = sqrt(dx² + dy²)
 */
float distance(City a, City b)
{
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return sqrtf(dx * dx + dy * dy);
}

/**
 * Calcula o comprimento total de um caminho (path).
 * O path contém os índices das cidades na ordem de visita.
 */
float calculate_path_length(City *cities, int *path, int n)
{
    float total = 0.0f;

    // Soma as distâncias entre cidades consecutivas no caminho
    for (int i = 0; i < n - 1; i++)
        total += distance(cities[path[i]], cities[path[i + 1]]);

    // OBRIGATÓRIO: Adiciona a distância da última cidade de volta para a primeira
    // Isso fecha o ciclo exigido pelo "Traveling Salesman Problem"
    total += distance(cities[path[n - 1]], cities[path[0]]);

    return total;
}

/**
 * Função utilitária para trocar dois índices no array de caminhos.
 */
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * Função de Backtracking que gera todas as permutações possíveis das cidades.
 * n! combinações são testadas (onde n <= 11).
 */
void find_shortest_path(City *cities, int *path, int start, int n, float *min_length)
{
    // CASO BASE: Uma permutação completa foi gerada
    if (start == n - 1)
    {
        float length = calculate_path_length(cities, path, n);
        // Se este caminho for menor que o recorde atual, atualiza o recorde
        if (length < *min_length)
            *min_length = length;
        return;
    }

    // Loop de permutação: fixa uma cidade e permuta o restante
    for (int i = start; i < n; i++)
    {
        swap(&path[start], &path[i]); // Troca
        find_shortest_path(cities, path, start + 1, n, min_length); // Recursão
        swap(&path[start], &path[i]); // Backtrack (desfaz a troca)
    }
}

int main(void)
{
    City cities[12]; // Enunciado garante no máximo 11 cidades
    int n = 0;

    // Lê as cidades do stdin no formato "x, y"
    // scanf retorna a quantidade de itens lidos com sucesso
    while (n < 12 && scanf("%f, %f\n", &cities[n].x, &cities[n].y) == 2)
        n++;

    // Se nenhuma cidade foi lida, encerra silenciosamente
    if (n == 0)
        return (0);

    // Inicializa o array 'path' com a ordem padrão (0, 1, 2, ..., n-1)
    int path[12];
    for (int i = 0; i < n; i++)
        path[i] = i;

    // Inicializa a menor distância com o maior valor possível para um float
    float min_length = FLT_MAX;

    // Inicia a busca exaustiva por todas as rotas
    find_shortest_path(cities, path, 0, n, &min_length);

    // Imprime o resultado final formatado com 2 casas decimais
    printf("%.2f\n", min_length);

    return (0);
}
