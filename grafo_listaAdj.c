#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "grafo_listaAdj.h"
#include "heap.h"
#include "tempo.h"

Grafo *inicializaGrafo(int numVertices, int numArestas, int numMenoresCaminhos)
{
    Grafo *grafo = (Grafo *)calloc(1, sizeof(Grafo));

    grafo->numVertices = numVertices;

    grafo->listaAdj = (Apontador *)calloc(numVertices, sizeof(Apontador));

    grafo->numArestas = numArestas;

    grafo->numMenoresCaminhos = numMenoresCaminhos;

    return grafo;
}

bool verificaValidadeVertice(int v, Grafo *grafo)
{
    // Verifica se o indice v esta dentro do escopo
    if (v > grafo->numVertices)
    {
        fprintf(stderr, "ERRO: Numero do vertice (%d) maior que o numero total de vertices (%d).\n", v, grafo->numVertices);
        return false;
    }
    if (v < 0)
    {
        fprintf(stderr, "ERRO: Numero do vertice (%d) deve ser positivo.\n", v);
        return false;
    }

    return true;
}

void insereAresta(int v1, int v2, Peso peso, Grafo *grafo)
{
    Apontador p;

    if (!(verificaValidadeVertice(v1, grafo) && verificaValidadeVertice(v2, grafo)))
    {
        return;
    }
    // Aloca memoria para a nova aresta
    if (!(p = (Apontador)calloc(1, sizeof(Aresta))))
    {
        fprintf(stderr, "ERRO: Falha na alocacao de memoria na funcao insereAresta\n");
        return;
    }
    // v2 eh um vertice adjacente a v1
    p->vdestino = v2;
    p->peso = peso;
    // Aponta para o que antes estava na primeira posicao
    p->prox = grafo->listaAdj[v1];
    // A aresta assume a primeira posicao
    grafo->listaAdj[v1] = p;
}

void liberaGrafo(Grafo *grafo)
{

    int v;
    Apontador p;

    for (v = 0; v < grafo->numVertices; v++)
    {
        while ((p = grafo->listaAdj[v]) != NULL)
        {
            grafo->listaAdj[v] = p->prox;
            p->prox = NULL;
            // Libera as arestas asjacentes a v
            free(p);
        }
    }

    grafo->numVertices = 0;
    free(grafo->listaAdj);
    grafo->listaAdj = NULL;

    free(grafo);
    grafo = NULL;
}

Grafo *preencheGrafo(FILE *nomearq)
{

    int numVertices, numArestas, numMenoresCaminhos;
    int v1, v2;
    Peso peso;

    if (nomearq == NULL)
    {
        fprintf(stderr, "ERRO: falha ao abrir arquivo.\n");
        return (NULL);
    }

    if (fscanf(nomearq, "%d %d %d", &numVertices, &numArestas, &numMenoresCaminhos) != 3)
    {
        fprintf(stderr, "ERRO: numero de argumentos de entrada invalido.\n");
        return (NULL);
    }

    // Verifica se os elementos estao dentro dos escopos definidos pelo trabalho
    if (numVertices < 2 || numVertices > 100000)
    {
        printf("ERRO: Numero de vertices invalido.\n");
        return (NULL);
    }

    if (numArestas < 1 || numArestas > 200000)
    {
        printf("ERRO: Numero de arestas invalido.\n");
        return (NULL);
    }

    if (numMenoresCaminhos < 1 || numMenoresCaminhos > 10)
    {
        printf("ERRO: Numero de menores caminhos invalido.\n");
        return (NULL);
    }

    // Commeca a contar o tempo
    tempo tempoInicio = tempoAtual();

    Grafo *grafo = inicializaGrafo(numVertices, numArestas, numMenoresCaminhos);

    for (int i = 1; i <= grafo->numArestas; i++)
    {
        if (fscanf(nomearq, "%d %d %lld", &v1, &v2, &peso) != 3)
        {
            fprintf(stderr, "ERRO 1: numero de argumentos de entrada invalido.\n");
        }
        insereAresta(v1 - 1, v2 - 1, peso, grafo);
    }

    // Para de contar o tempo
    tempo tempoFinal = tempoAtual();

    printf("Tempo de leitura:\n");
    imprimeTempos(tempoInicio, tempoFinal);

    return grafo;
}

void insereAdjacentes(Grafo *grafo, Vertice pai, Heap *heap)
{
    int indicePai = pai.id;
    Vertice filho;
    Apontador q;

    // q = a vertice pai
    q = grafo->listaAdj[indicePai];

    while (q != NULL)
    {
        filho.id = q->vdestino;
        // tecnica de relaxamento
        filho.distancia = q->peso + pai.distancia;

        // Insere os adjacentes ao vertice pai
        insere(heap, filho);
        q = q->prox;
    }
}

Peso *eppstein(Grafo *grafo)
{
    int numVertices = grafo->numVertices;
    int numMenoresCaminhos = grafo->numMenoresCaminhos;

    Heap *minHeap = criaHeapVazia(numVertices);
    // vetor para armazenar quantas vezes um vertice ja saiu da heap
    int *contadores = calloc((numVertices), sizeof(int));

    // Vetor para armazenar os pesos dos menores caminhos
    Peso *menoresCaminhos = calloc(numMenoresCaminhos, sizeof(Peso));
    // Indice para o vetor dos menores caminhos
    int indiceMenores = 0;

    Vertice atual;
    // Vertice que corresponde ao vertice de inicio
    Vertice raiz;
    raiz.id = 0;
    raiz.distancia = 0;

    // Insere o primeiro vertice na fila de prioridade
    insere(minHeap, raiz);

    // Enquanto o vertice de destino não for visitado k vezes
    while (contadores[numVertices - 1] < numMenoresCaminhos)
    {
        if (heapVazia(minHeap))
        {
            break;
        }

        // Vertice que esta sendo analisado = o vertice que tem menor distancia ate o vertice inicial
        atual = extraiMenor(minHeap);

        // Se o vertice ja foi visitado k vezes analisa o proximo vertice da fila
        if (contadores[atual.id] == numMenoresCaminhos)
        {
            continue;
        }

        // Aumenta o contador do vertice pois ele acabou de ser visitado
        contadores[atual.id]++;

        // Se o vertice que esta sendo analisado for o vertice final do caminho encontramos um menor caminho ate ele
        if (atual.id == numVertices - 1)
        {
            menoresCaminhos[indiceMenores] = atual.distancia;
            indiceMenores++;
            continue;
        }

        // insere todos os adjacentes ao vertice atual na heap
        insereAdjacentes(grafo, atual, minHeap);
    }

    destroiHeap(minHeap);

    free(contadores);

    return menoresCaminhos;
}

void imprimeMenoresCaminhos(FILE *nomearqEscrita, Grafo *grafo)
{
    // Comeca a contar o tempo
    tempo tempoInicio = tempoAtual();

    Peso *menoresCaminhos = eppstein(grafo);

    tempo tempoFinal = tempoAtual();
    // Termina de contar o tempo

    double tempoTotal = tempoDecorrido(tempoInicio.tv, tempoFinal.tv);

    printf("Tempo de execucao:\n");
    imprimeTempos(tempoInicio, tempoFinal);

    if (nomearqEscrita == NULL)
    {
        fprintf(stderr, "ERRO: falha ao abrir arquivo.\n");
        return;
    }

    for (int i = 0; i < grafo->numMenoresCaminhos; i++)
    {
        fprintf(nomearqEscrita, "%lld ", menoresCaminhos[i]);
    }
    fprintf(nomearqEscrita, "\n");

    free(menoresCaminhos);
}