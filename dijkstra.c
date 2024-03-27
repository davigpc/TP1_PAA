#include "dijkstra.h"
#include <stdio.h>
#include <stdlib.h>

Vertice *criaVetorCaminho(int numVertices)
{
    return (Vertice *)calloc(numVertices, sizeof(Vertice));
}

int dijkstra(Grafo *grafo)
{
    Heap *heap = criaHeap(grafo->numVertices);
    Vertice *caminho = criaVetorCaminho(grafo->numVertices);

    Vertice min;
    Apontador q;
    int indice;
    int indiceCaminho = 0;
    int caminhoTotal = 0;

    while (heap->tamanho >= 1)
    {
        min = extractMin(heap);

        caminho[indiceCaminho] = min;

        if (min.id == grafo->numVertices)
        {
            break;
        }

        q = grafo->listaAdj[min.id];
        while (q != NULL)
        {
            indice = pesquisaHeap(heap, q->vdestino);
            if (indice == -1)
            {
                q = q->prox;
            }

            else
            {
                if (q->peso + min.distancia < heap->naoVisitados[indice].distancia)
                {
                    heap->naoVisitados[indice].distancia = q->peso + min.distancia;
                    heap->naoVisitados[indice].verticePai = min.id;
                }
                q = q->prox;
            }
        }
        minHeapify(heap, 0);
        indiceCaminho++;
    }

    while (caminho[indiceCaminho].verticePai != -1)
    {
        caminhoTotal += obtemPesoAresta(caminho[indiceCaminho].verticePai, caminho[indiceCaminho].id, grafo);
        indiceCaminho = pesquisaCaminho(caminho, caminho[indiceCaminho].verticePai);
    }

    destroiHeap(heap);

    return caminhoTotal;
}

int pesquisaCaminho(Vertice *caminho, int id)
{
    Vertice *c = caminho;
    int i = 0;
    while (c)
    {
        if (id == c->id)
        {
            return i;
        }
        i++;
        c++;
    }

    return -1;
}

void imprimeMenorCaminho(char *nomearq, Grafo *grafo)
{
    FILE *fp;
    int menorCaminho;

    menorCaminho = dijkstra(grafo);

    fp = fopen(nomearq, "w");

    if (fp == NULL)
    {
        fprintf(stderr, "ERRO: falha ao abrir arquivo.\n");
        return;
    }

    fprintf(fp, "%d \n", menorCaminho);
}