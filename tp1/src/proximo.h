#ifndef PROXIMO_H_
#define PROXIMO_H_

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

typedef enum { false, true } bool;

extern unsigned char proximo(unsigned char *a, unsigned int i, unsigned int j, unsigned char regla, unsigned int N);


#endif /* PROXIMO_H_ */

