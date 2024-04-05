#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

// Define a createHeap function
Heap *criaHeapVazia(int capacidade)
{
    // Allocating memory to Heap h
    Heap *h = (Heap *)malloc(1 * sizeof(Heap));

    // set the values to size and capacidade
    h->tamanho = 0;
    h->capacidade = capacidade;

    // Allocating memory to array
    h->vertices = (Vertice *)malloc(capacidade * sizeof(Vertice));

    return h;
}

// Defining insertHelper function
void insertHelper(Heap *h, int index)
{

    // Store parent of element at index
    // in parent variable
    int parent = (index - 1) / 2;

    if (h->vertices[parent].distancia > h->vertices[index].distancia)
    {
        // Swapping when child is smaller
        // than parent element
        Vertice temp = h->vertices[parent];
        h->vertices[parent] = h->vertices[index];
        h->vertices[index] = temp;

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
    if (esquerda != -1 && h->vertices[esquerda].distancia < h->vertices[min].distancia)
        min = esquerda;
    if (direita != -1 && h->vertices[direita].distancia < h->vertices[min].distancia)
        min = direita;

    // Swapping the nodes
    if (min != index)
    {
        Vertice temp = h->vertices[min];
        h->vertices[min] = h->vertices[index];
        h->vertices[index] = temp;

        // recursively calling for their child elements
        // to maintain min Heap
        minHeapify(h, min);
    }
}

Vertice extractMin(Heap *h)
{
    Vertice deleteItem;
    int i = 0;
    int indice = 0;

    // Store the node in deleteItem that
    // is to be deleted.
    deleteItem = h->vertices[0];

    // Replace the deleted node with the last node
    h->vertices[0] = h->vertices[h->tamanho - 1];

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
        h->vertices[h->tamanho] = data;
        // Calling insertHelper function
        insertHelper(h, h->tamanho);
        // Incrementing size of array
        h->tamanho++;
    }
    else
    {
        h->capacidade = 2 * h->capacidade;
        h->vertices = (Vertice *)realloc((h->vertices), h->capacidade * sizeof(Vertice));
        insert(h, data);
    }
}

void printHeap(Heap *h)
{

    for (int i = 0; i < h->tamanho; i++)
    {
        printf("%d ", h->vertices[i].id);
    }
    printf("\n");
}

void destroiHeap(Heap *h)
{
    free(h->vertices);
    free(h);
}

int pesquisaHeap(Heap *h, int id)
{
    int i;
    for (i = 0; i < h->tamanho; i++)
    {
        if (id == h->vertices[i].id)
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
        printf("%d  %lld", h->vertices[i].id, h->vertices[i].distancia);
    }
}

bool getSizeHeap(Heap *heap)
{
    if (heap->tamanho == 0)
    {
        return true;
    }

    return false;
}