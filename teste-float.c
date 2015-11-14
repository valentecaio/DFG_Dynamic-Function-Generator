#include <math.h>
#include <stdio.h>
#include "cria_func.h"

typedef int (*funcp) ();
typedef int (*funcp1) (int);
typedef int (*funcp2) (int, int);
typedef int (*funcp3) (int, void*);
typedef float (*funcp4) (int, float);
typedef double (*funcp5) (int, double);
typedef float (*funcp6) (float);
typedef float (*funcp7) ();
typedef float (*funcp8) (int, float);

float soma (int a, float b, float c, float d) {
	return a+b+c+d;
}

int main (void) {
	DescParam params[5];
	int p0=2;
	//double p2 = 2.5;
	float p2 = 2.5, p1=3.7, p3=8.1;
	funcp8 f_gerada = NULL;
	
	params[0].tipo_val = INT_PAR;
	params[0].orig_val = PARAM;
	params[1].tipo_val = FLOAT_PAR;
	params[1].orig_val = PARAM;
	params[2].tipo_val = FLOAT_PAR;
	params[2].orig_val = FIX_IND;
	params[2].valor.v_ptr = &p2;
	params[3].tipo_val = FLOAT_PAR;
	params[3].orig_val = FIX_DIR;
	params[3].valor.v_float = p3;
	
	f_gerada = (funcp8) cria_func (soma, params, 4);
	
	printf("\nTESTE EXECUTADO\n\nesperado: %f, obtido: %f\n\n", soma(p0, p1, p2, p3), f_gerada(p0, p1));
	
	p2 = 4.0;
	printf("\nMUDEI O PONTEIRO!\n\nesperado: %f, obtido: %f\n\n", soma(p0, p1, p2, p3), f_gerada(p0, p1));
	
	return 0;
}
