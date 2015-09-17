#include "proximo.h"

int verificarRegla(char* argv1) {
  char* end;
  int regla = strtol(argv1, &end, 10);
  if (end == argv1 || *end != '\0' || errno == ERANGE) {
    fprintf(stderr, "El numero de regla no es valido. El mismo no contiene un valor numerico o se ha producido un overflow.\n"); //TODO: No se si es por overflow o qué
    return -1;
  }
  if ((regla < 0) || (regla > 255)) {
    fprintf(stderr, "El numero de regla no es valido. Debe ser un valor numerico entre 0 y 255.\n");
    return -1;
  }
  return regla;
}

int verificarN(char* argv2) {
  char* end;
  int N = strtol(argv2, &end, 10);
  if (end == argv2 || *end != '\0' || errno == ERANGE) {
    fprintf(stderr, "El numero de celdas e iteraciones (\"N\") no es valido. El mismo no contiene un valor numerico o se ha producido un overflow.\n"); //TODO: No se si es por overflow o qué
    return -1;
  }
  if ((N < 0) || (N > 10000)) {
    fprintf(stderr, "El numero de celdas e iteraciones (\"N\") no es valido. Debe ser un valor numerico entre 0 y 10000.\n");
    return -1;
  }
  return N;
}

FILE* verificarEntrada(char* argv3) {
  FILE* entrada = fopen(argv3, "r");
  if (entrada == NULL)
    fprintf(stderr, "El archivo de entrada especificado no se ha podido abrir o no existe.\n");
  return entrada;
}

unsigned char** crearMatriz(int N) {
  unsigned char** matriz;
  matriz = (unsigned char**) malloc(N * sizeof(unsigned char*));
  int i;
  for (i = 0; i < N; i++)
    matriz[i] = (unsigned char*) malloc(N * sizeof(unsigned char));
  return matriz;
}

void cargarPrimeraFila(int N, bool* continuar, FILE* entrada, unsigned char (*matriz)[N]) {
  int i = 0;
  int aux;
  while ((*continuar == true) && ((aux = fgetc(entrada)) != EOF)) {
    if (aux == '0' || aux == '1') {
      matriz[0][i] = aux - '0';
      //fprintf(stdout, "%c", matriz[0][i]);
      //fprintf(stdout, "%i\n", aux);
      i++;
    } else {
      if (aux != 10){
        //fprintf(stdout, "%i\n", aux);
        fprintf(stderr, "El formato del archivo de entrada no es correcto.\n");
        *continuar = false;
      } else fprintf(stdout, "fin de linea\n");
    }
    if (i > N) {
      fprintf(stderr, "La cantidad de columnas en el archivo de entrada es mayor a la longitud indicada por \"N\".\n");
      *continuar = false;
    }
  }
  if ((*continuar == true) && (i < N)) {
    fprintf(stderr, "La cantidad de columnas en el archivo de entrada es menor a la longitud indicada por \"N\".\n");
    *continuar = false;
  }
}

void calcularFilas(bool continuar, int N, int regla, unsigned char(*matriz)[N]) {
  int i;
  int j;
  if (continuar == true) {
    for (i = 0; i < N - 1; i++) {
      for (j = 0; j < N; j++) {
        matriz[i + 1][j] = proximo(&matriz[0][0], i, j, regla, N);
      }
    }
  }
}

FILE* escribirImagen(bool continuar, int N, unsigned char (*matriz)[N]) {
  int i;
  int j;
  FILE* salida;
  // Invierto el orden de los if para que pruebe primero de abrirlo asi despues al cerrarlo no hay segfault
  if (((salida = fopen("salida.pmb", "wb")) == NULL) && (continuar == true)) {
    fprintf(stderr, "Error al crear archivo salida.\n");
    continuar = false;
  }
  if (continuar == true) {
    fprintf(salida, "P1\n%d %d\n", N, N);
    for (i = 0; i < N; i++) {
      for (j = 0; j < N; j++) {
        fprintf(salida, "%d", matriz[i][j]);
      }
      fputc('\n', salida);
    }
  }
  return salida;
}

void liberarMemoriaYCerrarArchivos(int N, unsigned char (*matriz)[N], FILE* entrada, FILE* salida) {
  free(matriz);
  fclose(entrada);
  fclose(salida);
}

int main(int argc, char *argv[]) {
  //TODO: Verificar que haya algo (y que sea correcto) en argv
  // En toda esta primera parte donde todavia no se pidio memoria dejo los return -1 que es mas comodo.
  int regla = verificarRegla(argv[1]);
  if (regla == -1) return -1;

  int N = verificarN(argv[2]);
  if (N == -1) return -1;

  FILE* entrada = verificarEntrada(argv[3]);
  if (entrada == NULL) return -1;

  bool continuar = true;

  unsigned char (*matriz)[N] = malloc(sizeof *matriz * N);
  if (!matriz)
    continuar = false;

  cargarPrimeraFila(N, &continuar, entrada, matriz);

  calcularFilas(continuar, N, regla, matriz);

  FILE* salida = escribirImagen(continuar, N, matriz);

  liberarMemoriaYCerrarArchivos(N, matriz, entrada, salida);

  fprintf(stdout, "The End.\n");
  return 0;
}
