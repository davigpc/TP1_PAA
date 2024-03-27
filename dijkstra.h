#ifndef DJIKSTRA_H
#define DJIKSTRA_H

#include <stdlib.h>
#include <stdio.h>
#include "grafo_listaAdj.h"
#include "heap.h"

Vertice *criaVetorCaminho(int);
int dijkstra(Grafo *);
int pesquisaCaminho(Vertice *, int);
void imprimeMenorCaminho(char *, Grafo *);

#endif