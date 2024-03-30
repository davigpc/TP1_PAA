#include "dijkstra.h"
#include <stdio.h>
#include <stdlib.h>

Caminho *criaVetorCaminho(int numVertices)
{
    Caminho *caminho = (Caminho *)calloc(1, sizeof(Caminho));
    caminho->vertices = (Vertice *)calloc(numVertices, sizeof(Vertice));
    caminho->tamCaminho = 0;
    return caminho;
}

int dijkstra(Grafo *grafo)
{
    Heap *heap = criaHeap(grafo->numVertices);
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
                }
                q = q->prox;
            }
        }
        minHeapify(heap, 0);
        indiceCaminho++;
    }

    int i = 0;
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

    menorCaminho->pesoCaminho = pesoCaminho;
    organizaCaminho(menorCaminho);

    return menorCaminho;
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

void organizaCaminho(Caminho *caminnho)
{
    int inicio = 0;
    int fim = caminnho->tamCaminho - 1;
    Vertice temp;
    while (inicio < fim)
    {
        temp = caminnho->vertices[inicio];
        caminnho->vertices[inicio] = caminnho->vertices[fim];
        caminnho->vertices[fim] = temp;
        inicio++;
        fim++;
    }
}

// void imprimeMenorCaminho(char *nomearq, Grafo *grafo)
// {
//     FILE *fp;
//     int menorCaminho;

//     menorCaminho = dijkstra(grafo);

//     fp = fopen(nomearq, "w");

//     if (fp == NULL)
//     {
//         fprintf(stderr, "ERRO: falha ao abrir arquivo.\n");
//         return;
//     }

//     fprintf(fp, "%d \n", menorCaminho);
// }