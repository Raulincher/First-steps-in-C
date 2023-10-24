//librerias usadas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//tamaño maximo de las strings
#define MAX_FILENAME 25

//tipo propio struct
typedef struct {
	char name[50];
	int age;
} Musician;	

//tipo propio struct
typedef struct {
	char name[50];
	int cache;
	int num_musicians;
	Musician* musicians;
} Band;

//tipo propio struct
typedef struct {
	char name[50];
	int capacity;
} Venue;

/************************************************
@Finalidad: Abrir un fichero de texto y guardar sus datos en una struct dinámica
 @Parámetros : 
 in : banda = puntero que almacena la info de bandas
 in : numbands = entero que nos dira el numero de bandas existentes
 @Retorno : out : banda = el puntero de banda ya rellenado (en caso de que todo haya ido bien)
************************************************/
Band* InfoBands(Band* banda, int* numbands) {

	FILE* fp;
	int flag = 1, i = 0, j = 0;
	char trash, bandfilename[MAX_FILENAME];

	//bucle que acabará una vez el usuario introduzca un nombre de fichero valido
	while (flag == 1) {

		printf("\n\t- Bands: ");

		//pedimos nombre fichero
		scanf("%s", bandfilename);
		scanf("%c", &trash);

		//abrimos fichero
		fp = fopen(bandfilename, "r");

		//comprobamos si el fichero es correcto
		if (fp == NULL) {

			printf("ERROR: Can't open file '%s'", bandfilename);

		}
		else {

			flag = 0;

			//leemos el numero de bandas
			fscanf(fp, "%d", numbands);

			//Pedimos memoria para las bandas
			banda = (Band*)malloc(sizeof(Band) * (*numbands));

			//si todo ha ido bien procedemos a leer y almacenar datos
			if (banda != NULL) {
				while (i < *numbands) {

					fscanf(fp, "%c", &trash);
					fgets(banda[i].name, 50, fp);

					banda[i].name[strlen(banda[i].name) - 1] = '\0';

					fscanf(fp, "%d", &banda[i].cache);
					fscanf(fp, "%d", &banda[i].num_musicians);

					//Pido memoria para cada los músicos de cada banda
					banda[i].musicians = (Musician*)malloc(sizeof(Musician) * banda[i].num_musicians);

					//Comprobación a la hora de hacer el MALLOC de musicos
					if (banda[i].musicians != NULL) {

						j = 0;

						while (j < banda[i].num_musicians)
						{
							banda[i].musicians[j].age = 0;
							j++;
						}

						i++;
					}//liberamos musicos de esa banda en caso de que haya habido algún error
					else {

						
						free(banda[i].musicians);

					}

				}
				
			}//liberamos memoria de banda en caso de que algo hay ido mal
			else {
				free(banda);

			}
			//cerramos fichero de bandas
			fclose(fp);
		}
	}

	// devolvemos banda ya rellenado, en caso de que todo haya ido bien
	return(banda);
}


/************************************************
@Finalidad: Abrir un fichero de texto y guardar sus datos en una struct dinámica
 @Parámetros :
 in : escenario = puntero que almacena la info de los escenarios
 in : numvenues = entero que nos dira el numero de escenarios existentes
 @Retorno : out : escenario = el puntero de escenario ya rellenado (en caso de que todo haya ido bien)
************************************************/
Venue* InfoVenues(Venue* escenario, int* numvenues) {
	FILE *fv;
	int flag = 1, i = 0;
	char venuefile[MAX_FILENAME], trash;

	//bucle que acabará una vez el usuario introduzca un nombre de fichero valido
	while (flag == 1) {

		printf("\t- Venues: ");
		
		scanf("%s", venuefile);
		scanf("%c", &trash);

		fv = fopen(venuefile, "r");

		if (fv == NULL) {

			printf("ERROR: Can't open file '%s'\n", venuefile);
		}
		else {
			flag = 0;
			fscanf(fv, "%d", numvenues);
			//pedimos memoria para el numero de escenarios leido
			escenario = (Venue*)malloc(sizeof(Venue) * (*numvenues));

			//si todo ha ido bien leemos la info del fichero
			if (escenario != NULL) {
				while (i < *numvenues) {

					fscanf(fv, "%c", &trash);

					fgets(escenario[i].name, 50, fv);

					escenario[i].name[strlen(escenario[i].name) - 1] = '\0';

					fscanf(fv, "%d", &escenario[i].capacity);

					i++;

				}
			}//si hay algun problema con la petición de memoria el puntero será liberado
			else {

				free(escenario);

			}

			//cerramos fichero
			fclose(fv);
		}


	}

	//devolvemos escenario ya rellenado, en caso de que todo haya ido bien
	return(escenario);
}


