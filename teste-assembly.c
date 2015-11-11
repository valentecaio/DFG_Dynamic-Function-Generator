#include <math.h>
#include <stdio.h>
#include "cria_func.h"

typedef int (*funcp) (int);
typedef int (*funcp2) (funcp, int);

int main (void) {
	float a;
	printf("\n\nTestando assembly: ");
	a = assemblyFoo(2.0,4.0);
	printf ("%f", a);
	return 0;
}
