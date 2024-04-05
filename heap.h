#ifndef HEAP_H
#define HEAP_H

#include <stdlib.h>
#include <stdio.h>
#include "grafo_listaAdj.h"

typedef struct vertice
{
	int id;
	Peso distancia;
} Vertice;

typedef struct Heap
{
	Vertice *vertices;
	int tamanho;
	int capacidade;
} Heap;

Heap *criaHeapVazia(int capacidade);

Vertice extraiMenor(Heap *h);

void insere(Heap *h, Vertice data);

void destroiHeap(Heap *h);

bool heapVazia(Heap *heap);

#endif