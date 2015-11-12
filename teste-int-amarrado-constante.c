#include <math.h>
#include <stdio.h>
#include "cria_func.h"

typedef int (*funcp) ();
typedef int (*funcp1) (int);
// typedef int (*funcp2) (funcp, int);

int soma (int a, int b) {
	return a+b;
}

int main (void) {
	DescParam params[2];
	int p0=2000,p1=4;
	funcp f_gerada = NULL;

	params[0].tipo_val = INT_PAR;
	params[0].orig_val = FIX_DIR;
	params[0].valor.v_int = p0;
	params[1].tipo_val = INT_PAR;
	params[1].orig_val = FIX_DIR;
	params[1].valor.v_int = p1;

	f_gerada = (funcp) cria_func (soma, params, 2);
	printf("\nTESTE EXECUTADO\n\nesperado: %d, obtido: %d\n\n", soma(p0,p1), f_gerada());
	return 0;
}
