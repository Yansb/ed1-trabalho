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
  int totalClientes = 0;
  int totalEspera = 0;
  int qtdeCaixas = 3;
  int caixas[qtdeCaixas] = {0, 0, 0};

  int expediente = 1000;

  while (expediente > 0)
  {
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
        totalEspera += cliente.horarioChegada - expediente;
      }
    }

    if (chegouCliente())
    {
      totalClientes++;
      cliente.horarioChegada = expediente;
      printf("Chegou cliente no horário %d \n", expediente);
      int clienteInserido = 0;
      for (int i = 0; i < qtdeCaixas; i++)
      {
        if (caixas[i] == 0)
        {
          printf("Cliente atendido no caixa %d depois de esperar %d segundos\n", i, cliente.horarioChegada - expediente);
          totalEspera += cliente.horarioChegada - expediente;
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
          printf("Cliente %d inserido na fila atualmente temos [%d] pessoas na fila\n", cliente.horarioChegada, fila.qtdeAtual);
          printf("Inicio: ");
          imprimirFila(&fila);
        }
      }
    }

    expediente--;
  }

  printf("Fim do expediente\n");
  printf("Total de clientes atendidos: %d\n", totalClientes);
  printf("Tempo médio de espera: %d\n", totalEspera / totalClientes);
  printf("Total de espera dos clientes atendidos %d\n", totalEspera);
  printf("Faltaram ser atendidos %d clientes\n", fila.qtdeAtual);
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
