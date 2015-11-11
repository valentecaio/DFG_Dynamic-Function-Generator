/*
 * arquivo para testar a funcao-desejada.s
 * gcc -Wall -m32 -o funcao-desejada funcao-desejada.s teste-assembly.c -lm
 * 
 * */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "cria_func.h"

int assemblyFoo (int a, int b);

int soma (int a, int b) {
	return a+b;
}

int main (void) {
	int a, b=2, c=4;
	printf("\n\nTestando assembly: \n\n");
	a = assemblyFoo(b,c);
	printf ("Desejado: %d, \tobtido: %d\n\n", soma(b,c), a);
	return 0;
}
