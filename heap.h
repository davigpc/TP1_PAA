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

Heap *criaHeap(int);

void insert(Heap *, Vertice);

Vertice extractMin(Heap *);

void insertHelper(Heap *, int);

void minHeapify(Heap *, int);

void destroiHeap(Heap *);

int pesquisaHeap(Heap *, int);

void imprimeHeap(Heap *);

#endif