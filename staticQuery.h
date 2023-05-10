#include <stdio.h>

int const max = 5;

struct T_Cliente
{
  int horarioChegada;
};

struct T_Fila
{
  int inicio;
  int final;
  int qtdeAtual;
  T_Cliente dados[max];
};
void inicializarFila(T_Fila *fila)
{
  (*fila).inicio = 0;
  (*fila).final = 0;
  (*fila).qtdeAtual = 0;
}

int chkFilaVazia(T_Fila *fila)
{
  return fila->final == 0;
}

int inserir(T_Fila *fila, T_Cliente item)
{
  int flag = 0;
  if ((*fila).qtdeAtual < max)
  {
    (*fila).dados[fila->final] = item;
    fila->final++;
    fila->qtdeAtual++;
    flag = 1;
  }

  return flag;
}

void imprimirFila(T_Fila *fila)
{
  for (int i = 0; i < fila->qtdeAtual; i++)
  {
    printf("<- %d ", (*fila).dados[i].horarioChegada);
  }
  printf("\n");
}

int remover(T_Fila *fila)
{
  int flag = 0;
  if (!chkFilaVazia(fila))
  {
    for (int i = 0; i < fila->qtdeAtual; i++)
    {
      fila->dados[i] = fila->dados[i + 1];
    }
    fila->qtdeAtual--;
    fila->final--;
    flag = 1;
  }

  return flag;
}
