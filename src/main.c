#include "proximo.h"

bool verificarOpcion(char* argv1) {
	//Chequear que sea -V o --version, o bien, -h o --help
	if ( strcmp(argv1, "-V") == 0 || strcmp(argv1,"--version") == 0 )
    fprintf(stdout, "autcel: version 1.0\n");
	else if ( strcmp(argv1,"-h") == 0 || strcmp(argv1,"--help") == 0 )
		fprintf(stdout, "Uso:\nautcel -h\nautcel -V\nautcel R N inputfile [-o outputprefix]\n\nOpciones:\n-h, --help\tImprime este mensaje.\n-V, --version\tDa la version del programa.\n-o\t\tPrefijo de los archivos de salida.\n\nEjemplo:\nautcel 30 80 inicial -o evolucion\nCalcula la evolucion del automata \"Regla 30\", en un mundo unidimensional de 80 celdas, por 80 iteraciones.\nEl archivo de salida se llamara evolucion.pbm.\nSi no se da un prefijo para los archivos de salida, el prefijo sera el nombre del archivo de entrada.\n");
	else
    fprintf(stderr, "El comando ejecutado no respeta la sintaxis. Para mas ayuda ejecutar el programa con -h o --help.\n");
	return false;
}

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
  if ((N < 1) || (N > 10000)) {
    fprintf(stderr, "El numero de celdas e iteraciones (\"N\") no es valido. Debe ser un valor numerico entre 1 y 10000.\n");
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

bool verificarParametros(int argc, char* argv[], int* regla, int* N, FILE** entrada, char **salida) {
	//Recordar que argv tiene uno mas que los parametros que vienen de consola
	if (argc == 2)
    return verificarOpcion(argv[1]);
	else if (argc == 4 || argc == 6) {
		*regla = verificarRegla(argv[1]);
	  if (*regla == -1) return false;

	  *N = verificarN(argv[2]);
	  if (*N == -1) return false;

	  *entrada = verificarEntrada(argv[3]);
	  if (*entrada == NULL) return false;

	  if (argc == 6) {
	  	if ( strcmp(argv[4],"-o") != 0 ) {
	  		fprintf(stderr, "El comando ejecutado no respeta la sintaxis. Para mas ayuda ejecutar el programa con -h o --help.\n");
	  		return false;
	  	}
	  	//El nombre del archivo de salida podria ser cualquier cosa, asique no verifico nada.
	  	*salida = argv[5];
	  } else //El nombre de la salida es el nombre de la entrada. Luego se le agregara la extension .pbm
		  *salida = argv[3];
	} else {
    fprintf(stderr, "El comando ejecutado no respeta la sintaxis. Para mas ayuda ejecutar el programa con -h o --help.\n");
    return false;
  }
	return true;
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
      i++;
    } else {
      if (aux != 10) {
        fprintf(stderr, "El formato del archivo de entrada no es correcto.\n");
        *continuar = false;
      } // else fprintf(stdout, "fin de linea\n");
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

FILE* escribirImagen(bool continuar, int N, unsigned char (*matriz)[N], char** nombreSalida, bool* seAbrioArchSalida) {
  int i;
  int j;
  FILE* salida;
  strcat(*nombreSalida, ".pmb");

  if ( (continuar == true) && ((salida = fopen(*nombreSalida, "wb")) == NULL) ) {
    fprintf(stderr, "Error al crear archivo salida.\n");
    continuar = false;
  }
  if (continuar == true) {
    *seAbrioArchSalida = true;
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

void liberarMemoriaYCerrarArchivos(int N, unsigned char (*matriz)[N], FILE* entrada, FILE* salida, bool seAbrioArchSalida) {
  free(matriz);
  fclose(entrada);
  if (seAbrioArchSalida == true) fclose(salida);
}

int main(int argc, char *argv[]) {
  // En toda esta primera parte donde todavia no se pidio memoria dejo los return -1 que es mas comodo.
  int regla;
  int N;
  FILE* entrada;
  char* nombreSalida;

  if ( verificarParametros(argc, argv, &regla, &N, &entrada, &nombreSalida) == false ) return -1;

  bool continuar = true;

  unsigned char (*matriz)[N] = malloc(sizeof *matriz * N);
  if (!matriz)
    continuar = false;

  if (continuar == true) fprintf(stdout, "Leyendo estado inicial...\n");
  cargarPrimeraFila(N, &continuar, entrada, matriz);

  if (continuar == true)  fprintf(stdout, "Calculando los %i estados siguientes...\n", N-1);
  calcularFilas(continuar, N, regla, matriz);

  if (continuar == true) fprintf(stdout, "Grabando %s.pbm\n", nombreSalida);
  bool seAbrioArchSalida = false;
  FILE* salida = escribirImagen(continuar, N, matriz, &nombreSalida, &seAbrioArchSalida);

  liberarMemoriaYCerrarArchivos(N, matriz, entrada, salida, seAbrioArchSalida);

  if (continuar == true) fprintf(stdout, "Listo.\n");
  return 0;
}
