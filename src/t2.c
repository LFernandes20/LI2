#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "battleship.h"
#include "aux.h"
#include "t1.h"
#include "t2.h"


/** Função lerFicheiro: permite-nos ler um ficheiro de texto e carregar o tabuleiro lá contido.
@param e Tabuleiro
@param *str Nome do ficheiro a abrir
@param *s Endereço da stack
@return Retorna o tabuleiro lido do ficheiro
*/


tabuleiro lerFicheiro (tabuleiro e, char *str, stack *s) {
  int l, c, i, j;
  char linha [MAX_SIZE];
  char resto [MAX_SIZE];
  char linha2 [MAX_SIZE];
  FILE *fl = fopen (str, "r");

  if (fl == NULL) {
    printf ("Ficheiro invalido!\n");
    return e;
  }

  if (fgets (linha, MAX_SIZE, fl)!=NULL)
    sscanf (linha, "%d %d", &e.linhas, &e.colunas);
  if (fgets (linha, MAX_SIZE, fl)!=NULL)
    for (l = 0; l < e.linhas; l++) {
      int v;
      sscanf (linha, "%d %[^\n]", &v, resto);
      e.seg_lins [l] = v;
      strcpy (linha, resto);
    }
  if (fgets (linha, MAX_SIZE, fl)!=NULL)
    for (c = 0; c < e.colunas; c++) {
      int v;
      sscanf (linha, "%d %[^\n]", &v, resto);
      e.seg_cols [c] = v;
      strcpy (linha, resto);
    }
  for (i = 0; i < e.linhas; i++) {
    if (fgets (linha, MAX_SIZE, fl)!=NULL)
      for (j = 0; j < e.colunas; j++) {
        sscanf (linha, "%c%s", linha2, resto);
        e.tab [i] [j] = *linha2;
        strcpy (linha, resto);
      }
  }
  fclose (fl);
  push (s, 0, 0, 'l', 1);
  return e;
}


/** Função escreverFile: permite-nos escrever o tabuleiro atual num ficheiro de texto.
@param e Tabuleiro
@param *str Nome do ficheiro que irá ser criado
@return É uma função void, logo nao retorna nada
*/


void escreverFile (tabuleiro e, char *str) {
  int i, j;
  FILE *fl = fopen (str, "w");
  if (fl == NULL)
    printf ("Ficheiro invalido!\n");
  fprintf (fl, "%d %d\n", e.linhas, e.colunas);
  for (i = 0; i < e.linhas; i++) {
    if (i == e.linhas - 1)
      fprintf (fl, "%d\n", e.seg_lins[i]);
    else
      fprintf (fl, "%d ", e.seg_lins[i]);
  }
  for (i = 0; i < e.colunas; i++) {
    if (i == e.colunas - 1)
      fprintf (fl, "%d\n", e.seg_cols[i]);
    else
      fprintf (fl, "%d ", e.seg_cols[i]);
  }
  for (i = 0; i < e.linhas; i++) {
    for (j = 0; j < e.colunas; j++) {
      fprintf (fl, "%c", e.tab [i] [j]);
    }
    if (i != e.linhas - 1)
      fprintf (fl, "%c", '\n');
  }
  fprintf(fl, "%c", '\n');
  fclose (fl);
}


/** Função comandoE1: aplica uma estratégia predefinida sobre um certo tabuleiro.
Esta estratégia consiste em rodear de água ('~') todos os segmentos de barco contidos no tabuleiro.
@param e Tabuleiro
@param *s Endereço da stack
@return Retorna o tabuleiro resultante da aplicação da estratégia
*/


