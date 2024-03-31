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

Caminho criaVetorCaminho(int);
Caminho dijkstra(Grafo *, int);
int pesquisaCaminho(Vertice *, int);
Caminho organizaCaminho(Caminho);
// void imprimeMenorCaminho(char *, Grafo *);

#endif