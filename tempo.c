#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>
#include "tempo.h"

float tempoUsuario(struct rusage *inicio, struct rusage *fim)
{

  return (fim->ru_utime.tv_sec - inicio->ru_utime.tv_sec) + 1e-6 * (fim->ru_utime.tv_usec - inicio->ru_utime.tv_usec);
}

float tempoSistema(struct rusage *inicio, struct rusage *fim)
{
  return (fim->ru_stime.tv_sec - inicio->ru_stime.tv_sec) + 1e-6 * (fim->ru_stime.tv_usec - inicio->ru_stime.tv_usec);
}

float tempoRelogio(struct timeval *inicio, struct timeval *fim)
{
  return (fim->tv_sec - inicio->tv_sec) + 1e-6 * (fim->tv_usec - inicio->tv_usec);
}

void imprimeTempos(char *arqSaida, struct rusage *inicio, struct rusage *fim, struct timeval *inicioRelogio, struct timeval *fimRelogio)
{

  FILE *fp = fopen(arqSaida, "w");
  if (fp == NULL)
  {
    fprintf(stderr, "ERRO: falha ao abrir arquivo.\n");
    return;
  }

  fprintf(fp, "TEMPO USUARIO: %f\n", tempoUsuario(&inicio, &fim));
  fprintf(fp, "TEMPO SISTEMA: %f\n", tempoSistema(&inicio, &fim));
  fprintf(fp, "TEMPO RELOGIO: %f\n", tempoRelogio(&inicioRelogio, &fimRelogio));

  fclose(fp);
}