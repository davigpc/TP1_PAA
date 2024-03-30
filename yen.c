#include "yen.h"
#include <stdio.h>
#include <stdlib.h>

void yen(char *nomearq, Grafo *grafo)
{
    // fazer uma copia do grafo;
    Caminho *menoresCaminhos = (Caminho *)malloc(grafo->numMenoresCaminhos * sizeof(Caminho));
    Caminho *candidatos = (Caminho *)calloc(grafo->numArestas, sizeof(Caminho));
    Vertice spurVertice;
    Caminho caminhoRaiz;

    menoresCaminhos[0] = dijkstra(grafo);

    for (int i = 1; i < grafo->numMenoresCaminhos; i++)
    {
        for (int j = 0; j < menoresCaminhos[i - 1].tamCaminho - 1; j++)
        {
            spurVertice = menoresCaminhos[i].vertices[j];

            // caminhoRaiz = função que coloca o caminho até o spur node
            for (int k = 0; k < grafo->numMenoresCaminhos; k++)
            {
                // if(caminhoRaiz == função que coloca o caminho até o spur node no caminho dos menores caminhos)
                // remover o caminho ate o spur node
            }
        }
    }
}