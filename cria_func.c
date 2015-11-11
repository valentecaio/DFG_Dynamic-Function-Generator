// TESTANDO MODIFICAÇÃO
/*
a versão inicial vai apenas empilhar os parametros passados
e fazer o call da função passada

gcc -Wall -m32 -Wa,--execstack -o teste cria_func.c teste.c -lm
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
	cod[i++] = 0x55;	// push	%ebp
	cod[i++] = 0x89;	// mov	%esp, %ebp
	cod[i++] = 0xe5;
	return i;
}

int carrega_fim (unsigned char cod[], int tam) {
	cod[tam++] = 0x89;	// mov	%ebp, %esp
	cod[tam++] = 0xec;
	cod[tam++] = 0x5d;	// pop	%ebp
	cod[tam++] = 0xc3;	// ret
	return tam;
}

void libera_func (void* func) {
	
}

void* cria_func (void* f, DescParam params[], int n) {
	unsigned char *codigo;
	int tam=0;	// representa o primeiro indice vazio do vetor
	unsigned int callFunction;
	int i=0;
	
	if (n==0) {
		printf ("\n\nPrograma abortado! Nenhum parametro foi passado\n\n");
		exit(1);
	}
	codigo = (unsigned char*) malloc (200 * sizeof(char));
	tam = carrega_comeco (codigo);
	
	// trata o primeiro parametro
	if (params[0].orig_val == FIX_DIR) {
		if (params[0].tipo_val == INT_PAR) {
			codigo[tam++] = 0x6a;
			codigo[tam++] = params[0].valor.v_int;
		}
	}

	// trata o segundo parametro
	if (params[1].orig_val == FIX_DIR) {
		if (params[1].tipo_val == INT_PAR) {
			codigo[tam++] = 0x6a;
			codigo[tam++] = params[1].valor.v_int;
		}
	}
	
	// faz o call
	// b8 56 34 12 00          mov    $0x123456,%eax
	codigo[tam++] = 0xb8;
	
	// insere o codigo de f
	callFunction = (unsigned int) f;
	for (i=0; i<=3; i++) {
		codigo[tam++] = (callFunction >> (i*8)); // tem uma mascara &0xff implicita
	}
	
	// ff d0	call   *%eax
	codigo[tam++] = 0xff;
	codigo[tam++] = 0xd0;
	
	printf ("\n\n%d\n\n", callFunction);
	
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



			/*
			// ff 75 0c	pushl  16(%ebp)
			codigo[tam++] = 0xff;
			codigo[tam++] = 0x75;
			codigo[tam++] = 0x0c;
			
			// ff 75 08	pushl  8(%ebp)
			codigo[tam++] = 0xff;
			codigo[tam++] = 0x75;
			codigo[tam++] = 0x08;
			
			// e8 fc ff ff ff	call   a <assemblyFoo+0xa>
			codigo[tam++] = 0xe8;
			codigo[tam++] = 0xfc;
			codigo[tam++] = 0xff;
			codigo[tam++] = 0xff;
			codigo[tam++] = 0xff;
			*/
			
			// 6a 04	push   $4