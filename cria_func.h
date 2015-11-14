#ifndef CRIA_FUNC_H
#define CRIA_FUNC_H

typedef enum {INT_PAR, FLOAT_PAR, DOUBLE_PAR, PTR_PAR} TipoValor;
typedef enum {PARAM, FIX_DIR, FIX_IND} OrigemValor;

typedef struct {
   TipoValor    tipo_val;  /* indica o tipo do parametro */
   OrigemValor  orig_val;  /* indica a origem do valor do parametro */
   union {
     int v_int;
     float v_float;
     double v_double;
     void* v_ptr;
   } valor;         /* define o valor/endereco do valor do parametro */
} DescParam;

void print_end (void *x, char *name);
void* cria_func (void* f, DescParam params[], int n);
void libera_func (void* func);

#endif