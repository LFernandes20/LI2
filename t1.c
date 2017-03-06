#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "battleship.h"
#include "aux.h"


/** Função carregar: recebe um tabuleiro apartir do standard input (teclado) e guarda-o, retornando-o no fim ao interpretador.
@param e Tabuleiro
@param *s endereço da stack
@return Retorna o tabuleiro introduzido
*/

tabuleiro carregar (tabuleiro e, stack *s) {
  int l, c, i, j;
  char linha [MAX_SIZE];
  char resto [MAX_SIZE];
  char linha2 [MAX_SIZE];

  if (fgets (linha, MAX_SIZE, stdin) != NULL)
    sscanf (linha, "%d %d", &e.linhas, &e.colunas);

  if (e.linhas == 0 || e.colunas == 0) {
    printf ("Tabuleiro Inválido!\n");
    return e;
  }

  if (fgets (linha, MAX_SIZE, stdin) != NULL && e.linhas != 0)
    for (l = 0; l < e.linhas; l++) {
      int v;
      sscanf (linha, "%d %[^\n]", &v, resto);
      e.seg_lins [l] = v;
      strcpy (linha, resto);
    }
  if (fgets (linha, MAX_SIZE, stdin) != NULL && e.colunas != 0)
    for (c = 0; c < e.colunas; c++) {
      int v;
      sscanf (linha, "%d %[^\n]", &v, resto);
      e.seg_cols [c] = v;
      strcpy (linha, resto);
    }
  for (i = 0; i < e.linhas; i++) {
    if (fgets (linha, MAX_SIZE, stdin) != NULL && e.colunas != 0)
      for (j = 0; j < e.colunas; j++) {
        sscanf (linha, "%c%s", linha2, resto);
        e.tab [i] [j] = *linha2;
        strcpy (linha, resto);
      }
  }
  push (s, 0, 0, 'c', 1);
  return e;
}

/** Função mostrar: imprime no ecrã o respetivo tabuleiro recebido.
@param e Tabuleiro
@return É uma função void, logo nao retorna nada
*/


void mostrar (tabuleiro e) {
  int i, j;
  if (e.linhas == 0 || e.colunas == 0)
    printf ("Não existe tabuleiro!\n");
  else {
    for (i = 0; i < e.linhas; i++) {
      for (j = 0; j < e.colunas; j++) {
        printf ("%c", e.tab [i] [j]);
      }
      printf(" %d\n",e.seg_lins [i]);
    }
    for (j = 0; j < e.colunas; j++) {
      printf("%d",e.seg_cols[j]);
    }
    printf("\n");
  }
}


/** Função comandoP: esta função vai ao tabuleiro (matriz) e na posição <linha> <coluna> coloca o caracter 'c' recebido como argumento.
@param e Tabuleiro
@param c Caractér a colocar
@param i Posição nas linhas
@param j Posição nas colunas
@param qt Quantidade de comandos executados
@param *s Endereço da stack
@return Retorna o tabuleiro depois de colocar o caractér
*/


tabuleiro comandoP (tabuleiro e, char c, int i, int j, int qt, stack *s) {
  if (c != e.tab [i - 1] [j - 1]) {
    push (s, i - 1, j - 1, e.tab [i - 1] [j - 1], qt);
    e.tab [i - 1] [j - 1] = c;
  }
  return e;
}


/** Função comandoH: esta função vai ao tabuleiro e na linha nº <num> coloca todas as posições não determinadas como sendo água.
@param e Tabuleiro
@param i Linha que vai ser modificada
@param *s Endereço da stack
@return Retorna o tabuleiro depois de todas as alterações
*/


tabuleiro comandoH (tabuleiro e, int i, stack *s) {
  int j, qt = 1;
  for (j = 0; j < e.colunas; j++) {
    if (e.tab [i - 1] [j] == '.') {
      push (s, i - 1, j, e.tab [i - 1] [j], qt++);
      e.tab [i - 1] [j] = '~';
    }
  }
  return e;
}


/** Função comandoV: esta função vai ao tabuleiro e na coluna nº <num> coloca todas as grelhas não determinadas como sendo água.
@param e Tabuleiro
@param j Coluna que vai ser modificada
@param *s Endereço da stack
@return Retorna o tabuleiro depois de todas as alterações
*/


tabuleiro comandoV (tabuleiro e, int j, stack *s) {
  int i, qt = 1;
  for (i = 0; i < e.linhas; i++) {
    if (e.tab [i] [j-1]=='.') {
      push (s, i, j - 1, e.tab [i] [j - 1], qt++);
      e.tab [i] [j-1] = '~';
    }
  }
  return e;
}
