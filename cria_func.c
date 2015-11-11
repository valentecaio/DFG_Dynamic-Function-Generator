// TESTANDO MODIFICAÇÃO
/*
a versão inicial vai apenas empilhar os parametros passados
e fazer o call da função passada
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cria_func.h"

void printa_vetor_char_hexa (unsigned char *v, int n) {
	int i;
	printf ("\nEntradas do vetor: {");
	for (i=0; i<(n-1); i++) {
		printf ("%x, ", v[i]);
	}
	if (i<n) {
		printf ("%x}", v[i]);
	}
	if (i==0) {
		printf ("vetor vazio!");
	}
	printf ("\n\n");
}

int carrega_comeco (unsigned char* cod) {
	int i=0;
	cod[i] = 0x55; i++;	// push	%ebp
	cod[i] = 0x89; i++;	// mov	%esp, %ebp
	cod[i] = 0xe5; i++;
	return i;
}

int carrega_fim (unsigned char cod[], int tam) {
	cod[tam] = 0x89; tam++;	// mov	%ebp, %esp
	cod[tam] = 0xec; tam++;
	cod[tam] = 0x5d; tam++;	// pop	%ebp
	cod[tam] = 0xc3; tam++;	// ret
	return tam;
}

void libera_func (void* func) {
	
}

void* cria_func (void* f, DescParam params[], int n) {
	unsigned char *codigo;
	int tam=0;	// representa o primeiro indice vazio do vetor
	if (n==0) {
		printf ("\n\nPrograma abortado! Nenhum parametro foi passado\n\n");
		exit(1);
	}
	codigo = (unsigned char*) malloc (200* sizeof(char*));
	tam = carrega_comeco (codigo);
	
	
	tam = carrega_fim (codigo, tam);
	printa_vetor_char_hexa(codigo, tam);
	return codigo;
}

/*
   0:   55                      push   %ebp
   1:   89 e5                   mov    %esp,%ebp
   3:   8b 45 08                mov    0x8(%ebp),%eax
   6:   ff 75 0c                pushl  0xc(%ebp)
   9:   ff d0                   call   *%eax
   b:   89 ec                   mov    %ebp,%esp
   d:   5d                      pop    %ebp
   e:   c3                      ret    

*/