tabuleiro comandoE1 (tabuleiro e, stack *s) {
  int i, j, qt = 1;
  for (i = 0; i < e.linhas; i++) {
      for (j = 0; j < e.colunas; j++) {
        if (e.tab [i] [j] == 'O') {
          if (i != 0 && e.tab [i - 1] [j] == '.') {
            e = comandoP(e, '~', i, j + 1, qt++, s);
          }
          if (i + 1 < e.linhas && e.tab [i + 1] [j] == '.') {
            e = comandoP(e, '~', i + 2, j + 1, qt++, s);
          }
          if (j != 0 && e.tab [i] [j - 1] == '.') {
            e = comandoP(e, '~', i + 1, j, qt++, s);
          }
          if (j + 1 < e.colunas && e.tab [i] [j + 1] == '.') {
            e = comandoP(e, '~', i + 1, j + 2, qt++, s);
          }
          if (i != 0 && j != 0 && e.tab [i - 1] [j - 1] == '.') {
            e = comandoP(e, '~', i, j, qt++, s);
          }
          if (i != 0 && j < e.colunas && e.tab [i - 1] [j + 1] == '.') {
            e = comandoP(e, '~', i, j + 2, qt++, s);
          }
          if (i < e.linhas && j != 0 && e.tab [i + 1] [j - 1] == '.') {
            e = comandoP(e, '~', i + 2, j, qt++, s);
          }
          if (i < e.linhas && j < e.colunas && e.tab [i + 1] [j + 1] == '.') {
            e = comandoP(e, '~', i + 2, j + 2, qt++, s);
          }
        }
        else
          if (e.tab [i] [j] == 'v') {
            if (i + 1 < e.linhas && e.tab [i + 1] [j] == '.') {
              e = comandoP(e, '~', i + 2, j + 1, qt++, s);
            }
            if (j != 0 && e.tab [i] [j - 1] == '.') {
              e = comandoP(e, '~', i + 1, j, qt++, s);
            }
            if (j + 1 < e.colunas && e.tab [i] [j + 1] == '.') {
              e = comandoP(e, '~', i + 1, j + 2, qt++, s);
            }
            if (i != 0 && j != 0 && e.tab [i - 1] [j - 1] == '.') {
              e = comandoP(e, '~', i, j, qt++, s);
            }
            if (i != 0 && j < e.colunas && e.tab [i - 1] [j + 1] == '.') {
              e = comandoP(e, '~', i, j + 2, qt++, s);
            }
            if (i < e.linhas && j != 0 && e.tab [i + 1] [j - 1] == '.') {
              e = comandoP(e, '~', i + 2, j, qt++, s);
            }
            if (i < e.linhas && j < e.colunas && e.tab [i + 1] [j + 1] == '.') {
              e = comandoP(e, '~', i + 2, j + 2, qt++, s);
            }
        }
        else
          if (e.tab [i] [j] == '<') {
            if (i + 1 < e.linhas && e.tab [i + 1] [j] == '.') {
              e = comandoP(e, '~', i + 2, j + 1, qt++, s);
            }
            if (i != 0 && e.tab [i - 1] [j] == '.') {
              e = comandoP(e, '~', i, j + 1, qt++, s);
            }
            if (j != 0 && e.tab [i] [j - 1] == '.') {
              e = comandoP(e, '~', i + 1, j, qt++, s);
            }
            if (i != 0 && j != 0 && e.tab [i - 1] [j - 1] == '.') {
              e = comandoP(e, '~', i, j, qt++, s);
            }
            if (i != 0 && j < e.colunas && e.tab [i - 1] [j + 1] == '.') {
              e = comandoP(e, '~', i, j + 2, qt++, s);
            }
            if (i < e.linhas && j != 0 && e.tab [i + 1] [j - 1] == '.') {
              e = comandoP(e, '~', i + 2, j, qt++, s);
            }
            if (i < e.linhas && j < e.colunas && e.tab [i + 1] [j + 1] == '.') {
              e = comandoP(e, '~', i + 2, j + 2, qt++, s);
            }
          }
        else
          if (e.tab [i] [j] == '>') {
            if (i != 0 && e.tab [i - 1] [j] == '.') {
              e = comandoP(e, '~', i, j + 1, qt++, s);
            }
            if (i + 1 < e.linhas && e.tab [i + 1] [j] == '.') {
              e = comandoP(e, '~', i + 2, j + 1, qt++, s);
            }
            if (j + 1 < e.colunas && e.tab [i] [j + 1] == '.') {
              e = comandoP(e, '~', i + 1, j + 2, qt++, s);
            }
            if (i != 0 && j != 0 && e.tab [i - 1] [j - 1] == '.') {
              e = comandoP(e, '~', i, j, qt++, s);
            }
            if (i != 0 && j < e.colunas && e.tab [i - 1] [j + 1] == '.') {
              e = comandoP(e, '~', i, j + 2, qt++, s);
            }
            if (i < e.linhas && j != 0 && e.tab [i + 1] [j - 1] == '.') {
              e = comandoP(e, '~', i + 2, j, qt++, s);
            }
            if (i < e.linhas && j < e.colunas && e.tab [i + 1] [j + 1] == '.') {
              e = comandoP(e, '~', i + 2, j + 2, qt++, s);
            }
          }
        else
          if (e.tab [i] [j] == '^') {
            if (i != 0 && e.tab [i - 1] [j] == '.') {
              e = comandoP(e, '~', i, j + 1, qt++, s);
            }
            if (j != 0 && e.tab [i] [j - 1] == '.') {
              e = comandoP(e, '~', i + 1, j, qt++, s);
            }
            if (j + 1 < e.colunas && e.tab [i] [j + 1] == '.') {
              e = comandoP(e, '~', i + 1, j + 2, qt++, s);
            }
            if (i != 0 && j != 0 && e.tab [i - 1] [j - 1] == '.') {
              e = comandoP(e, '~', i, j, qt++, s);
            }
            if (i != 0 && j < e.colunas && e.tab [i - 1] [j + 1] == '.') {
              e = comandoP(e, '~', i, j + 2, qt++, s);
            }
            if (i < e.linhas && j != 0 && e.tab [i + 1] [j - 1] == '.') {
              e = comandoP(e, '~', i + 2, j, qt++, s);
            }
            if (i < e.linhas && j < e.colunas && e.tab [i + 1] [j + 1] == '.') {
              e = comandoP(e, '~', i + 2, j + 2, qt++, s);
            }
        }
        else
          if (e.tab [i] [j] == '#') {
            if (i != 0 && j != 0 && e.tab [i - 1] [j - 1] == '.') {
              e = comandoP(e, '~', i, j, qt++, s);
            }
            if (i != 0 && j < e.colunas && e.tab [i - 1] [j + 1] == '.') {
              e = comandoP(e, '~', i, j + 2, qt++, s);
            }
            if (i < e.linhas && j != 0 && e.tab [i + 1] [j - 1] == '.') {
              e = comandoP(e, '~', i + 2, j, qt++, s);
            }
            if (i < e.linhas && j < e.colunas && e.tab [i + 1] [j + 1] == '.') {
              e = comandoP(e, '~', i + 2, j + 2, qt++, s);
            }
            if ((e.tab [i] [j - 1] == '~' || j == 0) && j < e.colunas - 1) {
              e = comandoP(e, '~', i + 1, j + 2, qt++, s);
            }
            else if ((e.tab [i] [j + 1] == '~' || j == e.colunas - 1) && j != 0) {
              e = comandoP(e, '~', i + 1, j, qt++, s);
            }
            else if ((e.tab [i - 1] [j] == '~' || i == 0) && i < e.linhas - 1) {
              e = comandoP(e, '~', i + 2, j + 1, qt++, s);
            }
            else if ((e.tab [i + 1] [j] == '~' || i == e.linhas - 1) && i != 0) {
              e = comandoP(e, '~', i, j + 1, qt++, s);
            }
          }
        else
          if (e.tab [i] [j] == 'o') {
            if (i != 0 && j != 0 && e.tab [i - 1] [j - 1] == '.') {
              e = comandoP(e, '~', i, j, qt++, s);
            }
            if (i != 0 && j < e.colunas && e.tab [i - 1] [j + 1] == '.') {
              e = comandoP(e, '~', i, j + 2, qt++, s);
            }
            if (i < e.linhas && j != 0 && e.tab [i + 1] [j - 1] == '.') {
              e = comandoP(e, '~', i + 2, j, qt++, s);
            }
            if (i < e.linhas && j < e.colunas && e.tab [i + 1] [j + 1] == '.') {
              e = comandoP(e, '~', i + 2, j + 2, qt++, s);
            }
          }
      }
    }
  return e;
}


