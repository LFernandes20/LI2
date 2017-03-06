#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "battleship.h"
#include "aux.h"
#include "t1.h"
#include "t2.h"


/** Função comandoR: recebe um tabuleiro e resolve-o, usando para isso as estratégias definidas na etapa 2.
*
* @param e Tabuleiro
* @param *s Endereço da Stack
* @return Retorna o tabuleiro resultante depois da execução das estratégias.
*
*/


tabuleiro comandoR (tabuleiro e, stack *s) {
	int i, j, flag = 0, count;
	while (flag != -1) {
		count = 0;
		e = comandoE1 (e, s);
		e = comandoE2 (e, s);
		e = comandoE1 (e, s);
		e = comandoE3 (e, s);
		push (s, 0, 0,'R', 1);
		for (i = 0; i < e.linhas; i++) {
			for (j = 0; j < e.colunas; j++) {
				if (strchr ("o.", e.tab [i] [j]) == NULL)
					count++;
			}
		}
		if (count != e.linhas * e.colunas)
			flag = 0;
		else
			flag = -1;
	}
	return e;
}
