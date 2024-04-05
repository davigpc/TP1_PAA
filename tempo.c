#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>
#include "tempo.h"

tempo tempoAtual()
{

  tempo atual;

  getrusage(RUSAGE_SELF, &atual.rtime);
  gettimeofday(&atual.tv, NULL);

  return atual;
}

double tempoDecorrido(struct timeval inicio, struct timeval fim)
{
  struct timeval diff;

  timersub(&inicio, &fim, &diff);

  return (double)diff.tv_sec + diff.tv_usec / 1000000.0;
}

void imprimeTempos(char * arqSaida, tempo inicio, tempo fim)
{

  double tempoSistema = tempoDecorrido(inicio.rtime.ru_stime, fim.rtime.ru_stime);
  double tempoUsuario = tempoDecorrido(inicio.rtime.ru_utime, fim.rtime.ru_utime);
  double tempoRelogio = tempoDecorrido(inicio.tv, fim.tv);

  FILE *fp = fopen(arqSaida, "w");
  if (fp == NULL)
  {
    fprintf(stderr, "ERRO: falha ao abrir arquivo.\n");
    return;
  }

  fprintf(fp, "TEMPO USUARIO: %lf\n", tempoUsuario);
  fprintf(fp, "TEMPO SISTEMA: %lf\n", tempoSistema);
  fprintf(fp, "TEMPO RELOGIO: %lf\n", tempoRelogio);
}