/** Função comandoE2: aplica uma estratégia predefinida sobre um certo tabuleiro.
A estratégia consiste em colocar água ('~') onde se verifique que não existirão mais segmentos de barco.
@param e Tabuleiro
@param *s Endereço da stack
@return Retorna o tabuleiro resultante da aplicação da estratégia
*/


tabuleiro comandoE2 (tabuleiro e, stack *s) {
  int i, j, conta = 0, qt = 1, falhouColunas = 0;
  for (i = 0; i < e.linhas; i++) {
    for (j = 0; j < e.colunas; j++) {
      if (strchr ("~.", e.tab [i] [j]) == NULL)
        conta++;
    }
    if (conta == e.seg_lins [i]) {
      for (j = 0; j < e.colunas; j++)
        if (e.tab [i] [j] == '.'){
          e = comandoP(e, '~', i + 1, j + 1, qt++, s);
        }
    }
    else
      falhouColunas = 1;
    conta = 0;
  }
  for (j = 0; falhouColunas != 0 && j < e.colunas; j++) {
    for (i = 0; i < e.linhas; i++) {
      if (strchr ("~.", e.tab [i] [j]) == NULL)
        conta++;
    }
    if (conta == e.seg_cols [j]) {
      for (i = 0; i < e.linhas; i++)
        if (e.tab [i] [j] == '.') {
          e = comandoP(e, '~', i + 1, j + 1, qt++, s);
        }
      }
        conta = 0;
  }
  return e;
}


/** Função comandoE3: aplica uma estratégia predefinida sobre um certo tabuleiro.
A estratégia consiste em completar barcos incompletos onde seja possível.
@param e Tabuleiro
@param *s Endereço da stack
@return Retorna o tabuleiro resultante da aplicação da estratégia
*/


