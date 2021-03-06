#include <math.h>
#include <stdio.h>
#include "cria_func.h"

typedef int (*funcp) ();
typedef int (*funcp1) (int);
typedef int (*funcp2) (int, int);

int soma (int a, int b, int c) {
	return a+b+c;
}

int main (void) {
	DescParam params[3];
	int p0=2000,p1=4, p2=-230;
	funcp f_gerada = NULL;

	params[0].tipo_val = INT_PAR;
	params[0].orig_val = FIX_DIR;
	params[0].valor.v_int = p0;
	params[1].tipo_val = INT_PAR;
	params[1].orig_val = PARAM;
	params[2].tipo_val = INT_PAR;
	params[2].orig_val = PARAM;

	f_gerada = (funcp2) cria_func (soma, params, 3);
	printf("\nTESTE EXECUTADO\n\nesperado: %d, obtido: %d\n\n", soma(p0,p1, p2), f_gerada(p1, p2));
	return 0;
}
