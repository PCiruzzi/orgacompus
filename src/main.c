#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

unsigned char proximo(unsigned char *a, unsigned int i, unsigned int j,
                      unsigned char regla, unsigned int N);

int main(int argc, char *argv[]) {

	//TODO: Verificar que haya algo (y que sea correcto) en argv
//	int regla = atoi(argv[1]);
	char *end;
	int regla = strtol(argv[1], &end, 10);
	if (end == argv[1] || *end != '\0' || errno == ERANGE){
		fprintf(stderr, "El numero de regla no es valido. El mismo no contiene un valor numerico o se ha producido un overflow.\n"); //TODO: No se si es por overflow o qué
		return -1;
	}
	if ( (regla < 0 ) || (regla > 255) ){
		fprintf(stderr, "El numero de regla no es valido. Debe ser un valor numerico entre 0 y 255.\n");
		return -1;
	}

//	int N = atoi(argv[2]);
	int N = strtol(argv[2], &end, 10);
	if (end == argv[2] || *end != '\0' || errno == ERANGE){
		fprintf(stderr, "El numero de celdas e iteraciones (\"N\") no es valido. El mismo no contiene un valor numerico o se ha producido un overflow.\n"); //TODO: No se si es por overflow o qué
		return -1;
	}
	if ( (regla < 0 ) || (regla > 10000) ){
		fprintf(stderr, "El numero de celdas e iteraciones (\"N\") no es valido. Debe ser un valor numerico entre 0 y 10000.\n");
		return -1;
	}

	FILE* entrada = fopen(argv[3], "r");
	if (entrada == NULL){
		fprintf(stderr, "El archivo de entrada especificado no se ha podido abrir o no existe.\n");
		return -1;
	}


	// crear matriz
	unsigned char **matriz;
	matriz = (unsigned char **) malloc(N * sizeof(unsigned char *));
	int i;
	for (i = 0; i < N; i++)
		matriz[i] = (unsigned char *) malloc(N * sizeof(unsigned char));


	//TODO: Ojo con los return -1 porque si pedimos aca arriba memoria no deberiamos liberarla
	//		antes de hacer esos return?

	// cargar primer fila
	i = 0;
	int aux;
	while ((aux = fgetc(entrada)) != EOF) {
		if (aux == '0' || aux == '1'){
			matriz[0][i] = aux - '0';
			fprintf(stdout, "%c", matriz[0][i]);
			fprintf(stdout, "%i\n", aux);
			i++;
		} else {
			if (aux == 10)
					fprintf(stdout, "fin de linea\n");
			else {
				fprintf(stdout, "%i\n", aux);
				fprintf(stderr, "El formato del archivo de entrada no es correcto.\n");
	//			return -1;
			}
		}
		if (i > N) {
			fprintf(stderr, "La cantidad de columnas en el archivo de entrada es mayor a la longitud indicada por \"N\".\n");
			return -1;
		}
	}
	if (i < N) {
		fprintf (stderr, "La cantidad de columnas en el archivo de entrada es menor a la longitud indicada por \"N\".\n");
		return -1;
	}


	// calcular las demas filas
	fprintf(stdout, "%i\n", aux); // Deberia imprimir -1 ya que seria el EOF
	int j;
	for (i = 0; i < N-1; i++){
		for(j = 0; j < N; j++){
			matriz[i+1][j] = proximo(&matriz[0][0],i,j,regla,N);
		}
	}


	// escribir imagen:
	FILE *salida;
	if ((salida = fopen("salida.pmb", "wb")) == NULL) {
		fprintf(stderr, "Error al crear archivo salida.\n");
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


	return 0;
}


unsigned char proximo(unsigned char *a, unsigned int i, unsigned int j,
                      unsigned char regla, unsigned int N){
	// falta implementar y pasar a assembler
	// pongo que devuelva cualquier cosa para probar
	if ((i+j)%2==0)
		return 1;
	return 0;
}
