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

typedef union {
	int i;
	char c[4];
} U;

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

// TODO
void libera_func (void* func) {
	
}

// adiciona os 4 bytes de um inteiro no vetor de codigo
int add_int (unsigned char *codigo, int tam, int x) {
	U u;
	int i;
	u.i = x;
	for (i=0; i<4; i++) {
		codigo[tam++] = u.c[i];
	}
	return tam;
}

// retorna a posição relativa de uma 'variavel' passada a partir de ebp, em bytes
int distance_from_ebp (DescParam params[], int index) {
	int distance;
	int i;
	distance = 4; // sempre tem os 4 bytes do endereco de retorno
	for (i=(index-1); i>=0; i--) { // anda ao contrario pq a pilha empilha os ultimos por baixo
		if (params[i].tipo_val == DOUBLE_PAR) {
			distance += 8;
		} else { // INT_PAR || FLOAT_PAR || PTR_PAR
			distance += 4;
		}
	}
	return distance;
}

void* cria_func (void* f, DescParam params[], int n) {
	unsigned char *codigo;
	int tam=0;	// representa o primeiro indice vazio do vetor
	int j;
	
	if (n==0) {
		printf ("\n\nPrograma abortado! Nenhum parametro foi passado\n\n");
		exit(1);
	}
	
	// aloca a variavel e carrega os primeiros comandos de pilha
	codigo = (unsigned char*) malloc (200 * sizeof(char));
	tam = carrega_comeco (codigo);
	
	// looping principal, percorre o vetor de parametros
	for (j=n; j>=0; j--) { 
		// trata os parametros começando pelo ultimo
		
		
		if (params[j].tipo_val == INT_PAR) { // inteiros
			
			if (params[j].orig_val == FIX_DIR) { // parametro amarrado a constante
				// push de 8 bits é 0x6a (nao é o que vamos usar)
				// push de 16 ou 32 é 0x68
				codigo[tam++] = 0x68;
				tam = add_int (codigo, tam, params[j].valor.v_int);
			} else if (params[j].orig_val == PARAM) { // parametro nao amarrado a nada
				// ff 75 08	pushl  0x8(%ebp)
				codigo[tam++] = 0xff;
				codigo[tam++] = 0x75;
				codigo[tam++] = distance_from_ebp(params, j);
			} else { // parametro amarrado a variavel
				
				
			}
		}
	}
	
	// faz o call
	
	// oxb8 é movl para %eax
	codigo[tam++] = 0xb8;
	
	// insere o endereco de f
	tam = add_int (codigo, tam, (int)f);
	
	// ff d0	call   *%eax
	codigo[tam++] = 0xff;
	codigo[tam++] = 0xd0;
	
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