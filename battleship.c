#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "battleship.h"
#include "auxBattleship.h"
#include "t1.h"
#include "t2.h"
#include "t3.h"


/** Função interpretador: esta função mantém um ciclo para o utilizador poder inserir comandos.git 
@param *tab Endereço do tabuleiro
@param *s Endereço da stack
@return O programa retorna sempre 0
*/


int interpretador (tabuleiro *tab, stack *s) {
  char linha [MAX_SIZE];
  char cmd [MAX_SIZE];
  char arg1 [MAX_SIZE];
  char arg2 [MAX_SIZE];
  int nargs = 0, res = 1, conta = 0;

  while (res != 0) {
    if (fgets (linha, MAX_SIZE, stdin) != NULL)

      nargs = sscanf (linha, "%s %s %s", cmd, arg1, arg2);

      if (strcmp (cmd, "c") == 0 && nargs == 1) {
        *tab = carregar (*tab, s);
      }
      else
        if (strcmp (cmd, "m") == 0 && nargs == 1){
          mostrar (*tab);
        }
        else
          if (strcmp (cmd, "h") == 0 && nargs == 2) {
            *tab = comandoH (*tab, atoi(arg1), s);
          }
          else
            if (strcmp (cmd, "l") == 0 && nargs == 2) {
              *tab = lerFicheiro(*tab, arg1, s);
            }
            else
              if (strcmp (cmd, "e") == 0 && nargs == 2) {
                escreverFile (*tab, arg1);
              }
              else
                if (strcmp (cmd, "v") == 0 && nargs == 2) {
                  *tab = comandoV (*tab, atoi(arg1), s);
                }
                else
                  if ((cmd [0]=='p') && nargs == 3) {
                    *tab = comandoP (*tab, cmd[1], atoi (arg1), atoi (arg2), 1, s);
                  }
                  else
                    if ((cmd [0] == 'E') && nargs == 1) {
                      if (cmd [1] - '0' == 1)
                        *tab = comandoE1 (*tab, s);
                      else
                        if (cmd [1] - '0' == 2)
                          *tab = comandoE2 (*tab, s);
                        else
                          *tab = comandoE3 (*tab, s);
                    }
                    else
                      if (strcmp (cmd, "V") == 0) {
                        verifica (tab, s);
                      }
                      else
                        if (strcmp (cmd, "D") == 0) {
                          *tab = comandoD (*tab, s);
                        }
                        else
                          if (strcmp (cmd, "R") == 0) {
                            *tab = comandoR (*tab, s);
                          }
                          else
                            if (strcmp (cmd, "help") == 0 && nargs == 1)
                              printf ("c - Ler tabuleiro do standard input.\nm - Mostrar o tabuleiro no standard output.\nl <ficheiro> - Ler o tabuleiro a partir do ficheiro.\ne <ficheiro> - Escrever o tabuleiro no ficheiro.\nh <num> - Colocar o estado de todas as grelhas da linha nº 'num' que ainda não estão determinadas como sendo água.\nv <num> - Colocar o estado de todas as grelhas da coluna nº 'num' que ainda não estão determinadas como sendo água.\np<char> <l> <c> - Colocar o caracter <char> na linha l e coluna c.\n");
                            else
                              if (strcmp (cmd, "q") == 0 && nargs == 1)
                                res = 0;
                              else
                                printf ("Comando inválido!\n");
  }
  return conta;
}



/** Função main: esta função apenas chama a função interpretador.
*/


int main () {
  tabuleiro tab;
  stack s;
  s.top = -1;
  tab.linhas = 0;
  tab.colunas = 0;
  interpretador (&tab, &s);
  return 0;
}