/************************************************
@Finalidad: Abrir un fichero de texto y guardar sus datos en una struct dinámica
 @Parámetros :
 in : banda = puntero que almacena la info de las bandas previamente almacenadas
 in : numbands = entero que nos dira el numero de bandas existentes
 @Retorno : out : banda = el puntero de banda modificado con la info de músicos (en caso de que todo haya ido bien)
************************************************/
Band* InfoMusicians(Band *banda, int* numbands) {

	//inicialización de variables
	FILE *mf;
	int flag = 1, num_musicians = 0, i = 0, a = 0, j = 0, ageaux = 0;
	char musicianfile[MAX_FILENAME], trash, auxname[50], bandnameaux[50];

	//bucle que acabará una vez el usuario introduzca un nombre de fichero valido
	while (flag == 1) {

		printf("\t- Musicians: ");

		scanf("%s", musicianfile);
		scanf("%c", &trash);

		mf = fopen(musicianfile, "r");

		if (mf == NULL) {

			printf("ERROR: Can't open file '%s'\n", musicianfile);

		}
		else {
			flag = 0;

			//leemos el numero de musicos
			fscanf(mf, "%d", &num_musicians);

			//lectura de datos via fichero
			while (i < num_musicians) {

				fscanf(mf, "%c", &trash);

				fgets(auxname, 50, mf);

				auxname[strlen(auxname) - 1] = '\0';

				fgets(bandnameaux, 50, mf);

				bandnameaux[strlen(bandnameaux) - 1] = '\0';

				fscanf(mf, "%d", &ageaux);

				j = 0;
				while(j < *numbands) 
				{
					a = 0;
					//comprobamos que la banda sea la misma que la del musico
					if (strcmp(bandnameaux, banda[j].name) == 0) 
					{

						/*en caso de que el fichero no nos ofrezca los musicos de misma banda uno detras de otro hacemos esta comprobacion 
						asi cuando un múscio tenga una edad diferente de 0 sabremos que debemos hacer el recuento a partir de él*/
						while (banda[j].musicians[a].age != 0) {

							a++;
						}
							
						//inserción de datos a nuestra estructura
						strcpy(banda[j].musicians[a].name, auxname);

						banda[j].musicians[a].age = ageaux;

						a++;
						
					}

					j++;
				}

				i++;

			}


			//cerramos fichero
			fclose(mf);
		}

	}

	//devolvemos la info de banda ya modificada
	return(banda);
}


/***********************************************
* @Finalidad: Mostramos las bandas o los escenarios
* @Parametros:	in: banda = puntero a las bandas almacenadas
*				in: escenario = puntero a los escenarios almacenados
*				in: numvenues = número de escenarios
*				in: numbands = número de bandas
* @Retorno: ----
************************************************/

void Opcion1(Band *banda, Venue *escenario, int numbands, int numvenues) {

	int opt = 0, i = 0;

	printf("\n1. Show bands | 2. Show venues\n");
	printf("Select option: ");
	scanf("%d", &opt);

	//comprobación de errores con la opción escogida
	while (opt != 1 && opt != 2) {

		printf("ERROR: Wrong option number\n");

		printf("\n1. Show bands | 2. Show venues\n");
		printf("Select option: ");
		scanf("%d", &opt);
	}

	//mostrar bandas
	if (opt == 1) {

		i = 0;
		printf("\nBands:\n");

		while (i < numbands) {

			printf("\t%d - %s\n",i + 1,banda[i].name);
			i++;
		}
	}
	
	//mostrar escenarios
	if (opt == 2) {

		i = 0;
		printf("\nVenues:\n");


		while (i < numvenues) {

			printf("\t%d - %s\n", i + 1, escenario[i].name);
			i++;

		}
	}
}



