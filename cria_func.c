// TESTANDO MODIFICAÇÃO
/*
a versão inicial vai apenas empilhar os parametros passados
e fazer o call da função passada

mudanca no notebook
*/

#include <stdio.h>
#include <cria_func.h>

typedef enum {INT_PAR, FLOAT_PAR, DOUBLE_PAR, PTR_PAR} TipoValor;
typedef enum {PARAM, FIX_DIR, FIX_IND} OrigemValor;

typedef struct {
   TipoValor    tipo_val;  /* indica o tipo do parametro (inteiro, float, double ou ponteiro) */
   OrigemValor  orig_val;  /* indica a origem do valor do parametro */
   union {
     int v_int;
     float v_float;
     double v_double;
     void* v_ptr;
   } valor;         /* define o valor/endereço do valor do parametro */
} DescParam;

void carrega_comeco (unsigned char* cod) {
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
	unsigned char [200] codigo;
	int tam=0;	// representa o primeiro indice vazio do vetor
	tam = carrega_comeco (codigo);
	
	
	tam = carrega_fim (codigo, tam);
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
