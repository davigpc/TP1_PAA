#include <stdio.h>
#include <stdlib.h>

#include "grafo_listaAdj.h"
#include "heap.h"

Heap *criaHeapVazia(int capacidade)
{
    Heap *h = (Heap *)malloc(1 * sizeof(Heap));

    h->tamanho = 0;
    h->capacidade = capacidade;

    h->vertices = (Vertice *)malloc(capacidade * sizeof(Vertice));

    return h;
}

void ajudaInserir(Heap *h, int index)
{

    // Guarda posicao do pai do elemento que esta em index
    int pai = (index - 1) / 2;

    if (h->vertices[pai].distancia > h->vertices[index].distancia)
    {
        // Troca quando o filho eh menor que o pai
        Vertice temp = h->vertices[pai];
        h->vertices[pai] = h->vertices[index];
        h->vertices[index] = temp;

        // Chamada recursiva da funcao
        ajudaInserir(h, pai);
    }
}

void minHeapify(Heap *h, int index)
{
    int esquerda = index * 2 + 1;
    int direita = index * 2 + 2;
    int min = index;

    // Verifica se os indices esquerda e direita estão dentro do escopo da heapp
    if (esquerda >= h->tamanho || esquerda < 0)
        esquerda = -1;
    if (direita >= h->tamanho || direita < 0)
        direita = -1;

    // Armazena os indices esquerda e direita caso seus elementos sejam menores que seu no pai
    if (esquerda != -1 && h->vertices[esquerda].distancia < h->vertices[min].distancia)
        min = esquerda;
    if (direita != -1 && h->vertices[direita].distancia < h->vertices[min].distancia)
        min = direita;

    // Troca os vertices
    if (min != index)
    {
        Vertice temp = h->vertices[min];
        h->vertices[min] = h->vertices[index];
        h->vertices[index] = temp;

        // Chamada recursiva para manter as propriedades da minheap
        minHeapify(h, min);
    }
}

Vertice extraiMenor(Heap *h)
{
    Vertice deletaItem;
    int i = 0;
    int indice = 0;

    // Armazena o vertice a ser deletado em deleta item
    deletaItem = h->vertices[0];

    // Substitui o vertice a ser deletado pelo ultimo vertice
    h->vertices[0] = h->vertices[h->tamanho - 1];

    // Diminui o tamanho da heap
    h->tamanho--;

    // Chamada recursiva para manter as propriedades da minheap
    minHeapify(h, 0);
    return deletaItem;
}

void insere(Heap *h, Vertice data)
{

    // Verifica se a heap esta cheia
    if (h->tamanho < h->capacidade)
    {
        // insere o elemento dentro da heap
        h->vertices[h->tamanho] = data;

        ajudaInserir(h, h->tamanho);
        // Aumenta o tamanho da heap
        h->tamanho++;
    }
    // Se a heap estiver cheia aumenta sua capacidade
    else
    {
        h->capacidade = 2 * h->capacidade;
        h->vertices = (Vertice *)realloc((h->vertices), h->capacidade * sizeof(Vertice));

        insere(h, data);
    }
}

void destroiHeap(Heap *h)
{
    free(h->vertices);
    free(h);
}

bool heapVazia(Heap *heap)
{
    if (heap->tamanho == 0)
    {
        return true;
    }

    return false;
}