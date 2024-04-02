#include "dijkstra.h"
#include <stdio.h>
#include <stdlib.h>

Caminho *criaVetorCaminho(int numVertices)
{
    Caminho *caminho = (Caminho *)malloc(1 * sizeof(Caminho));
    caminho->vertices = (Vertice *)calloc(numVertices, sizeof(Vertice));
    caminho->tamCaminho = 0;
    return caminho;
}

Caminho *dijkstra(Grafo *grafo, int fonte)
{
    Heap *heap = criaHeap(grafo->numVertices, fonte);
    Caminho *caminho = criaVetorCaminho(grafo->numVertices);
    Caminho *menorCaminho = criaVetorCaminho(grafo->numVertices);

    Vertice min;
    Apontador q;
    int indiceHeap;
    int indiceCaminho = 0;
    Peso pesoCaminho = 0;

    while (heap->tamanho >= 1)
    {
        min = extractMin(heap);

        caminho->vertices[indiceCaminho] = min;
        caminho->tamCaminho++;

        if (min.id == grafo->numVertices)
        {
            break;
        }

        q = grafo->listaAdj[min.id];
        while (q != NULL)
        {
            indiceHeap = pesquisaHeap(heap, q->vdestino);
            if (indiceHeap == -1)
            {
                q = q->prox;
            }

            else
            {
                if (q->peso + min.distancia < heap->naoVisitados[indiceHeap].distancia)
                {
                    heap->naoVisitados[indiceHeap].distancia = q->peso + min.distancia;
                    heap->naoVisitados[indiceHeap].verticePai = min.id;
                    heap->naoVisitados[indiceHeap].idVerticePai = indiceCaminho;
                }
                q = q->prox;
            }
        }
        minHeapify(heap, 0);
        indiceCaminho++;
    }

    int i = 0;

    if (caminho->vertices[indiceCaminho].verticePai == 0)
    {
        return menorCaminho;
    }

    while (caminho->vertices[indiceCaminho].verticePai != -1)
    {
        menorCaminho->vertices[i] = caminho->vertices[indiceCaminho];
        pesoCaminho += obtemPesoAresta(caminho->vertices[indiceCaminho].verticePai, caminho->vertices[indiceCaminho].id, grafo);
        indiceCaminho = caminho->vertices[indiceCaminho].idVerticePai;
        i++;
    }
    menorCaminho->vertices[i] = caminho->vertices[indiceCaminho];
    menorCaminho->tamCaminho = i + 1;

    destroiHeap(heap);

    free(caminho->vertices);
    free(caminho);

    menorCaminho->pesoCaminho = pesoCaminho;
    menorCaminho = organizaCaminho(menorCaminho);

    return menorCaminho;
}

Caminho *organizaCaminho(Caminho *caminho)
{
    int inicio = 0;
    int fim = caminho->tamCaminho - 1;
    Vertice temp;
    while (inicio < fim)
    {
        temp = caminho->vertices[inicio];
        caminho->vertices[inicio] = caminho->vertices[fim];
        caminho->vertices[fim] = temp;
        inicio++;
        fim--;
    }

    return caminho;
}