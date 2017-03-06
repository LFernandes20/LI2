#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "battleship.h"


/* Funções E3 */


/** Função contaCol: conta quantos '.' ou 'o' existem numa certa coluna.
@param e Tabuleiro
@param j Coluna que vai ser modificada
@return Retorna o número de caractéres iguas a '.' ou 'o'
*/


int contaCol (tabuleiro e, int j) {
  int i, c = 0;
  for (i = 0; i < e.linhas; i++) {
    if (e.tab [i] [j] == '.' || e.tab [i] [j] == 'o')
      c++;
  }
  return c;
}


/** Função contaLin: conta quantos '.' ou 'o' existem numa certa linha.
@param e Tabuleiro
@param i Linha que vai ser modificada
@return Retorna o número de caractéres iguas a '.' ou 'o'
*/


int contaLin (tabuleiro e, int i) {
  int j, c = 0;
  for (j = 0; j < e.colunas; j++) {
    if (e.tab [i] [j] == '.' || e.tab [i] [j] == 'o')
      c++;
  }
  return c;
}


/** Função contaVazio: conta quantos '.' consecutivos existem dependendo da diração do barco.
@param e Tabuleiro
@param i Linha onde se encontra o caractér
@param j Colunas onde se encontra o caractér
@param c Barco encontrada, que posteriormente serve de guia para saber para onde contar
@return Retorna o número de espaços vazios consecutivos
*/


int contaVazio (tabuleiro e, int i, int j, char c) {
  int conta = 0;
  if (c == '<') {
    for (; e.tab [i] [j] == '.' && j < e.colunas; j++)
      conta++;
  }
  else
    if (c == '^')
      for (; e.tab [i] [j] == '.' && i < e.linhas; i++)
        conta++;
    else
      if (c == '>')
        for (; e.tab [i] [j] == '.' && j >= 0; j--)
          conta ++;
      else
        if (c == 'v')
          for (; e.tab [i] [j] == '.' && i >= 0; i--)
            conta++;
  return conta;
}


/** Função contaBarcos: conta quantos segmentos de barco existem numa certa linha ou coluna, dependendo do que o utilizador quiser.
@param e Tabuleiro
@param i Linha a verificar. Pode ser 0 se quisermos verificar a coluna
@param j Coluna a verificar. Pode ser 0 se quisermos verificar a linha
@param q Caractér para sabermos se queremos contar linha ou coluna
@return Retorna o número de barcos
*/


int contaBarcos (tabuleiro e, int i, int j, char q) {
  int c = 0;
  if (q == 'c')
    for (i = 0; i < e.linhas; i++) {
      if (e.tab [i] [j] == 'O' || e.tab [i] [j] == '^' || e.tab [i] [j] == '<' || e.tab [i] [j] == '>' || e.tab [i] [j] == 'v' || e.tab [i] [j] == 'o' || e.tab [i] [j] == '#')
        c++;
    }
  else
    for (j = 0; j < e.colunas; j++) {
      if (e.tab [i] [j] == 'O' || e.tab [i] [j] == '^' || e.tab [i] [j] == '<' || e.tab [i] [j] == '>' || e.tab [i] [j] == 'v' || e.tab [i] [j] == 'o' || e.tab [i] [j] == '#')
        c++;
    }
  return c;
}


/* Funções V */



/** Função contaLinhas: conta, numa dada linha, o número de casas que não contêm água.
@param e Tabuleiro
@param i Linha a ser verificada
@return Retorna o número de caractéres diferentes de '~'
*/


int contaLinhas (tabuleiro e, int i) {
  int conta = 0, j;
  for (j = 0; j < e.colunas; j++)
    if (e.tab [i] [j] != '~')
      conta++;
  return conta;
}


/** Função contaColunas: conta, numa dada coluna, o número de casas que não contêm água.
@param e Tabuleiro
@param j Coluna a ser verificada
@return Retorna o número de caractéres diferentes de '~'
*/


int contaColunas (tabuleiro e, int j) {
  int conta = 0, i;
  for (i = 0; i < e.colunas; i++)
    if (e.tab [i] [j] != '~')
      conta++;
  return conta;
}


/** Função eSubmarino: verifica se numa certa casa, recebida como input, se encontra ou não um submarino.
@param e Tabuleiro
@param i Posiçao nas linhas
@param j Posição nas colunas
@return Retorna 1 se for submarino, 0 se o oposto
*/


