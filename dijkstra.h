#ifndef DJIKSTRA_H
#define DJIKSTRA_H

#include <stdlib.h>
#include <stdio.h>
#include "grafo_listaAdj.h"
#include "heap.h"

typedef struct
{
    Vertice *vertices;
    int tamCaminho;
    Peso pesoCaminho;
} Caminho;

Caminho *criaVetorCaminho(int);
Caminho *dijkstra(Grafo *, int);
Caminho *organizaCaminho(Caminho *);

#endif