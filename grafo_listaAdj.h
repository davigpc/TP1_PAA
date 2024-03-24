#ifndef GRAFO_LISTAADJ_H
#define GRAFO_LISTAADJ_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define VERTICE_INVALIDO NULL
#define ARESTA_NULA -1

typedef int Peso;

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

} Grafo;

Grafo *inicializaGrafo(int, int);

bool verificaValidadeVertice(int, Grafo *);

bool listaAdjVazia(int, Grafo *);

Apontador proxListaAdj(int, Grafo *, Aresta *);

void insereAresta(int, int, Peso, Grafo *);

bool removeArestaObtendoPeso(int, int, Peso *, Grafo *);

Apontador primeiroListaAdj(int, Grafo *);

bool existeAresta(int, int, Grafo *);

Apontador encontraAresta(int, int, Grafo *);

void liberaGrafo(Grafo *);

void imprimeGrafo(char *, Grafo *);

Grafo *leGrafo(char *, int *);

Peso obtemPesoAresta(int, int, Grafo *);

#endif
