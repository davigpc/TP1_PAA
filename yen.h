#ifndef YEN_H
#define YEN_H

#include <stdlib.h>
#include <stdio.h>
#include "grafo_listaAdj.h"
#include "heap.h"
#include "dijkstra.h"

typedef struct
{
    Caminho **caminhos;
    int qtdCaminhos;
} Caminhos;

Caminhos *criaCaminhos(int);

Caminhos *yen(char *, Grafo *);

Caminho *copiaCaminho(Grafo *, Caminho *, int);

bool verificaCaminhosIguais(Grafo *, Caminho *, Caminho *);

void removeVerticesCaminho(Grafo *, Caminho *);

bool spurPathVazio(Caminho *);

Caminho *juntaCaminhos(Grafo *, Caminho *, Caminho *, int);

void ordenaCandidatos(Caminhos *);

bool existeCaminhoCandidato(Caminhos *, Caminho *, Grafo *);

void imprimeMenoresCaminhos(char *, char *, Grafo *);

void removePrimeiroCandidato(Caminhos *);

void imprimeCandidatos(FILE *, Caminhos *);

void liberaCaminhos(Caminhos *);

#endif