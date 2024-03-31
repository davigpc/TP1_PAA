#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

// Define a createHeap function
Heap *criaHeap(int capacidade, int fonte)
{
    // Allocating memory to Heap h
    Heap *h = (Heap *)malloc(1 * sizeof(Heap));

    // set the values to size and capacidade
    h->tamanho = 0;
    h->capacidade = capacidade;

    // Allocating memory to array
    h->naoVisitados = (Vertice *)malloc(capacidade * sizeof(Vertice));

    int i;

    for (i = 0; i < capacidade; i++)
    {
        h->naoVisitados[i].id = i + 1;
        h->naoVisitados[i].distancia = PESO_MAXIMO;
        h->naoVisitados[i].verticePai = 0;
    }

    h->naoVisitados[fonte - 1].distancia = 0;
    h->naoVisitados[fonte - 1].verticePai = -1;

    h->tamanho = i;
    i = (h->tamanho - 2) / 2;
    while (i >= 0)
    {
        minHeapify(h, i);
        i--;
    }
    return h;
}

// Defining insertHelper function
void insertHelper(Heap *h, int index)
{

    // Store parent of element at index
    // in parent variable
    int parent = (index - 1) / 2;

    if (h->naoVisitados[parent].distancia > h->naoVisitados[index].distancia)
    {
        // Swapping when child is smaller
        // than parent element
        Vertice temp = h->naoVisitados[parent];
        h->naoVisitados[parent] = h->naoVisitados[index];
        h->naoVisitados[index] = temp;

        // Recursively calling insertHelper
        insertHelper(h, parent);
    }
}

void minHeapify(Heap *h, int index)
{
    int esquerda = index * 2 + 1;
    int direita = index * 2 + 2;
    int min = index;

    // Checking whether our esquerda or child element
    // is at direita index or not to avoid index error
    if (esquerda >= h->tamanho || esquerda < 0)
        esquerda = -1;
    if (direita >= h->tamanho || direita < 0)
        direita = -1;

    // store esquerda or direita element in min if
    // any of these is smaller that its parent
    if (esquerda != -1 && h->naoVisitados[esquerda].distancia < h->naoVisitados[index].distancia)
        min = esquerda;
    if (direita != -1 && h->naoVisitados[direita].distancia < h->naoVisitados[min].distancia)
        min = direita;

    // Swapping the nodes
    if (min != index)
    {
        Vertice temp = h->naoVisitados[min];
        h->naoVisitados[min] = h->naoVisitados[index];
        h->naoVisitados[index] = temp;

        // recursively calling for their child elements
        // to maintain min Heap
        minHeapify(h, min);
    }
}

Vertice extractMin(Heap *h)
{
    Vertice deleteItem;

    // Store the node in deleteItem that
    // is to be deleted.
    deleteItem = h->naoVisitados[0];

    // Replace the deleted node with the last node
    h->naoVisitados[0] = h->naoVisitados[h->tamanho - 1];

    // Decrement the size of Heap
    h->tamanho--;

    // Call minHeapify_top_down for 0th index
    // to maintain the Heap property
    minHeapify(h, 0);
    return deleteItem;
}

// Define a insert function
void insert(Heap *h, Vertice data)
{

    // Checking if Heap is full or not
    if (h->tamanho < h->capacidade)
    {
        // Inserting data into an array
        h->naoVisitados[h->tamanho] = data;
        // Calling insertHelper function
        insertHelper(h, h->tamanho);
        // Incrementing size of array
        h->tamanho++;
    }
}

void printHeap(Heap *h)
{

    for (int i = 0; i < h->tamanho; i++)
    {
        printf("%d ", h->naoVisitados[i].id);
    }
    printf("\n");
}

void destroiHeap(Heap *h)
{
    free(h->naoVisitados);
    free(h);
}

int pesquisaHeap(Heap *h, int id)
{
    int i;
    for (i = 0; i < h->tamanho; i++)
    {
        if (id == h->naoVisitados[i].id)
        {
            return i;
        }
    }
    return -1;
}

void imprimeHeap(Heap *h)
{
    for (int i = 0; i < h->tamanho; i++)
    {
        printf("%d  %d", h->naoVisitados[i].id, h->naoVisitados[i].distancia);
    }
}