#ifndef HEAP_H
#define HEAP_H

#include <stdlib.h>
#include <stdio.h>
#include "grafo_listaAdj.h"

typedef struct vertice
{
	int id;
	int distancia;
	int verticePai;
} Vertice;

typedef struct Heap
{
	Vertice *naoVisitados;
	int tamanho;
	int capacidade;
} Heap;

Heap *createHeap(int, Grafo *);

void insert(Heap *, int);

Vertice extractMin(Heap *);

void insertHelper(Heap *, int);

void minHeapify(Heap *h, int);

#endif