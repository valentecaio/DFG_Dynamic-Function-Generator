#include <math.h>
#include <stdio.h>
#include "cria_func.h"

typedef int (*funcp) ();
typedef int (*funcp1) (int);
typedef int (*funcp2) (int, int);
typedef int (*funcp3) (int, void*);
typedef float (*funcp4) (int, float);
typedef double (*funcp5) (int, double);
typedef void* (*funcp6) ();
typedef void (*funcp7) (void*);


float soma (int a, int b, float c) {
	return a+b+c;
}

void print_strings (char *a, char *b, char *c) {
	printf ("\n\nstring a: %s\nstring b: %s\nstring c: %s\n\n", a, b,c);
}

int main (void) {
	DescParam params[3];
	//int p0=2000,p1=4;
	char a[]="elfos";
	char b[]="gnomos";
	char c[]="ogros";
	void *d = &c;
	//double p2 = 2.5;
	//float p2 = 2.5;
	funcp7 f_gerada = NULL;
	
	params[0].tipo_val = PTR_PAR;
	params[0].orig_val = FIX_DIR;
	params[0].valor.v_ptr = a;
	params[1].tipo_val = PTR_PAR;
	params[1].orig_val = PARAM;
	params[2].tipo_val = PTR_PAR;
	params[2].orig_val = FIX_IND;
	params[2].valor.v_ptr = &d;
	print_end (&d, "&d");
	print_end (&c, "&c");
	
	f_gerada = (funcp7) cria_func (print_strings, params, 3);
	
	printf("\nTESTE EXECUTADO\n\nesperado:");
	print_strings(a, b, c);
	printf("\n\nobtido:");
	f_gerada(b);
	
	d = &a;
	printf("\n\nmodifiquei o ponteiro d!\n\n");
	
	printf("\nTESTE EXECUTADO\n\nesperado:");
	print_strings(a, b, a);
	printf("\n\nobtido:");
	f_gerada(b);
	
	return 0;
}
