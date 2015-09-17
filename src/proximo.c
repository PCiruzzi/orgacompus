#include "proximo.h"

unsigned char proximo(unsigned char *a, unsigned int i, unsigned int j, unsigned char regla, unsigned int N){

  unsigned char izq,der,actual;
  if (j== 0)
    izq = *(a+N*i+ (N-1));
  else
    izq = *(a+N*i+ (j-1) );
  if (j == (N-1))
    der = *(a+N*i);
  else
    der = *(a+N*i+ (j+1) );
  actual = *(a+N*i+j);
  unsigned char pos = 4*izq + 2*actual + der;
  if ((regla) & (1<<(pos)))
    return 1;
  return 0;
  
}