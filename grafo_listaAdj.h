#ifndef GRAFO_LISTAADJ_H
#define GRAFO_LISTAADJ_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "tempo.h"

#define VERTICE_INVALIDO NULL
#define ARESTA_NULA -1
#define PESO_MAXIMO 100000000000001

typedef long long int Peso;

typedef struct str_aresta
{

    int vdestino;
    Peso peso;
    struct str_aresta *prox;

} Aresta;

typedef Aresta *Apontador;

typedef struct
{

    Apontador *listaAdj;
    int numVertices;
    int numArestas;
    int numMenoresCaminhos;

} Grafo;

void liberaGrafo(Grafo *grafo);

Grafo *leGrafo(FILE *nomearq);

void imprimeMenoresCaminhos(FILE *nomearqEscrita, Grafo *grafo);

#endif
