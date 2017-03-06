#ifndef auxBattleship_h
#define auxBattleship_h

int contaCol (tabuleiro e, int j);
int contaLin (tabuleiro e, int i);
int contaVazio (tabuleiro e, int i, int j, char c);
int contaBarcos (tabuleiro e, int i, int j, char q);
/* Funções V */
int contaLinhas (tabuleiro e, int i);
int contaColunas (tabuleiro e, int j);
int eSubmarino (tabuleiro e, int i, int j);
int eBarco (tabuleiro e, int i, int j);
/* Funções Stack */
void push (stack *s, int i, int j, char c, int qt);
tabuleiro pop (tabuleiro e, stack *s, int i, int j, char c);

#endif
