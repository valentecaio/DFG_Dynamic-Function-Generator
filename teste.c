#include <math.h>
#include <stdio.h>
#include "cria_func.h"

typedef float (*funcp) (int, float, double, char[]);

float foo (int a1, int a2, int a3, float f1, float f2, float f3, double d1, 
	    double d2, double d3, char *c1, char *c2, char *c3) {
	printf ("\nINTEIROS:\na1 = %d,\ta2 = %d,\ta3 = %d\n", a1, a2, a3);
	printf ("\nFLOATS:\nf1 = %.1f,\tf2 = %.1f,\tf3 = %.1f\n", f1, f2, f3);
	printf ("\nDOUBLES:\nd1 = %.1f,\td2 = %.1f,\td3 = %.1f\n", d1, d2, d3);
	printf ("\nPONTEIROS:\nc1 = %s,\tc2 = %s,\tc3 = %s\n", c1, c2, c3);
	return (a1+a2+a3+f1+f2+f3+d1+d2+d3);
}

int main (void) {
	DescParam params[12];
	int	a1=1, a2=2, a3=3;
	float	f1=4.0, f2=5.0, f3=6.0;
	double	d1=7.0, d2=8.0, d3=9.0;
	char	*c1="c1", *c2="c2", *c3="c3", *c4="c3 foi alterada";
	float	resultado;
	
	funcp f_gerada = NULL;
	
	params[0].tipo_val = INT_PAR;
	params[0].orig_val = FIX_DIR;
	params[0].valor.v_int = a1;
	params[1].tipo_val = INT_PAR;
	params[1].orig_val = PARAM;
	params[2].tipo_val = INT_PAR;
	params[2].orig_val = FIX_IND;
	params[2].valor.v_ptr = &a3;
	
	params[3].tipo_val = FLOAT_PAR;
	params[3].orig_val = FIX_DIR;
	params[3].valor.v_float = f1;
	params[4].tipo_val = FLOAT_PAR;
	params[4].orig_val = PARAM;
	params[5].tipo_val = FLOAT_PAR;
	params[5].orig_val = FIX_IND;
	params[5].valor.v_ptr = &f3;
	
	params[6].tipo_val = DOUBLE_PAR;
	params[6].orig_val = FIX_DIR;
	params[6].valor.v_double = d1;
	params[7].tipo_val = DOUBLE_PAR;
	params[7].orig_val = PARAM;
	params[8].tipo_val = DOUBLE_PAR;
	params[8].orig_val = FIX_IND;
	params[8].valor.v_ptr = &d3;
	
	params[9].tipo_val = PTR_PAR;
	params[9].orig_val = FIX_DIR;
	params[9].valor.v_ptr = c1;
	params[10].tipo_val = PTR_PAR;
	params[10].orig_val = PARAM;
	params[11].tipo_val = PTR_PAR;
	params[11].orig_val = FIX_IND;
	params[11].valor.v_ptr = &c3;
	
	f_gerada = (funcp) cria_func (foo, params, 12);
	
	resultado = f_gerada(a2, f2, d2, c2);
	printf("\nTESTE EXECUTADO\n\nesperado: %f",
	       foo(a1,a2,a3,f1,f2,f3,d1,d2,d3,c1,c2,c3));
	printf(", obtido: %f\n\n", resultado);
	
	a3 *= 2; f3 *= 2; d3 *= 2;
	c3 = c4;
	
	resultado = f_gerada(a2, f2, d2, c2);
	printf("\nMUDEI OS PONTEIROS!\n\nesperado: %f",
	       foo(a1,a2,a3,f1,f2,f3,d1,d2,d3,c1,c2,c3));
	printf(", obtido: %f\n\n", resultado);
	
	return 0;
}
