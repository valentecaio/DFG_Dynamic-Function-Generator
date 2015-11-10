#include <math.h>
#include <stdio.h>
#include "cria_func.h"

typedef double (*func_ptr) ();

int main (void) {
  DescParam params[2];
  func_ptr f_potencia = NULL;
  double pot;

  params[0].tipo_val = DOUBLE_PAR;
  params[0].orig_val = FIX_DIR;
  params[0].valor.v_double = 2.0;
  params[1].tipo_val = DOUBLE_PAR;
  params[1].orig_val = FIX_IND;
  params[1].valor.v_ptr = &pot;

  f_potencia = (func_ptr) cria_func (pow, params, 2);
  for (pot = 0.0; pot <=  10.0; pot++) {
     printf("2.0 ^ %2.1f = %4.1f\n", pot, f_potencia());
  }
  libera_func(f_potencia);
  return 0;
}
