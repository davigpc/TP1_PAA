#ifndef HEAP_H
#define HEAP_H

#include <stdlib.h>
#include <stdio.h>


typedef struct Heap {
	int *arr;
	int size;
	int capacity;
} Heap;

Heap* createHeap(int capacity, int* nums);

void insert(Heap* h, int data);

int extractMin(Heap* h);

void insertHelper(Heap* h, int index);

void minHeapify(Heap* h, int index);

#endif