int eSubmarino (tabuleiro e, int i, int j) {
  int res = 0;
  if (i == 0 && j == 0) {
    if (e.tab [i + 1] [j] == '~' && e.tab [i] [j + 1] == '~' && e.tab [i + 1] [j + 1] == '~')
      res = 1;
  }
  else
    if (i == 0 && j == e.colunas - 1) {
      if (e.tab [i + 1] [j] == '~' && e.tab [i] [j - 1] == '~' && e.tab [i + 1] [j - 1] == '~')
        res = 1;
  }
  else
    if (i == e.linhas - 1 && j == 0) {
      if (e.tab [i - 1] [j] == '~' && e.tab [i] [j + 1] == '~' && e.tab [i - 1] [j + 1] == '~')
        res = 1;
  }
  else
    if (i == e.linhas - 1 && j == e.colunas - 1) {
      if (e.tab [i - 1] [j] == '~' && e.tab [i] [j - 1] == '~' && e.tab [i - 1] [j - 1] == '~')
        res = 1;
  }
  else
    if (i == 0) {
      if (e.tab [i + 1] [j] == '~' && e.tab [i] [j - 1] == '~' && e.tab [i] [j + 1] == '~' && e.tab [i + 1] [j - 1] == '~' && e.tab [i + 1] [j + 1] == '~')
        res = 1;
  }
  else
    if (j == 0) {
      if (e.tab [i - 1] [j] == '~' && e.tab [i + 1] [j] == '~' && e.tab [i] [j + 1] == '~' && e.tab [i - 1] [j + 1] == '~' && e.tab [i + 1] [j + 1] == '~')
        res = 1;
  }
  else
    if (j == e.colunas - 1) {
      if (e.tab [i - 1] [j] == '~' && e.tab [i + 1] [j] == '~' && e.tab [i] [j - 1] == '~' && e.tab [i - 1] [j - 1] == '~' && e.tab [i + 1] [j - 1] == '~')
        res = 1;
  }
  else
    if (i == e.linhas - 1) {
      if (e.tab [i - 1] [j] == '~' && e.tab [i] [j - 1] == '~' && e.tab [i] [j + 1] == '~' && e.tab [i - 1] [j + 1] == '~' && e.tab [i - 1] [j - 1] == '~')
        res = 1;
  }
  else
    if (e.tab [i - 1] [j] == '~' && e.tab [i + 1] [j] == '~' && e.tab [i] [j - 1] == '~' && e.tab [i] [j + 1] == '~' && e.tab [i - 1] [j + 1] == '~' && e.tab [i - 1] [j - 1] == '~' && e.tab [i + 1] [j + 1] == '~' && e.tab [i + 1] [j - 1] == '~')
      res = 1;

  return res;
}


/** Função eBarco: verifica se uma certa casa recebida como input não se encontra nas margens do tabuleiro e se é um segmento de barco.
@param e Tabuleiro
@param i Posição nas linhas
@param j Posição nas colunas
@return Retorna 0 se estiver fora do tabuleiro e se nao for segmento de barco, retorna 1 se o oposto
*/


int eBarco (tabuleiro e, int i, int j) {
  if (i < 0 || i >= e.linhas || j < 0 || j >= e.colunas)
    return 0;
  if (strchr ("voO#<>^", e.tab [i] [j]) != NULL)
    return 1;
  else
    return 0;
}


/* Funções Stack */



/** Função push: guarda cada comando executado numa stack, de maneira a que mais tarde se possa anular, se necessário.
@param *s Endereço da stack
@param i Posição nas linhas a colocar na stack
@param j Posição nas colunas a colocar na stack
@param c Caractér a colocar na stack
@param qt Quantidade de comandos que irão ser anulados numa só execução da função pop
@return É uma função void, logo nao retorna nada
*/


void push (stack *s, int i, int j, char c, int qt) {
  s -> top++;
  s -> valores [s -> top].i = i;
  s -> valores [s -> top].j = j;
  s -> valores [s -> top].c = c;
  s -> valores [s -> top].qt = qt;
}


/** Função pop: retira comandos da stack.
@param e Tabuleiro
@param *s Endereço da stack
@param i Posição nas linhas onde irá ser colocado o caractér c
@param j Posição nas colunas onde irá ser colocado o caractér c
@param c Caractér a ser colocado na posição [i] [j]
@return Retorna o tabuleiro depois das alterações
*/


tabuleiro pop (tabuleiro e, stack *s, int i, int j, char c) {
  s -> top--;
  if (c == 'c' || c == 'l') {
    e.linhas = 0;
    e.colunas = 0;
  }
  else
    if (c == 'R');
    else
      e.tab [i] [j] = c;
  return e;
}
