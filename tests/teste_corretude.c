#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/grafo.h"
#include "../include/BFS.h"

extern Graph *graph;
extern COLOR *color;
extern int *parent;
extern int *distance;

void BFS_Sequencial(Graph *graph, int start);
void BFS_Concorrente(int inicio, int num_threads);

typedef struct {
    int vertices;
    int arestas;
    int threads[5];
    int qtd_threads;
} CasoCorretude;

// Compara se as distâncias são iguais.
static int compara_distancias(const int *esperado, const int *obtido, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (esperado[i] != obtido[i]) {
            return i; // Retorna índice onde há diferença
        }
    }
    return -1; // Tudo igual
}

// Valida se os pais são consistentes com as distâncias.
static int valida_pais(const int *distancias, const int *pais, int tamanho, int inicio) {
    for (int i = 0; i < tamanho; i++) {
        // Vértice inicial não deve ter pai
        if (i == inicio) {
            if (pais[i] != -1) return i;
            continue;
        }

        // Vértice inalcançável não deve ter pai
        if (distancias[i] == -1) {
            if (pais[i] != -1) return i;
            continue;
        }

        // Pai deve ser válido e estar a distância correta
        int pai = pais[i];
        if (pai < 0 || pai >= tamanho) return i;
        if (distancias[pai] != distancias[i] - 1) return i;
    }
    return -1; // Tudo válido
}

int main(void) {
    CasoCorretude casos[] = {
        {10, 15, {1, 2, 4}, 3},
        {100, 250, {1, 2, 4, 8}, 4},
        {250, 300, {1, 2, 4, 8}, 4},
        {500, 500, {1, 2, 4, 8}, 4},
        {1000, 2500, {1, 2, 4, 8}, 4}
    };

    const int quantidade_casos = sizeof(casos) / sizeof(casos[0]);
    const int vertice_inicial = 0;

    printf("=================================================================\n");
    printf("TESTES DE CORRETUDE - BFS CONCORRENTE\n");
    printf("=================================================================\n\n");

    for (int i = 0; i < quantidade_casos; i++) {
        CasoCorretude *caso = &casos[i];

        printf("Caso %d/%d: %d vertices, %d arestas\n", 
               i + 1, quantidade_casos, caso->vertices, caso->arestas);

        // Gera o grafo
        Graph *grafo = gerar_grafo_aleatorio(caso->vertices, caso->arestas);
        graph = grafo;

        // Executa BFS sequencial (referência)
        BFS_Sequencial(grafo, vertice_inicial);

        // Salva resultados da versão sequencial
        int *distancias_seq = malloc(sizeof(int) * caso->vertices);
        if (!distancias_seq) {
            fprintf(stderr, "ERRO: Falha ao alocar memória\n");
            return 1;
        }
        memcpy(distancias_seq, distance, sizeof(int) * caso->vertices);

        // Testa com diferentes números de threads
        for (int t = 0; t < caso->qtd_threads; t++) {
            int num_threads = caso->threads[t];

            graph = grafo;
            BFS_Concorrente(vertice_inicial, num_threads);

            // Verifica distâncias
            int erro_dist = compara_distancias(distancias_seq, distance, caso->vertices);
            if (erro_dist != -1) {
                fprintf(stderr,
                        "  FALHA com %d threads: distância incorreta no vértice %d (esperado=%d, obtido=%d)\n",
                        num_threads, erro_dist, distancias_seq[erro_dist], distance[erro_dist]);
                free(distancias_seq);
                freeGraph(grafo);
                return 1;
            }

            // Verifica pais
            int erro_pai = valida_pais(distancias_seq, parent, caso->vertices, vertice_inicial);
            if (erro_pai != -1) {
                fprintf(stderr,
                        "FALHA com %d threads: pai inconsistente no vértice %d (pai=%d, dist=%d)\n",
                        num_threads, erro_pai, parent[erro_pai], distance[erro_pai]);
                free(distancias_seq);
                freeGraph(grafo);
                return 1;
            }

            printf("%d threads: OK\n", num_threads);
        }

        free(distancias_seq);
        freeGraph(grafo);
        printf("\n");
    }

    printf("=================================================================\n");
    printf("Todos os %d testes de corretude passaram!\n", quantidade_casos);
    printf("=================================================================\n");
    
    return 0;
}
