#include "yen.h"
#include <stdio.h>
#include <stdlib.h>

void yen(char *nomearq, Grafo *grafo)
{
    Caminho *menoresCaminhos = (Caminho *)malloc(grafo->numMenoresCaminhos * sizeof(Caminho));
    Caminho *candidatos = (Caminho *)calloc(grafo->numMenoresCaminhos, sizeof(Caminho));
    Vertice spurVertice;
    Vertice proxSpurVertice;
    Caminho caminhoRaiz;
    Caminho caminhoSpur;
    Caminho caminhoTotal;

    for (int i = 0; i < grafo->numMenoresCaminhos; i++)
    {
        menoresCaminhos[i] = criaVetorCaminho(grafo->numVertices);
    }

    for (int i = 0; i < grafo->numMenoresCaminhos; i++)
    {
        candidatos[i] = criaVetorCaminho(grafo->numVertices);
    }

    menoresCaminhos[0] = dijkstra(grafo, 1);

    for (int i = 1; i < grafo->numMenoresCaminhos; i++)
    {
        for (int j = 0; j < menoresCaminhos[i - 1].tamCaminho - 1; j++)
        {
            spurVertice = menoresCaminhos[i - 1].vertices[j];
            proxSpurVertice = menoresCaminhos[i - 1].vertices[j + 1];

            // caminhoRaiz = função que coloca o caminho até o spur node
            caminhoRaiz = copiaCaminho(grafo, menoresCaminhos[i - 1], spurVertice.id);

            for (int k = 0; k < grafo->numMenoresCaminhos; k++)
            {
                if (verificaCaminhosIguais(grafo, caminhoRaiz, menoresCaminhos[k]))
                {
                    removeAresta(spurVertice.id, proxSpurVertice.id, grafo);
                }
            }

            removeVertices(grafo, caminhoRaiz);

            caminhoSpur = dijkstra(grafo, spurVertice.id);

            if (spurPathVazio(caminhoSpur))
            {
                continue;
            }

            Caminho caminhoTotal = juntaCaminhos(grafo, caminhoRaiz, caminhoSpur, spurVertice.id);

            if (!existeCaminhoCandidato(candidatos, caminhoTotal, grafo))
            {
                ordenaCandidatos(candidatos, grafo->numMenoresCaminhos);
                if (caminhoTotal.pesoCaminho < candidatos[grafo->numMenoresCaminhos - 1].pesoCaminho)
                {
                    candidatos[grafo->numMenoresCaminhos - 1].pesoCaminho = caminhoTotal.pesoCaminho;
                }
            }

            liberaGrafo(grafo);
            grafo = leGrafo(nomearq);
        }

        if (candidatos[0].vertices == NULL)
        {
            break;
        }

        ordenaCandidatos(candidatos, grafo->numMenoresCaminhos);

        menoresCaminhos[i] = candidatos[0];
    }

    return menoresCaminhos;
}

Caminho copiaCaminho(Grafo *grafo, Caminho caminhoOriginal, int destino)
{

    Caminho novoCaminho = criaVetorCaminho(caminhoOriginal.tamCaminho);

    Peso pesoCaminho = 0;

    for (int i = 0; i < caminhoOriginal.tamCaminho; i++)
    {
        novoCaminho.vertices[i] = caminhoOriginal.vertices[i];

        if (i > 0) // o primeiro nao tem vertice pai
        {
            pesoCaminho += obtemPesoAresta(caminhoOriginal.vertices[i].idVerticePai, caminhoOriginal.vertices[i].id, grafo);
        }

        if (caminhoOriginal.vertices[i].id == destino)
        {
            novoCaminho.pesoCaminho = pesoCaminho;
            novoCaminho.tamCaminho = i + 1;
            break;
        }
    }
    return novoCaminho;
}

bool verificaCaminhosIguais(Grafo *grafo, Caminho caminhoRaiz, Caminho caminhoOriginal)
{
    int contador = 0;

    for (int i = 0; i < caminhoRaiz.tamCaminho; i++)
    {
        if (caminhoRaiz.vertices[i].id == caminhoOriginal.vertices[i].id)
        {
            contador++;
        }
    }

    if (contador == caminhoRaiz.tamCaminho)
    {
        return true;
    }

    return false;
}

void removeVertices(Grafo *grafo, Caminho caminhoRaiz)
{
    Apontador p;
    int indice;

    for (int i = 0; i < caminhoRaiz.tamCaminho - 1; i++)
    {
        indice = caminhoRaiz.vertices[i].id;
        while ((p = grafo->listaAdj[indice]) != NULL)
        {

            grafo->listaAdj[indice] = p->prox;
            p->prox = NULL;
            free(p);
        }
    }
}

bool spurPathVazio(Caminho caminhoSpur)
{

    if (caminhoSpur.tamCaminho == 0)
    {
        return true;
    }

    return false;
}

Caminho juntaCaminhos(Grafo *grafo, Caminho caminhoRaiz, Caminho caminhoSpur, int destino)
{

    Caminho novoCaminho = criaVetorCaminho(caminhoRaiz.tamCaminho + caminhoSpur.tamCaminho - 1);

    Peso pesoCaminho = 0;

    for (int i = 0; i < caminhoRaiz.tamCaminho; i++)
    {
        novoCaminho.vertices[i] = caminhoRaiz.vertices[i];

        if (i > 0)
        {
            pesoCaminho += obtemPesoAresta(caminhoRaiz.vertices[i].idVerticePai, caminhoRaiz.vertices[i].id, grafo);
        }

        if (caminhoRaiz.vertices[i].id == destino)
        {
            novoCaminho.pesoCaminho = pesoCaminho;
            novoCaminho.tamCaminho = i + 1;
            break;
        }
    }

    for (int i = caminhoRaiz.tamCaminho; i < caminhoRaiz.tamCaminho + caminhoSpur.tamCaminho - 1; i++)
    {
        novoCaminho.vertices[i] = caminhoSpur.vertices[i];
        pesoCaminho += obtemPesoAresta(caminhoSpur.vertices[i].idVerticePai, caminhoSpur.vertices[i].id, grafo);
        novoCaminho.tamCaminho = i + 1;
    }

    return novoCaminho;
}

Caminho menorCandidato(Caminho *candidatos)
{

    Caminho menor;
    menor.pesoCaminho = PESO_MAXIMO;
    int indice;

    for (int i = 0; i < candidatos->tamCaminho; i++)
    {
        if (candidatos[i].pesoCaminho < menor.pesoCaminho)
        {
            menor.pesoCaminho = candidatos[i].pesoCaminho;
            indice = i;
        }
    }

    return candidatos[indice];
}

void ordenaCandidatos(Caminho *candidatos, int n)
{
    int i, j;
    Caminho chave;

    for (i = 1; i < n; i++)
    {

        chave = candidatos[i];
        j = i - 1;

        while (j >= 0 && candidatos[j].pesoCaminho > chave.pesoCaminho)
        {
            candidatos[j + 1] = candidatos[j];
            j = j - 1;
        }
        candidatos[j + 1] = chave;
    }
}

bool existeCaminhoCandidato(Caminho *candidatos, Caminho caminhoTotal, Grafo *grafo)
{
    int comparador = 0;
    int indiceCandidatos = 0;

    while (candidatos[indiceCandidatos].vertices != NULL)
    {
        if (verificaCaminhosIguais(grafo, caminhoTotal, candidatos[indiceCandidatos]))
        {
            return true;
        }
        indiceCandidatos++;
    }
    return false;
}
