#include <math.h>
#include <stdio.h>
#include "cria_func.h"

typedef int (*funcp) ();
typedef int (*funcb) (int);
typedef double (*funcc) (int, int);
typedef int (*funcd) (int, void*);
typedef float (*funcp4) (int, float);
typedef double (*funcp5) (int, double);
typedef float (*funcp6) (float);
typedef float (*funcp7) ();
typedef float (*funcp8) (int, float);

double soma (int a, int b, double c, float d, int e) {
	printf ("a = %d,\tb = %d,\tc = %.1f,\td = %.1f,\te = %d\n", a, b, c, d, e);
	return a+b+c+d;
}

int main (void) {
	DescParam params[10];
	int a=2, e=6, b=4;
	double d=5.2; 
	//float c = 3.0;
	double c = 3.0;

	funcc f_gerada = NULL;
	//funcp4 f_gerada = NULL;
	
	params[0].tipo_val = INT_PAR;
	params[0].orig_val = PARAM;
	params[1].tipo_val = INT_PAR;
	params[1].orig_val = PARAM;
	params[2].tipo_val = DOUBLE_PAR;
	params[2].orig_val = FIX_IND;
	params[2].valor.v_ptr = &c;
	params[3].tipo_val = FLOAT_PAR;
	params[3].orig_val = FIX_DIR;
	params[3].valor.v_float = (float)d;
	params[4].tipo_val = INT_PAR;
	params[4].orig_val = FIX_DIR;
	params[4].valor.v_int = e;
	
	f_gerada = (funcc) cria_func (soma, params, 5);
	//f_gerada = (funcp4) cria_func (soma, params, 5);
	
	printf("\nTESTE EXECUTADO\n\nesperado: %f, obtido: %f\n\n",
	       soma(a, b, c, (float)d, e), f_gerada(a, b));
	
	c *= 2;
	printf("\nMUDEI O PONTEIRO!\n\nesperado: %f, obtido: %f\n\n",
	       soma(a, b, c, (float)d, e), f_gerada(a, b));
	
	return 0;
}