tabuleiro comandoE3 (tabuleiro e, stack *s) {
  int i, j, vl, vc, k, conta, nBarcosC, nBarcosL, qt = 1;
  for (i = 0; i < e.linhas; i++) {
    for (j = 0; j < e.colunas; j++) {
      nBarcosC = contaBarcos (e, 0, j, 'c');
      nBarcosL = contaBarcos (e, i, 0, 'l');
      if (e.tab [i] [j] == '<') {
        vl = contaLin (e, i);
        conta = nBarcosL;
        if (vl >= e.seg_lins [i] - conta) {
          vl = contaVazio (e, i, j + 1, e.tab [i] [j]);
          if (vl > e.seg_lins [i])
            vl = e.seg_lins [i] - nBarcosL;
          for (k = j + 1; vl > 0; vl--, k++) {
            if (vl == 1) {
              if (e.tab [i] [k + 1] == '>') {
                e = comandoP(e, '#', i + 1, k + 1, qt++, s);
              }
              else
                if (e.tab [i] [k + 1] == '#') {
                  e = comandoP(e, '#', i + 1, k + 1, qt++, s);
                }
                else {
                  e = comandoP(e, '>', i + 1, k + 1, qt++, s);
                }
            }
            else {
              if (e.seg_cols [k + 1] - contaBarcos (e, 0, k + 1, 'c') != 0) {
                e = comandoP(e, '#', i + 1, k + 1, qt++, s);
              }
              else {
                e = comandoP(e, '>', i + 1, k + 1, qt++, s);
                vl = 0;
              }
            }
          }
        }
      }
      else
        if (e.tab [i] [j] == '>') {
          conta = nBarcosL;
          vl = contaLin (e, i);
          if (vl >= e.seg_lins [i] - conta) {
            vl = contaVazio (e, i, j - 1, e.tab [i] [j]);
            if (vl > e.seg_lins [i])
              vl = e.seg_lins [i] - nBarcosL;
            for(k = j - 1; vl > 0; vl--, k--) {
              if (vl == 1) {
                if (e.tab [i] [k - 1] == '<') {
                  e = comandoP(e, '#', i + 1, k + 1, qt++, s);
                }
                else
                  if (e.tab [i] [k - 1] == '#') {
                    e = comandoP(e, '#', i + 1, k + 1, qt++, s);
                  }
                  else {
                    e = comandoP(e, '<', i + 1, k + 1, qt++, s);
                  }
              }
              else {
                if (e.seg_cols [k - 1] - contaBarcos (e, 0, k - 1, 'c') != 0) {
                  e = comandoP(e, '#', i + 1, k + 1, qt++, s);
                }
                else {
                  e = comandoP(e, '<', i + 1, k + 1, qt++, s);
                  vl = 0;
                }
              }
            }
          }
        }
        else
          if (e.tab [i] [j] == 'v') {
            conta = nBarcosC;
            vc = contaCol (e, j);
            if (vc >= e.seg_cols [j] - conta) {
              vc = contaVazio (e, i - 1, j, e.tab [i] [j]);
              if (vc > e.seg_cols [j])
                vc = e.seg_cols [j] - nBarcosC;
              for (k = i - 1; vc > 0; vc--, k--) {
                if (vc == 1) {
                  if (e.tab [k - 1] [j] == '^') {
                    e = comandoP(e, '#', k + 1, j + 1, qt++, s);
                  }
                  else
                    if (e.tab [k - 1] [j] == '#') {
                      e = comandoP(e, '#', k + 1, j + 1, qt++, s);
                    }
                    else {
                      e = comandoP(e, '^', k + 1, j + 1, qt++, s);
                    }
                }
                else {
                  if (e.seg_lins [k - 1] - contaBarcos (e, k - 1, 0, 'l') != 0) {
                    e = comandoP(e, '#', k + 1, j + 1, qt++, s);
                  }
                  else {
                    e = comandoP(e, '^', k + 1, j + 1, qt++, s);
                    vc = 0;
                  }
                }
              }
            }
          }
          else
            if (e.tab [i] [j] == '^') {
              conta = nBarcosC;
              vc = contaCol (e, j);
              if (vc >= e.seg_cols [j] - conta) {
                vc = contaVazio (e, i + 1, j, e.tab [i] [j]);
                if (vc > e.seg_cols [j])
                  vc = e.seg_cols [j] - nBarcosC;
                for (k = i + 1; vc > 0; vc--, k++) {
                  if (vc == 1) {
                    if (e.tab [k + 1] [j] == 'v') {
                      e = comandoP(e, '#', k + 1, j + 1, qt++, s);
                    }
                    else
                      if (e.tab [k + 1] [j] == '#') {
                        e = comandoP(e, '#', k + 1, j + 1, qt++, s);
                      }
                      else {
                        e = comandoP(e, 'v', k + 1, j + 1, qt++, s);
                      }
                  }
                  else {
                    if (e.seg_lins [k + 1] - contaBarcos (e, k + 1, 0, 'l') != 0) {
                      e = comandoP(e, '#', k + 1, j + 1, qt++, s);
                    }
                    else {
                      e = comandoP(e, 'v', k + 1, j + 1, qt++, s);
                      vc = 0;
                    }
                  }
                }
              }
            }
            else
              if (e.tab [i] [j] == '#') {
                if (eBarco (e, i, j - 1) && e.tab [i] [j + 1] == '.') {
                  vl = contaVazio (e, i, j + 1, e.tab [i] [j]);
                  for (k = j + 1; vl > 0; vl--, k++) {
                    if (vl == 1) {
                      if (e.tab [i] [k + 1] == '>') {
                        e = comandoP(e, '#', i + 1, k + 1, qt++, s);
                      }
                      else {
                        e = comandoP(e, '>', i + 1, k + 1, qt++, s);
                      }
                    }
                    else {
                      e = comandoP(e, '#', i + 1, k + 1, qt++, s);
                    }
                  }
                }
                else
                  if (eBarco (e, i, j + 1) && e.tab [i] [j - 1] == '.') {
                    vl = contaVazio (e, i, j - 1, e.tab [i] [j]);
                    for(k = j - 1; vl > 0; vl--, k--) {
                      if (vl == 1) {
                        if (e.tab [i] [k - 1] == '<') {
                          e = comandoP(e, '#', i + 1, k + 1, qt++, s);
                        }
                        else
                          if (e.tab [i] [k - 1] == '#') {
                            e = comandoP(e, '#', i + 1, k + 1, qt++, s);
                          }
                        else {
                          e = comandoP(e, '<', i + 1, k + 1, qt++, s);
                        }
                      }
                      else {
                        e = comandoP(e, '#', i + 1, k + 1, qt++, s);
                      }
                    }
                  }
                else
                  if (eBarco (e, i - 1, j) && e.tab [i + 1] [j] == '.') {
                    vc = contaVazio (e, i + 1, j, e.tab [i] [j]);
                    for (k = i + 1; vc > 0; vc--, k++) {
                      if (vc == 1) {
                        if (e.tab [k + 1] [j] == 'v') {
                          e = comandoP(e, '#', k + 1, j + 1, qt++, s);
                        }
                        else
                          if (e.tab [k + 1] [j] == '#') {
                            e = comandoP(e, '#', k + 1, j + 1, qt++, s);
                          }
                        else {
                          e = comandoP(e, 'v', k + 1, j + 1, qt++, s);
                        }
                      }
                      else {
                        e = comandoP(e, '#', k + 1, j + 1, qt++, s);
                      }
                    }
                  }
                else
                  if (eBarco (e, i + 1, j) && e.tab [i - 1] [j] == '.') {
                    vc = contaVazio (e, i - 1, j, e.tab [i] [j]);
                    for (k = i - 1; vc > 0; vc--, k--) {
                      if (vc == 1) {
                        if (e.tab [k - 1] [j] == '^') {
                          e = comandoP(e, '#', k + 1, j + 1, qt++, s);
                        }
                        else
                          if (e.tab [k - 1] [j] == '#') {
                            e = comandoP(e, '#', k + 1, j + 1, qt++, s);
                          }
                        else {
                          e = comandoP(e, '^', k + 1, j + 1, qt++, s);
                        }
                      }
                      else {
                        e = comandoP(e, '#', k + 1, j + 1, qt++, s);
                      }
                    }
                  }
              }
            else
              if (e.tab [i] [j] == '.') {
                vl = contaLin(e, i);
                vc = contaCol (e, j);
                if ((vl >= e.seg_lins [i] - nBarcosL) && (vc >= e.seg_cols [j] - nBarcosC) && (e.seg_lins [i] - nBarcosL != 0) && (e.seg_cols [j] - nBarcosC != 0)) {
                  if (e.tab [i-1] [j] == '~' && e.tab [i+1] [j] == '~' && e.tab [i] [j-1] == '~' && e.tab [i] [j+1] == '.' && i != 0 && j != 0) {
                    e = comandoP(e, '<', i + 1, j + 1, qt++, s);
                  }
                  else
                    if (e.tab [i-1] [j] == '~' && e.tab [i+1] [j] == '~' && e.tab [i] [j+1] == '~' && e.tab [i] [j-1] == '.') {
                      e = comandoP(e, '>', i + 1, j + 1, qt++, s);
                    }
                  else
                    if (e.tab [i] [j+1] == '~' && e.tab [i+1] [j] == '~' && e.tab [i] [j-1] == '.' && i == 0) {
                      e = comandoP(e, '>', i + 1, j + 1, qt++, s);
                    }
                  else
                    if (e.tab [i] [j-1] == '~' && e.tab [i+1] [j] == '~' && e.tab [i] [j+1] == '.' && i == 0) {
                      e = comandoP(e, '<', i + 1, j + 1, qt++, s);
                    }
                  else
                    if (e.tab [i+1] [j] == '~' && e.tab [i] [j+1] == '.' && i == 0 && j == 0) {
                      e = comandoP(e, '<', i + 1, j + 1, qt++, s);
                    }
                  else
                    if (e.tab [i+1] [j] == '~' && e.tab [i] [j-1] == '.' && e.tab [i] [j + 1] == '~' && i == 0) {
                      e = comandoP(e, '>', i + 1, j + 1, qt++, s);
                    }
                  else
                    if (e.tab [i-1] [j] == '~' && e.tab [i+1] [j] == '~' && e.tab [i] [j+1] == '.' && j == 0) {
                      e = comandoP(e, '<', i + 1, j + 1, qt++, s);
                    }
                  else
                    if (e.tab [i-1] [j] == '~' && e.tab [i+1] [j] == '~' && e.tab [i] [j+1] == '.' && j == e.colunas - 1) {
                      e = comandoP(e, '>', i + 1, j + 1, qt++, s);
                    }
                  else
                    if (j == 0 && i == e.linhas - 1 && e.tab [i-1] [j] == '~' && e.tab [i] [j+1] == '.') {
                      e = comandoP(e, '<', i + 1, j + 1, qt++, s);
                    }
                  else
                    if (e.tab [i-1] [j] == '~' && e.tab [i] [j-1] == '.' && j == e.colunas - 1 && i == e.linhas - 1) {
                      e = comandoP(e, '>', i + 1, j + 1, qt++, s);
                    }
                  else
                    if (e.tab [i] [j-1] == '~' && e.tab [i-1] [j] == '~' && e.tab [i] [j+1] == '.' && i == e.linhas - 1) {
                      e = comandoP(e, '<', i + 1, j + 1, qt++, s);
                    }
                  else
                    if (e.tab [i] [j+1] == '~' && e.tab [i-1] [j] == '~' && eBarco (e, i, j - 1) && i == e.linhas - 1) {
                      e = comandoP(e, '>', i + 1, j + 1, qt++, s);
                    }
                  else
                    if (eSubmarino (e, i, j) == 1) {
                      e = comandoP(e, 'O', i + 1, j + 1, qt++, s);
                    }
                  else
                    j++;
                  j--;
                }
                if (vc >= e.seg_cols [j] - nBarcosC && vl >= e.seg_lins [i] - nBarcosL && e.seg_cols [j] - nBarcosC != 0 && e.seg_lins [i] - nBarcosL != 0) {
                  if (e.tab [i+1] [j] == '.' && e.tab [i] [j+1] == '~'  && i == 0 && j == 0) {
                    e = comandoP(e, '^', i + 1, j + 1, qt++, s);
                  }
                  else
                    if (e.tab [i] [j-1] == '~' && e.tab [i] [j+1] == '~' && e.tab [i+1] [j] == '.' && i == 0 && j != e.colunas - 1) {
                      e = comandoP(e, '^', i + 1, j + 1, qt++, s);
                    }
                  else
                    if (e.tab [i] [j-1] == '~' && e.tab [i+1] [j] == '.' && i == 0 && j == e.colunas - 1) {
                      e = comandoP(e, '^', i + 1, j + 1, qt++, s);
                    }
                  else
                    if (e.tab [i] [j+1] == '~' && e.tab [i-1] [j] == '~' && e.tab [i+1] [j] == '.' && j == 0 && i != e.linhas - 1) {
                      e = comandoP(e, '^', i + 1, j + 1, qt++, s);
                    }
                  else
                    if (e.tab [i-1] [j] == '.' && e.tab [i] [j-1] == '~' && i == e.linhas - 1 && j == e.colunas - 1) {
                      e = comandoP(e, 'v', i + 1, j + 1, qt++, s);
                    }
                  else
                    if (e.tab [i-1] [j] == '.' && e.tab [i] [j+1] == '~' && i == e.linhas - 1 && j == 0) {
                      e = comandoP(e, 'v', i + 1, j + 1, qt++, s);
                    }
                  else
                    if (e.tab [i] [j-1] == '~' && e.tab [i-1] [j] == '.' && e.tab [i+1] [j] == '~' && j == e.colunas - 1 && i == e.linhas - 1) {
                      e = comandoP(e, 'v', i + 1, j + 1, qt++, s);
                    }
                  else
                    if (e.tab [i-1] [j] == '~' && e.tab [i] [j-1] == '~' && e.tab [i+1] [j] == '.' && j == e.colunas - 1) {
                      e = comandoP(e, '^', i + 1, j + 1, qt++, s);
                    }
                  else
                    if (e.tab [i-1] [j] == '.' && e.tab [i] [j-1] == '~' && e.tab [i] [j+1] == '~' && i == e.linhas - 1) {
                      e = comandoP(e, 'v', i + 1, j + 1, qt++, s);
                    }
                  else
                    if (e.tab [i-1] [j] == '.' && e.tab [i+1] [j] == '~' && e.tab [i] [j+1] == '~' && j == 0) {
                      e = comandoP(e, 'v', i + 1, j + 1, qt++, s);
                    }
                  else
                    if (e.tab [i] [j-1] == '~' && e.tab [i-1] [j] == '.' && e.tab [i] [j+1] == '~' && e.tab [i+1] [j] == '~') {
                      e = comandoP(e, 'v', i + 1, j + 1, qt++, s);
                    }
                  else
                    if (e.tab [i] [j+1] == '~' && e.tab [i] [j-1] == '~' && e.tab [i-1] [j] == '~' && e.tab [i+1] [j] == '.') {
                      e = comandoP(e, '^', i + 1, j + 1, qt++, s);
                    }
                  else
                    if (eSubmarino (e, i, j) == 1) {
                      e = comandoP(e, 'O', i + 1, j + 1, qt++, s);
                    }
                  else
                    j++;
                  j--;
                }
              }
          }
        }
  return e;
}


