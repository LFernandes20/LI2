#ifndef t2_h
#define t2_h

tabuleiro lerFicheiro (tabuleiro e, char *str, stack *s);
void escreverFile (tabuleiro e, char *str);
tabuleiro comandoE1 (tabuleiro e, stack *s);
tabuleiro comandoE2 (tabuleiro e, stack *s);
tabuleiro comandoE3 (tabuleiro e, stack *s);
void verifica (tabuleiro *e, stack *s);
tabuleiro comandoD (tabuleiro e, stack *s);

#endif
