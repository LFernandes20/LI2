#ifndef battleship_h
#define battleship_h
#define MAX_SIZE 1024
#define MAX_COLS 101
#define MAX_LINS 101

/**
@param linhas Número de linhas do tabuleiro
@param colunas Número de colunas do tabuleiro
@param seg_lins Array com o número de segmentos de barcos nas linhas
@param seg_cols Array com o número de segmentos de barcos nas colunas
@param tab Matriz com os caractéres do tabuleiro
*/

typedef struct tabuleiro {
  int linhas;
  int colunas;
  int seg_lins [MAX_LINS];
  char seg_cols [MAX_COLS];
  char tab [MAX_LINS] [MAX_COLS];
} tabuleiro;

/**
@param i Posição nas linhas
@param j Posição nas colunas
@param qt Quantidade de comandos executados por cada função
@param c Caractér que estava na posição [i] [j]
*/

typedef struct elemS {
  int i, j, qt;
  char c;
} elemS;

/**
@param valores Array com elementos do tipo elemS
@param top Posição atual no Array
*/

typedef struct stack {
  elemS valores [100000];
  int top;
} stack;

int interpretador (tabuleiro *tab, stack *s);
int main();

#endif