/** Função verifica: aplica diversos testes sobre um tabuleiro e escreve no ecrã "SIM" caso este seja válido ou "NAO" caso contrário.
@param *e Endereço do tabuleiro
@param *s Endereço da stack
@return É uma função void, logo nao retorna nada
*/


void verifica (tabuleiro *e, stack *s) {
  int i ,j ,v = 0;
  char barco = '>' || '<' || '^' || 'v' || '#' || 'O' || 'o';
  *e = comandoE1 (*e, s);
  for (i = 0; v != 1 && i < e -> linhas; i++) {
    for (j = 0; v != 1 && j < e -> colunas ; j++) {
      if (contaLinhas (*e, i) < e -> seg_lins [i])
        v = 1;
      if (contaColunas (*e, j) < e -> seg_cols [j])
        v = 1;

      if (eBarco (*e, i, j)) {
        if (eBarco (*e, i - 1, j - 1) || eBarco (*e, i - 1, j + 1) || eBarco (*e, i + 1, j - 1) || eBarco (*e, i + 1, j + 1))
          v = 1;
      }

      if (e -> tab [i] [j] == '#' && v != 1) {
        if ((i == 0 && j == 0) || (i == 0 && j == e -> colunas - 1) || (i == e -> linhas - 1 && j == 0) || (i == e -> linhas - 1 && j == e -> colunas - 1))
          v = 1;
        else
          if (i == 0) {
            if ((strchr ("~", e -> tab [i] [j - 1]) == NULL ) && e -> tab [i + 1] [j] != barco && (strchr ("~", e -> tab [i] [j + 1]) == NULL ));
            else
              v = 1;
        }
        else
          if (j == 0) {
            if ((strchr ("~", e -> tab [i - 1] [j]) == NULL ) && (strchr ("~", e -> tab [i + 1] [j]) == NULL ) && e -> tab [i] [j + 1] != barco);
            else
              v = 1;
        }
        else
          if (i == e -> linhas -1) {
            if ((strchr ("~", e -> tab [i] [j - 1]) == NULL ) && (strchr ("~", e -> tab [i] [j + 1]) == NULL ) && e -> tab [i - 1] [j] != barco);
            else
              v = 1;
        }
        else
          if (j == e -> colunas - 1) {
            if ((strchr ("~", e -> tab [i - 1] [j]) == NULL) && e -> tab [i] [j - 1] != barco && (strchr ("~", e -> tab [i + 1] [j]) == NULL ));
            else
              v = 1;
        }
        else
          if ((strchr ("~", e -> tab [i - 1] [j]) == NULL ) && (strchr ("~", e -> tab [i + 1] [j]) == NULL ) && e -> tab [i] [j + 1] != barco && e -> tab [i] [j - 1] != barco);
          else
            if (e -> tab [i - 1] [j] != barco && e -> tab [i + 1] [j] != barco && (strchr ("~", e -> tab [i] [j + 1]) == NULL ) && (strchr ("~", e -> tab [i] [j - 1]) == NULL ));
          else
            v = 1;
      }
      else
        if (e -> tab [i] [j] == 'o' && v != 1) {
          if (i == 0 && j == 0) {
            if ((strchr ("~", e -> tab [i] [j + 1]) == NULL ) && e -> tab [i + 1] [j] != barco);
            else
              if ((strchr ("~", e -> tab [i + 1] [j]) == NULL ) && e -> tab [i] [j + 1] != barco);
            else
              v = 1;
          }
          else
            if (i == 0 && j == e -> colunas - 1) {
              if ((strchr ("~", e -> tab [i] [j - 1]) == NULL ) && e -> tab [i + 1] [j] != barco);
              else
                if ((strchr ("~", e -> tab [i + 1] [j]) == NULL ) && e -> tab [i] [j - 1] != barco);
              else
                v = 1;
          }
          else
            if (i == e -> linhas - 1 && j == 0) {
              if ((strchr ("~", e -> tab [i] [j + 1]) == NULL ) && e -> tab [i - 1] [j] != barco);
              else
                if ((strchr ("~", e -> tab [i - 1] [j]) == NULL ) && e -> tab [i] [j + 1] != barco);
              else
                v = 1;
          }
          else
            if (i == e -> linhas -1  && j == e -> colunas - 1) {
              if ((strchr ("~", e -> tab [i] [j - 1]) == NULL ) && e -> tab [i - 1] [j] != barco);
              else
                if ((strchr ("~", e -> tab [i - 1] [j]) == NULL ) && e -> tab [i] [j - 1] != barco);
              else
                v = 1;
          }
          else
            if (i == 0) {
              if ((strchr ("~", e -> tab [i] [j - 1]) == NULL || strchr ("~", e -> tab [i] [j + 1]) == NULL  ) && e -> tab [i + 1] [j] != barco);
              else
                if ((strchr ("~", e -> tab [i + 1] [j]) == NULL ) && e -> tab [i] [j + 1] != barco && e -> tab [i] [j - 1] != barco);
              else
                v = 1;
          }
          else
            if (j == 0) {
              if ((strchr ("~", e -> tab [i] [j + 1]) == NULL ) && e -> tab [i + 1] [j] != barco && e -> tab [i - 1] [j] != barco);
              else
                if ((strchr ("~", e -> tab [i + 1] [j]) == NULL || strchr ("~", e -> tab [i - 1] [j]) == NULL  ) && e -> tab [i] [j + 1] != barco);
              else
                v = 1;
          }
          else
            if (i == e -> linhas - 1) {
              if ((strchr ("~", e -> tab [i] [j - 1]) == NULL || strchr ("~", e -> tab [i] [j + 1]) == NULL  ) && e -> tab [i - 1] [j] != barco);
              else
                if ((strchr ("~", e -> tab [i - 1] [j]) == NULL ) && e -> tab [i] [j + 1] != barco && e -> tab [i] [j - 1] != barco);
              else
                v = 1;
          }
          else
            if ( j == e -> colunas - 1) {
              if ((strchr ("~", e -> tab [i] [j - 1]) == NULL ) && e -> tab [i + 1] [j] != barco && e -> tab [i - 1] [j] != barco);
              else
                if ((strchr ("~", e -> tab [i + 1] [j]) == NULL || strchr ("~", e -> tab [i - 1] [j]) == NULL  ) && e -> tab [i] [j - 1] != barco);
              else
                v = 1;
          }
          else
            if ((strchr ("~", e -> tab [i - 1] [j]) == NULL ) && e -> tab [i] [j + 1] != barco && e -> tab [i] [j - 1] != barco);
            else
              if ((strchr ("~", e -> tab [i + 1] [j]) == NULL ) && e -> tab [i] [j - 1] != barco && e -> tab [i] [j + 1] != barco);
              else
                if ((strchr ("~", e -> tab [i] [j - 1]) == NULL ) && e -> tab [i - 1] [j] != barco && e -> tab [i + 1] [j] != barco);
                else
                  if ((strchr ("~", e -> tab [i] [j + 1]) == NULL ) && e -> tab [i - 1] [j] != barco && e -> tab [i + 1] [j] != barco);
            else
              v = 1;
      }
      else
        if (e -> tab [i] [j] == 'v' && v != 1) {
          if (i == 0)
            v = 1;
          if (i == e -> linhas - 1 && j == 0) {
            if ((strchr ("~", e -> tab [i - 1] [j]) == NULL ) && e -> tab [i] [j + 1] != barco);
            else
              v = 1;
          }
          else
            if (i == e -> linhas - 1 && j == e -> colunas - 1) {
              if (e -> tab [i] [j - 1] != barco && (strchr ("~", e -> tab [i - 1] [j]) == NULL ));
              else
                v = 1;
          }
          else
            if (j == 0) {
              if (e -> tab [i] [j + 1] != barco && e -> tab [i + 1] [j] != barco && (strchr ("~", e -> tab [i - 1] [j]) == NULL ));
              else
                v = 1;
            }
          else
            if (j == e -> colunas - 1) {
              if (e -> tab [i] [j - 1] != barco && e -> tab [i + 1] [j] != barco && (strchr ("~", e -> tab [i - 1] [j]) == NULL ));
              else
                v = 1;
            }
          else
            if (i == e -> linhas - 1) {
              if (e -> tab [i] [j - 1] != barco && e -> tab [i] [j + 1] != barco && (strchr ("~", e -> tab [i - 1] [j]) == NULL ));
              else
                v = 1;
            }
          else
            if (e -> tab [i] [j - 1] != barco && e -> tab [i] [j + 1] != barco && e -> tab [i + 1] [j] != barco && (strchr ("~", e -> tab [i - 1] [j]) == NULL ));
            else
              v = 1;
      }
      else
        if (e -> tab [i] [j] == '^' && v != 1) {
          if (i == 0 && j == 0) {
            if (e -> tab [i] [j + 1] != barco && (strchr ("~", e -> tab [i + 1] [j]) == NULL ));
            else
              v = 1;
        }
        else
          if (i == 0 && j == e -> colunas - 1){
            if (e -> tab [i] [j - 1] != barco && (strchr ("~", e -> tab [i + 1] [j]) == NULL ));
            else
              v = 1;
        }
        else
          if (i == 0) {
            if (e -> tab [i] [j - 1] != barco && e -> tab [i] [j + 1] != barco && (strchr ("~", e -> tab [i + 1] [j]) == NULL ));
            else
              v = 1;
        }
        else
          if (j == 0) {
            if (e -> tab [i - 1] [j] != barco && e -> tab [i] [j + 1] != barco && (strchr ("~", e -> tab [i + 1] [j]) == NULL ));
            else
              v = 1;
        }
        else
          if (j == e -> colunas - 1) {
            if (e -> tab [i - 1] [j] != barco && e -> tab [i] [j - 1] != barco && (strchr ("~", e -> tab [i + 1] [j]) == NULL ));
            else
              v = 1;
        }
        else
          if (e -> tab [i] [j - 1] != barco && e -> tab [i] [j + 1] != barco && e -> tab [i - 1] [j] != barco && (strchr ("~", e -> tab [i + 1] [j]) == NULL ));
          else
            v = 1;
      }
      else
        if (e -> tab [i] [j] == 'O' && v != 1) {
          if (eSubmarino (*e, i, j) == 0)
            v = 1;
      }
      else
        if (e -> tab [i] [j] == '>' && v != 1) {
          if (j == 0)
            v = 1;
          else
            if (i == 0 && j == e -> colunas - 1) {
              if (e -> tab [i + 1] [j] != barco && (strchr ("~", e -> tab [i] [j - 1]) == NULL ));
              else
                v = 1;
            }
          else
            if (i == e -> linhas - 1 && j == e -> colunas - 1) {
              if (e -> tab [i - 1] [j] != barco && (strchr ("~", e -> tab [i] [j - 1]) == NULL ));
              else
                v = 1;
            }
          else
            if (i == 0) {
              if (e -> tab [i] [j + 1] != barco && e -> tab [i + 1] [j] != barco && strchr ("~", e -> tab [i] [j - 1]) == NULL);
              else
                v = 1;
            }
          else
            if (j == e -> colunas - 1) {
              if (e -> tab [i - 1] [j] != barco && e -> tab [i + 1] [j] != barco && (strchr ("~", e -> tab [i] [j - 1]) == NULL ));
              else
                v = 1;
            }
          else
            if (i == e -> linhas - 1) {
              if (e -> tab [i - 1] [j] != barco && e -> tab [i] [j + 1] != barco && (strchr ("~", e -> tab [i] [j - 1]) == NULL ));
              else
                v = 1;
            }
          else
            if (e -> tab [i] [j + 1] != barco && e -> tab [i + 1] [j] != barco && e -> tab [i - 1] [j] != barco && (strchr ("~", e -> tab [i] [j - 1]) == NULL ));
            else
              v = 1;
        }
      else
        if (e -> tab [i] [j] == '<' && v != 1) {
          if (j == e -> colunas - 1)
            v = 1;
          else
            if (i == 0 && j == 0) {
              if (e -> tab [i + 1] [j] != barco && strchr ("~", e -> tab [i] [j + 1]) == NULL);
              else
                v = 1;
            }
          else
            if (i == e -> linhas - 1 && j == 0) {
              if (e -> tab [i - 1] [j] != barco && strchr ("~", e -> tab [i] [j + 1]) == NULL);
              else
                v = 1;
            }
          else
            if (j == 0) {
              if (e -> tab [i + 1] [j] != barco && e -> tab [i - 1] [j] != barco && (strchr ("~", e -> tab [i] [j + 1]) == NULL ));
              else
                v = 1;
            }
          else
            if (i == 0) {
              if (e -> tab [i + 1] [j] != barco && e -> tab [i] [j - 1] != barco && (strchr ("~", e -> tab [i] [j + 1]) == NULL ));
              else
                v = 1;
            }
          else
            if (i == e -> linhas - 1) {
              if (e -> tab [i - 1] [j] != barco && e -> tab [i] [j - 1] != barco && strchr ("~", e -> tab [i] [j + 1]) == NULL);
              else
                v = 1;
            }
          else
            if (e -> tab [i] [j - 1] != barco && e -> tab [i + 1] [j] != barco && e -> tab [i - 1] [j] != barco && (strchr ("~", e -> tab [i] [j + 1]) == NULL ||  e -> tab [i] [j + 1] == '.'));
            else
              v = 1;
      }
    }
  }
  if (v == 0)
    printf("SIM\n");
  else printf("NAO\n");
  *e = comandoD (*e, s);
}


/** Função comandoD: recebe um tabuleiro e uma stack e permite-nos anular comandos anteriormente dados.
@param e Tabuleiro
@param *s Endereço da stack
@return Retorna o tabuleiro depois de todas as anulações
*/


tabuleiro comandoD (tabuleiro e, stack *s) {
  int qt = s -> valores [s -> top].qt;
  int i;
  if (s -> valores [s -> top].c == 'R') {
    e = pop (e, s, s -> valores [s -> top].i, s -> valores [s -> top].j, s -> valores [s -> top].c);
    for (i = 3; i > 0; i--) {
      qt = s -> valores [s -> top].qt;
      while (qt > 0 && s -> top != -1) {
        e = pop (e, s, s -> valores [s -> top].i, s -> valores [s -> top].j, s -> valores [s -> top].c);
        qt--;
      }
    }
  }
  else
    while (qt > 0 && s -> top != -1) {
      e = pop (e, s, s -> valores [s -> top].i, s -> valores [s -> top].j, s -> valores [s -> top].c);
      qt--;
    }
  return e;
}
