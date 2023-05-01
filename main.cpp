#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "staticQuery.h"
int generateRandomNumberUntil(int max);
bool chegouCliente();
void iniciarTransacao(int *caixa);

int main()
{
  T_Fila fila;
  T_Cliente cliente;

  inicializarFila(&fila);
  int qtdeCaixas = 3;
  int caixas[qtdeCaixas] = {0, 0, 0};

  int expediente = 28800; // 8 horas em segundos

  while (expediente > 0)
  {
    if (chegouCliente())
    {
      cliente.horarioChegada = expediente;
      printf("Chegou cliente no horário %d \n", expediente);
      int clienteInserido = 0;
      for (int i = 0; i < qtdeCaixas; i++)
      {
        if (caixas[i] == 0)
        {
          printf("Cliente atendido no caixa %d depois de esperar %d segundos\n", i, cliente.horarioChegada - expediente);
          iniciarTransacao(&caixas[i]);
          printf("Caixa [%d]: iniciando transação de %d segundos\n", i, caixas[i]);
          clienteInserido = 1;
          break;
        }
      }
      if (clienteInserido == 0)
      {
        int response = inserir(&fila, cliente);
        if (response == 0)
        {
          printf("Fila cheia\n");
        }
        else
        {
          printf("Cliente inserido na fila atualmente temos [%d] pessoas na fila\n", fila.qtdeAtual);
        }
      }
    }

    for (int i = 0; i < qtdeCaixas; i++)
    {
      if (caixas[i] > 0)
      {
        caixas[i]--;
        printf("Caixa [%d]: transação em andamento. Falta %d segundos\n", i, caixas[i]);
      }

      if (caixas[i] == 0 && !chkFilaVazia(&fila))
      {
        iniciarTransacao(&caixas[i]);
        printf("Caixa [%d]: iniciando transação de %d segundos\n", i, caixas[i]);
        remover(&fila);
        printf("Cliente atendido no caixa %d depois de esperar %d segundos\n", i, cliente.horarioChegada - expediente);
      }
    }

    expediente--;
  }

  printf("Fim do expediente\n");
  return 0;
}

bool chegouCliente()
{
  return generateRandomNumberUntil(3) == 0;
}

int generateRandomNumberUntil(int max)
{
  return rand() % (max + 1);
}

void iniciarTransacao(int *caixa)
{
  switch (generateRandomNumberUntil(4))
  {
  case 0:
    *caixa = 10;
    break;
  case 1:
    *caixa = 20;
    break;
  case 2:
    *caixa = 30;
    break;
  case 3:
    *caixa = 40;
    break;
  case 4:
    *caixa = 50;
    break;

  default:
    break;
  }
}