/***********************************************
* @Finalidad: Calcular el precio de las entradas de los conciertos
* @Parametros:	in: banda = puntero a las bandas almacenadas
*				in: escenario = puntero a los escenarios almacenados
*				in: numvenues = número de escenarios
*				in: numbands = número de bandas
* @Retorno: ----
************************************************/
void Opcion2(Band *banda, Venue *escenario, int numbands, int numvenues) {

	int band_number = 0, venue_number = 0;
	float result = 0;

	printf("\nSelect band number: ");
	scanf("%d", &band_number);

	while (band_number > numbands || band_number < 1)
	{
		printf("ERROR: Invalid band number\n");

		printf("\nSelect band number: ");
		scanf("%d",&band_number);

	}

	printf("\nSelect venue number: ");
	scanf("%d", &venue_number);

	while (venue_number > numvenues || venue_number < 1) 
	{

		printf("ERROR: Invalid venue number\n");

		printf("\nSelect venue number: ");
		scanf("%d", &venue_number);

	}

	result = (float)banda[band_number - 1].cache / (float)escenario[venue_number - 1].capacity;

	printf("\nThe minimum ticket price is %.2f euros\n", result);
}

/***********************************************
* @Finalidad: Mostramos los musicos de x banda
* @Parametros:	in: banda = puntero a las bandas almacenadas
*				in: numbands = número de bandas
* @Retorno: ----
************************************************/

void Opcion3(Band* banda, int numbands) {

	int band_number = 0, i = 0;

	//pedimos el numero de banda
	printf("\nSelect band number: ");
	scanf("%d", &band_number);

	//comprobamos el numero de banda
	while (band_number > numbands || band_number < 1) 
	{
		printf("ERROR: Invalid band number\n");

		printf("\nSelect band number: ");
		scanf("%d", &band_number);
	}

	//printamos los miembros de la banda x
	printf("\nMembers:\n");

	while(i < banda[band_number - 1].num_musicians)
	{
		printf("\t- %s\n", banda[band_number - 1].musicians[i].name);
		
		i++;
	}

}

/***********************************************
* @Finalidad: Mostrar el menú
* @Parametros: ----
* @Retorno: ----
************************************************/

void PrintaMenu() {

	printf("\n1. Show bands or venues | 2. Calculate ticket price | 3. Show band members | 4. Exit");
	printf("\nSelect option: ");

}


/***********************************************
* @Finalidad: Comprobar si la opción escogida en el menú es válida
* @Parametros:	in: opt = entero que nos dice la opción del menú
* @Retorno: out: opt = opción comprobada
************************************************/
int ComprobarOpt(int opt) {

	//comprobamos que la opción este entre 1 y 4
	while (opt > 4 || opt < 1) {

		printf("ERROR: Wrong option number\n");

		printf("\n1. Show bands or venues | 2. Calculate ticket price | 3. Show band members | 4. Exit");
		printf("\nSelect option: ");
		scanf("%d", &opt);

	}

	return(opt);
}

/***********************************************
* @Finalidad: Juntar i muntar totes les funcions i buscar l'objectiu desitjat
* @Parametros:----
* @Retorno:----
************************************************/
int main() {
	//punteros
	Band *banda;//puntero de banda
	Venue *escenario;//puntero de escenario
	//inicialización de los punteros a nulo
	banda = NULL;
	escenario = NULL;

	//variables de tipo entero
	int i = 0, opt = 0, numbands = 0, numvenues = 0;


	printf("Welcome!\n");

	printf("\nIntroduce the file names:");

	//función de llenado del puntero banda
	banda = InfoBands(banda, &numbands);
	//función de llenado del puntero musicians dentro del puntero banda
	banda = InfoMusicians(banda, &numbands);
	//función de llenado del puntero escenario
	escenario = InfoVenues(escenario, &numvenues);


	do {

		//funcion de printado de menú
		PrintaMenu();
		//pedimos opción al usuario
		scanf("%d", &opt);
		
		//comprobamos la opción dada
		opt = ComprobarOpt(opt);
			
		//diferentes opciones
			switch (opt) {

				case 1:

					//función de la opción 1
					Opcion1(banda, escenario, numbands, numvenues);

					break;

				case 2:

					//función de la opción 2
					Opcion2(banda, escenario, numbands, numvenues);


					break;

				case 3:

					//función de la opción 3
					Opcion3(banda, numbands);

					break;

			}

	} while (opt != 4);

	//despedida
	printf("\nBye!\n");

	i = 0;
	//liberación de memoria
	while(i < numbands)
	{
		free(banda[i].musicians);
		banda[i].musicians = NULL;
		i++;
	}

	free(banda);
	free(escenario);

	banda = NULL;
	escenario = NULL;

	
	return (0);
}