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
	void *p;
	float f;
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
	cod[i++] = 0x53;	// push	%ebx
	return i;
}

int carrega_fim (unsigned char cod[], int tam) {
	cod[tam++] = 0x5b;	// pop	%ebx
	cod[tam++] = 0x89;	// mov	%ebp, %esp
	cod[tam++] = 0xec;
	cod[tam++] = 0x5d;	// pop	%ebp
	cod[tam++] = 0xc3;	// ret
	return tam;
}

void libera_func (void* func) {
	free (func);
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

// retorna a posição relativa de uma 'variavel' passada pela pilha , em bytes (é a distancia ate ebp na memoria)
int distance_from_ebp (DescParam params[], int index) {
	int i;
	int distance = 8; // o primeiro sempre começa no 8
	for (i=(index-1); i>=0; i--) { // anda ao contrario pq a pilha empilha os ultimos por baixo
		if (params[i].orig_val == PARAM) { // só incrementa se houver parametros passados
			distance += (params[i].tipo_val == DOUBLE_PAR)? 8:4;
		}
	}
	return distance;
}

// printa uma tabela util para os testes da funcao acima
void print_table_distance_from_ebp(DescParam params[], int  n) {
	int param_index;
	for (param_index=(n-1); param_index>=0; param_index--) {
		printf ("\nindice = %d\t| distance = %d\t| %s",
			param_index, 
			distance_from_ebp(params, param_index),
			(params[param_index].orig_val == PARAM)? 
			(params[param_index].tipo_val == DOUBLE_PAR)?
			"PARAM 8 BYTES":"PARAM 4 BYTES"
			:"-"
		);
	}
	printf ("\n\n");
}

// calcula qual o tamanho da pilha de variaveis
int altura_pilha_bytes (DescParam params[], int size_of_param_vector) {
	int cont=0;
	int i=0;
	for (i=0; i<size_of_param_vector; i++) {
		if (params[i].orig_val == PARAM) { // só incrementa se houver parametros de indice maior
			cont += (params[i].tipo_val == DOUBLE_PAR)? 8:4;
		}
	}
	return cont;
}

// calcula o tamanho minimo necessario para gerar o vetor de codigo
int calcula_tamanho_vetor_codigo (DescParam params[], int size_of_param_vector) {
	TipoValor tipo;
	OrigemValor origem;
	int cont = 4+5+7+6; // começo + fim + call + addl
	int i;
	for (i=0; i<size_of_param_vector; i++) {
		tipo = params[i].tipo_val;
		origem = params[i].orig_val;
		if (origem == FIX_DIR)
			cont += (tipo == DOUBLE_PAR) ? 13 : 5;
		else if (origem == PARAM)
			cont += (tipo == DOUBLE_PAR) ? 06 : 3;
		else
			cont += (tipo == DOUBLE_PAR) ? 10 : 7;
	}
	return cont;
}

void* cria_func (void* f, DescParam params[], int n) {
	unsigned char *codigo;
	int tam=0;	// representa o primeiro indice vazio do vetor
	int param_index;
	int vector_size;
	TipoValor tipo;
	OrigemValor origem;
	
	vector_size = calcula_tamanho_vetor_codigo (params, n);

	// aloca a variavel e carrega os primeiros comandos de pilha
	codigo = (unsigned char*) malloc (vector_size * sizeof(char));

	print_table_distance_from_ebp(params, n);
	
	// 4
	tam = carrega_comeco (codigo);
	
	// looping principal, percorre o vetor de parametros
	for (param_index=(n-1); param_index>=0; param_index--) {
		// trata os parametros começando pelo ultimo
		tipo = params[param_index].tipo_val;
		origem = params[param_index].orig_val;
		if (origem == FIX_DIR) { // parametro amarrado a constante, 5 + 8 = 13
			if (tipo==DOUBLE_PAR) { // 8
				// push da segunda metade da union valor
				// bb ea 00 00 00	mov    $0xea, %ebx
				codigo[tam++] = 0xbb;
				tam = add_int(codigo, tam, (int)(&params[param_index].valor) );
				// ff 73 04		pushl  0x4(%ebx)
				codigo[tam++] = 0xff;
				codigo[tam++] = 0x73;
				codigo[tam++] = 0x04;
			}
			// push de 16 ou 32 é 0x68
			codigo[tam++] = 0x68;
			tam = add_int (codigo, tam, params[param_index].valor.v_int);
		} else if (origem == PARAM) { // parametro nao amarrado a nada, 3 + 3 = 6
			if (tipo==DOUBLE_PAR) { // 3
				// ff 75 08	pushl  0x8(%ebp)
				codigo[tam++] = 0xff;
				codigo[tam++] = 0x75;
				codigo[tam++] = 4 + distance_from_ebp(params, param_index);
			}
			// ff 75 08	pushl  0x8(%ebp)
			codigo[tam++] = 0xff;
			codigo[tam++] = 0x75;
			codigo[tam++] = distance_from_ebp(params, param_index);
		} else if (origem == FIX_IND) { // parametro amarrado a variavel, 7 + 3 = 10
			// bb ea 00 00 00	mov    $0xea, %ebx
			codigo[tam++] = 0xbb;
			tam = add_int(codigo, tam, params[param_index].valor.v_int);
			
			if (tipo == DOUBLE_PAR) { // 3
				// empurra a segunda metade da union valor
				// ff 73 04		pushl  0x4(%ebx)
				codigo[tam++] = 0xff;
				codigo[tam++] = 0x73;
				codigo[tam++] = 0x04;
			}
			
			// ff 33		pushl  (%ebx)
			codigo[tam++] = 0xff;
			codigo[tam++] = 0x33;
		}
		
	}
	
	// faz o call, 7
	// 0xb8 é movl para %eax
	codigo[tam++] = 0xb8;
	// insere o endereco de f
	tam = add_int (codigo, tam, (int)f);
	// ff d0	call   *%eax
	codigo[tam++] = 0xff;
	codigo[tam++] = 0xd0;
	
	// faz o addl para 'apagar' os parametros da pilha, 6
	// 81 c4 b6 01 00 00       add    $0x1b6,%esp
	codigo[tam++] = 0x81;
	codigo[tam++] = 0xc4;
	tam = add_int(codigo, tam, altura_pilha_bytes (params, n));
	
	// 5
	tam = carrega_fim (codigo, tam);
	printa_vetor_char_hexa(codigo, tam);
	printf("\n\ntam = %d, vector_size = %d\n\n", tam, vector_size);
	return codigo;
}

