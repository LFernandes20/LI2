#ifndef t1_h
#define t1_h

tabuleiro carregar (tabuleiro e, stack *s);
void mostrar (tabuleiro e);
tabuleiro comandoP (tabuleiro e, char c, int i, int j, int qt, stack *s);
tabuleiro comandoH (tabuleiro e, int i, stack *s);
tabuleiro comandoV (tabuleiro e, int j, stack *s);

#endif
