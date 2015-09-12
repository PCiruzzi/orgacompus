#include <stdio.h>
#include <stdlib.h>

unsigned char proximo(unsigned char *a, unsigned int i, unsigned int j,
                      unsigned char regla, unsigned int N);

int main(int argc, char *argv[]) {

  int regla = atoi(argv[1]);
  int N = atoi(argv[2]);
  FILE* entrada = fopen(argv[3], "r");
  int i;

  char **matriz;
  matriz = (char **) malloc(N * sizeof(char *));
  for (i = 0; i < N; i++)
    matriz[i] = (char *) malloc(N * sizeof(char));

  i = 0;
  int aux = fgetc(entrada);
  while (aux != EOF) {
    matriz[i][0] = aux - '0';
    i++;
    aux = fgetc(entrada);
  }

  int j;
  for (i = 0; i < N-1; i++){
    for(j = 0; j < N; j++){
      matriz[i+1][j] = proximo(&matriz[0][0],i,j,regla,N);
    }
  }

  for (i = 0; i < N; i++)
    free(matriz[i]);
  free(matriz);
  fclose(entrada);
}


unsigned char proximo(unsigned char *a, unsigned int i, unsigned int j,
                      unsigned char regla, unsigned int N){

  // falta implementar y pasar a assembler
  // pongo que devuelva cualquier cosa para probar
  if ((i+j)%2==0)
    return 1;
  return 0;
}
