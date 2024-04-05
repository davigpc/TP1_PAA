#ifndef EPPSTEIN_H
#define EPPSTEIN_H

#include <stdlib.h>
#include <stdio.h>
#include "grafo_listaAdj.h"
#include "heap.h"

Peso *eppstein(Grafo *);
void insereFihos(Grafo *, Vertice, Heap *, int *);
void imprimeMenoresCaminhos(char *nomearqEscrita, Grafo *grafo);

#endif