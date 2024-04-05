#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "grafo_listaAdj.h"
#include "heap.h"
#include "tempo.h"

/*                    inicializaGrafo (TipoGrafo* grafo, int numvertices): Cria um grafo com n vertices.

    Aloca espaco para o vetor de apontadores de listas de adjacencias e,
    para cada vertice, inicializa o apontador de sua lista de adjacencia.
    Retorna true se inicializou com sucesso e false caso contrario.


    vertices vao de 1 a numvertices.
*/

Grafo *inicializaGrafo(int numVertices, int numArestas, int numMenoresCaminhos)
{

    Grafo *grafo = (Grafo *)calloc(1, sizeof(Grafo));

    grafo->numVertices = numVertices;

    grafo->listaAdj = (Apontador *)calloc(numVertices, sizeof(Apontador));

    // for num vert

    grafo->numArestas = numArestas;

    grafo->numMenoresCaminhos = numMenoresCaminhos;

    // calloc ja inicializa com zeros.... nao precisa inicializar grafo->listaAdj[i]

    return grafo;
}

bool verificaValidadeVertice(int v, Grafo *grafo)
{
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
bool listaAdjVazia(int v, Grafo *grafo)
{

    if (!verificaValidadeVertice(v, grafo))
        return false;

    return (grafo->listaAdj[v] == NULL);
}

Apontador proxListaAdj(int v, Grafo *grafo, Apontador atual)
{

    if (atual == NULL)
    {
        fprintf(stderr, "atual == NULL\n");
        return VERTICE_INVALIDO;
    }
    return (atual->prox);
}

void insereAresta(int v1, int v2, Peso peso, Grafo *grafo)
{

    Apontador p;

    if (!(verificaValidadeVertice(v1, grafo) && verificaValidadeVertice(v2, grafo)))
    {
        return;
    }
    if (!(p = (Apontador)calloc(1, sizeof(Aresta))))
    {
        fprintf(stderr, "ERRO: Falha na alocacao de memoria na funcao insereAresta\n");
        return;
    }
    p->vdestino = v2;
    p->peso = peso;
    p->prox = grafo->listaAdj[v1]; // insere no inicio
    grafo->listaAdj[v1] = p;
}

bool removeAresta(int v1, int v2, Grafo *grafo)
{

    Apontador q, anterior;

    if (!(verificaValidadeVertice(v1, grafo) && verificaValidadeVertice(v2, grafo)))
    {
        return ARESTA_NULA;
    }

    q = grafo->listaAdj[v1];

    while ((q != NULL) && (q->vdestino != v2))
    {
        anterior = q;
        q = q->prox;
    }

    if (q != NULL)
    {
        if (grafo->listaAdj[v1] == q)
        {
            grafo->listaAdj[v1] = q->prox;
            free(q);
            q = NULL;
        }
        else
        {
            anterior->prox = q->prox;
            free(q);
            q = NULL;
            return true;
        }
    }

    return false;
}

Apontador primeiroListaAdj(int v, Grafo *grafo)
{
    return (grafo->listaAdj[v]);
}

bool existeAresta(int v1, int v2, Grafo *grafo)
{

    Apontador q;

    if (!(verificaValidadeVertice(v1, grafo) && verificaValidadeVertice(v2, grafo)))
    {
        return false;
    }

    q = grafo->listaAdj[v1];

    while ((q != NULL) && (q->vdestino != v2))
    {
        q = q->prox;
    }

    if (q != NULL)
    {
        return true;
    }

    return false;
}

Apontador encontraAresta(int v1, int v2, Grafo *grafo)
{

    Apontador q;

    if (!(verificaValidadeVertice(v1, grafo) && verificaValidadeVertice(v2, grafo)))
    {
        return NULL;
    }

    q = grafo->listaAdj[v1];

    while ((q != NULL) && (q->vdestino != v2))
    {
        q = q->prox;
    }

    if (q != NULL)
    {
        return q;
    }

    return NULL;
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
            free(p);
        }
    }

    // for (int i = 0; i < grafo->numVertices + 1; i++)
    // {
    //     free(grafo->listaAdj[i]);
    // }

    grafo->numVertices = 0;
    free(grafo->listaAdj);
    grafo->listaAdj = NULL;

    free(grafo);
    grafo = NULL;
}

void imprimeGrafo(char *nomearq, Grafo *grafo)
{

    FILE *fp;
    int v;
    Apontador p;

    fp = fopen(nomearq, "w");

    if (fp == NULL)
    {
        fprintf(stderr, "ERRO: falha ao abrir arquivo.\n");
        return;
    }

    for (v = 1; v <= grafo->numVertices; v++)
    {
        p = grafo->listaAdj[v];
        while (p != NULL)
        {
            fprintf(fp, "%d ---> %d\n", v, p->vdestino);
            p = p->prox;
        }
    }
}

Grafo *leGrafo(FILE * nomearq)
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

    if(numVertices < 2 || numVertices > 100000){
        printf("ERRO: Numero de vertices invalido.\n");
        return (NULL);
    }

    if(numArestas < 1 || numArestas > 200000){
        printf("ERRO: Numero de arestas invalido.\n");
        return (NULL);
    }

    if(numMenoresCaminhos < 1 || numMenoresCaminhos > 10){
        printf("ERRO: Numero de menores caminhos invalido.\n");
        return (NULL);
    }

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

    tempo tempoFinal = tempoAtual();

    printf("Tempo de leitura:\n");
    imprimeTempos(tempoInicio, tempoFinal);

    return grafo;
}

Peso obtemPesoAresta(int v1, int v2, Grafo *grafo)
{
    Apontador p;

    p = encontraAresta(v1, v2, grafo);

    if (p == NULL)
    {
        fprintf(stderr, "ERRO: numero de argumentos de entrada invalido.\n");
        return (ARESTA_NULA);
    }

    return (p->peso);
}


Peso *eppstein(Grafo *grafo)
{
    int numVertices = grafo->numVertices;
    int numMenoresCaminhos = grafo->numMenoresCaminhos;

    Heap *minHeap = criaHeapVazia(numVertices);
    int *contadores = calloc((numVertices), sizeof(int));

    Peso *menoresCaminhos = calloc(numMenoresCaminhos, sizeof(Peso));
    int indiceMenores = 0;

    Vertice atual;
    Vertice raiz;
    raiz.id = 0;
    raiz.distancia = 0;

    insert(minHeap, raiz);

    while (contadores[numVertices - 1] < numMenoresCaminhos)
    {
        if (getSizeHeap(minHeap))
        {
            break;
        }

        atual = extractMin(minHeap);

        if (contadores[atual.id] == numMenoresCaminhos)
        {
            continue;
        }

        contadores[atual.id]++;

        if (atual.id == numVertices - 1)
        {
            menoresCaminhos[indiceMenores] = atual.distancia;
            indiceMenores++;
            continue;
        }

        insereFihos(grafo, atual, minHeap);
    }

    destroiHeap(minHeap);

    free(contadores);

    return menoresCaminhos;
}

void insereFihos(Grafo *grafo, Vertice pai, Heap *heap)
{
    int indicePai = pai.id;
    Vertice filho;
    Apontador q;

    q = grafo->listaAdj[indicePai];

    while (q != NULL)
    {
        filho.id = q->vdestino;
        filho.distancia = q->peso + pai.distancia;

        insert(heap, filho);
        q = q->prox;
    }

}

void imprimeMenoresCaminhos(FILE *nomearqEscrita, Grafo *grafo)
{
    tempo tempoInicio = tempoAtual();

    Peso *menoresCaminhos = eppstein(grafo);

    tempo tempoFinal = tempoAtual();

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