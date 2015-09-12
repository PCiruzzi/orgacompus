#include <stdio.h>
#include <stdlib.h>

unsigned char proximo(unsigned char *a, unsigned int i, unsigned int j,
                      unsigned char regla, unsigned int N);

int main(int argc, char *argv[]) {

  int regla = atoi(argv[1]);
  int N = atoi(argv[2]);
  FILE* entrada = fopen(argv[3], "r");

  // crear matriz y cargar primer fila
  char **matriz;
  matriz = (char **) malloc(N * sizeof(char *));
  int i;
  for (i = 0; i < N; i++)
    matriz[i] = (char *) malloc(N * sizeof(char));
  i = 0;
  int aux = fgetc(entrada);
  while (aux != EOF) {
    matriz[0][i] = aux - '0';
    i++;
    aux = fgetc(entrada);
  }

  // calcular las demas filas
  int j;
  for (i = 0; i < N-1; i++){
    for(j = 0; j < N; j++){
      matriz[i+1][j] = proximo(&matriz[0][0],i,j,regla,N);
    }
  }


  // escribir imagen:
  FILE *salida;
  if ((salida = fopen("salida.pmb", "wb")) == NULL) {
         fprintf(stderr, "error al crear archivo salida");
         return -1;
  }

  fprintf(salida, "P1\n%d %d\n", N, N);
  for (i = 0; i < N; i++){
    for(j = 0; j < N; j++){
      fprintf(salida,"%d",matriz[i][j]);
    }
    fputc('\n',salida);
  }


  //frees y fcloses
  for (i = 0; i < N; i++)
    free(matriz[i]);
  free(matriz);
  fclose(entrada);
  fclose(salida);
}


unsigned char proximo(unsigned char *a, unsigned int i, unsigned int j,
                      unsigned char regla, unsigned int N){

  // falta implementar y pasar a assembler
  // pongo que devuelva cualquier cosa para probar
  if ((i+j)%2==0)
    return 1;
  return 0;
}
