#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include "eppstein.h"

void insereFihos(Grafo *grafo, Vertice pai, Heap *heap);

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

    // minHeapify(heap, 0);
}

void imprimeMenoresCaminhos(char *nomearqEscrita, Grafo *grafo)
{
    Peso *menoresCaminhos = eppstein(grafo);
    FILE *fp;

    fp = fopen(nomearqEscrita, "w");

    if (fp == NULL)
    {
        fprintf(stderr, "ERRO: falha ao abrir arquivo.\n");
        return;
    }

    for (int i = 0; i < grafo->numMenoresCaminhos; i++)
    {
        fprintf(fp, "%lld ", menoresCaminhos[i]);
    }
    fprintf(fp, "\n");

    free(menoresCaminhos);

    fclose(fp);
}