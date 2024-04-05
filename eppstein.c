#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include "eppstein.h"

Peso *eppstein(Grafo *grafo)
{
    int numVertices = grafo->numVertices;
    int numMenoresCaminhos = grafo->numMenoresCaminhos;

    Heap *minHeap = criaHeapVazia;
    int *contadores = calloc((numVertices + 1), sizeof(int));

    Peso *menoresCaminhos = malloc(numMenoresCaminhos * sizeof(Peso));
    int indiceMenores = 0;

    Vertice atual;
    Vertice raiz;
    raiz.id = 1;
    raiz.distancia = 0;

    insereFihos(grafo, raiz, minHeap, contadores);

    while (contadores[numVertices] < numMenoresCaminhos)
    {
        atual = extractMin(minHeap);

        if (contadores[atual.id] == numMenoresCaminhos)
        {
            continue;
        }

        contadores[atual.id]++;

        if (atual.id == numVertices)
        {
            menoresCaminhos[indiceMenores] = atual.distancia;
        }

        insereFihos(grafo, atual, minHeap, contadores);
    }

    return menoresCaminhos;
}

void insereFihos(Grafo *grafo, Vertice pai, Heap *heap, int *contadores)
{
    int indicePai = pai.id;
    Vertice filho;
    Apontador q;

    q = grafo->listaAdj[indicePai];

    while (q != NULL)
    {
        filho.id = q->vdestino;
        filho.distancia = q->peso + pai.distancia;
        contadores[q->vdestino]++;

        insert(heap, filho);
        q = q->prox;
    }
}