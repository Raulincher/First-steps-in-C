/***********************************************
*
* @Proposito: tratamiento de ficheros binarios y de texto
* @Autor/es: Raúl Luque Sanmartín
* @Fecha creacion: 05 / 03 / 2021
* @Fecha ultima modificacion: 07 / 03 / 2021
*
************************************************/

//declaracion de librerias
#include <stdio.h>
#include <string.h>

//declaracion de defines
#define MAX 30 //maximo de caractertes para un array
#define MAX_ACTORS 25 //maximo de actores que se cargan simultaneamente
#define MAX_COSTUME_SIZE_STRING_LENGTH 3 //maximo de letras que puede contener una talla de difraz
#define MAX_EMAIL_STRING_LENGTH 30 //maximo de caracteres que contiene un email
#define MAX_PHONE_STRING_LENGTH 15 //maximo de caracteres que contiene un numero de telefono
#define MAX_ACTOR_NAME_STRING_LENGTH 30 //maximo de caracteres que contienen el nombre de un actor
#define MAX_COSTUMES 15 //maximo de disfraces que se cargan simultaneamente
#define MAX_SEARCH 100 //maximo de busquedas que se cargan simultaneamente


//declaracion de tipos propios

//array de caracteres que contie la talla que usa el actor
typedef char CostumeSize[MAX_COSTUME_SIZE_STRING_LENGTH];

//estructura que contiene la informacion de contacto de un actor
typedef struct {
	char email[MAX_EMAIL_STRING_LENGTH];
	char phone[MAX_PHONE_STRING_LENGTH];
} ContactInformation;

//estructura que contiene la informacion de un actor
typedef struct {
	char name[MAX_ACTOR_NAME_STRING_LENGTH];
	int age;
	int height;
	CostumeSize costume_size;
	ContactInformation contact_information;
} Actor;

//estructura que contiene la informacion de un disfraz
typedef struct {
	int ID;
	char cat;
	int weight;
	char size[MAX_COSTUME_SIZE_STRING_LENGTH];
} Costumes;

//estructura que contiene la informacion de una busqueda
typedef struct {
	char search_name[MAX_ACTOR_NAME_STRING_LENGTH];
	char search_cat;
}Search;

//funciones y procedimientos

/***********************************************
*
* @Finalidad: Función de printado de menú
* @Parametros: ---
* @Retorno: ---
*
************************************************/

void printaMenu() {

	printf("\nChoose action from: actors | costumes | search | exit\n");
	printf("Action: ");
}

/***********************************************
*
* @Finalidad: Comprobación de errores a la hora de escoger una opción del menu
* @Parametros: in/out opt[] = pasamos una cadena para comprobar si coincide con alguna opcion del menú
* @Retorno: ---
*
************************************************/

void ComprobarOpt(char opt[MAX]) {

	char trash;

	while ((strcmp(opt, "actors") != 0) && (strcmp(opt, "costumes") != 0) && (strcmp(opt, "search") != 0) && (strcmp(opt, "exit") != 0)) {

		printf("\nERROR: Wrong action\n\n");

		printf("Choose action from: actors | costumes | search | exit\n");
		printf("Action: ");


		scanf("%s", opt);
		scanf("%c", &trash);

	}
}


/***********************************************
*
* @Finalidad: Función que nos permite comprobar si los actores que contiene el fichero tienen mal escrito el email
* @Parametros:   in: Actor actor[] = variable que me coge mi array de structs previamente llenado del tipo Actor
*				 in: ContactInformation info[] = variable que me coge mi array de structs previamente llenado del tipo ContactInformation
*				 in: j = variable que me guarda mi posicion actual de actores
* @Retorno: flag = una variable que comprueba si ha habido fallos con el actor
*
************************************************/

int compruebaArroba(Actor actor[MAX_ACTORS], ContactInformation info[MAX_ACTORS], int j) {

	int i = 0, flag = 1;

	while (actor[j].contact_information.email[i] != '\0') {

		if (actor[j].contact_information.email[i] == '@') {

			flag = 0;

		}
		i++;
	}

	return(flag);
}

/***********************************************
*
* @Finalidad: Función que nos permite comprobar si los actores que contiene el fichero tienen mal escrito el telefono movil
* @Parametros:  in: Actor actor[] = variable que me coge mi array de structs previamente llenado del tipo Actor
*				in: ContactInformation info[] = variable que me coge mi array de structs previamente llenado del tipo ContactInformation
*				in: j = variable que me guarda mi posicion actual de actores
* @Retorno: flag = una variable que comprueba si ha habido fallos con el numero de telefono
*
************************************************/

int compruebaNumero(Actor actor[MAX_ACTORS], ContactInformation info[MAX_ACTORS], int j) {

	int i = 0, flag = 1, flag_numeros = 1, flag_cantidad = 0;

	while (actor[j].contact_information.phone[i] != '\0') {

		if (actor[j].contact_information.phone[i] < '0' || actor[j].contact_information.phone[i] > '9') {

			flag_numeros = 0;
		}
		i++;

	}

	if (i == 9) {

		flag_cantidad = 1;
	}

	if (flag_numeros == 1 && flag_cantidad == 1) {

		flag = 0;
	}

	return(flag);


}


/***********************************************
*
* @Finalidad: Función que nos permite cargar el fichero de actores
* @Parametros:  in: flag_opt1 = variable que se activara cuando esta función se haya completado safisfactoriamente
*				in / out: Actor actor[] = variable que me coge mi array de structs del tipo Actor el cual llenaremos y devolveremos
*				in / out: ContactInformation info[] = variable que me coge mi array de structs del tipo ContactInformation el cual llenaremos y devolveremos
				in / out: CostumeSize size[] = variable que me coge mi array de structs del tipo CostumesSize el cual llenaremos y devolveremos
* @Retorno: flag_opt1 = variable que se activara cuando esta función se haya completado safisfactoriamente
*
************************************************/

int cargaActors(int flag_opt1, Actor actor[MAX_ACTORS], ContactInformation info[MAX_ACTORS], CostumeSize size[MAX_ACTORS]) {

	FILE* fp;
	char fichero_actors[MAX], trash;
	int i = 0, j = 0;

	printf("\nType the name of the file: ");
	scanf("%s", fichero_actors);
	scanf("%c", &trash);


	fp = fopen(fichero_actors, "rb");
	if (fp == NULL) {

		printf("ERROR: Can't open file '%s'\n", fichero_actors);

	}
	else {

		printf("File loaded with the following actors\n\n");

		fread(&actor[i], sizeof(Actor), 1, fp);

		while (!feof(fp)) {

			i++;

			fread(&actor[i], sizeof(Actor), 1, fp);
		}
		while (j < i) {

			if ((compruebaArroba(actor, info, j) == 0) && (compruebaNumero(actor, info, j) == 0)) {
				printf("<%s>-", actor[j].name);
				printf("<%d>-", actor[j].age);
				printf("<%s>-", actor[j].costume_size);
				printf("<%s>\n", actor[j].contact_information.email);
			}
			j++;
		}

		flag_opt1 = 1;

		fclose(fp);
	}
	return(flag_opt1);
}

/***********************************************
*
* @Finalidad: Función que nos permite cargar el fichero de disfraces
* @Parametros:  in: flag_opt2 = variable que se activara cuando esta función se haya completado safisfactoriamente
*				in / out: Costumes trajes[] = variable que me coge mi array de structs del tipo Costumes el cual llenaremos y devolveremos
* @Retorno: flag_opt2 = variable que se activara cuando esta función se haya completado safisfactoriamente
* 
************************************************/

int cargaCostumes(int flag_opt2, Costumes trajes[MAX_COSTUMES]) {

	FILE* tp;
	char fichero_costumes[MAX], trash;
	int i = 0, j = 0;

	printf("\nType the name of the file: ");
	scanf("%s", fichero_costumes);
	scanf("%c", &trash);

	tp = fopen(fichero_costumes, "r");
	if (tp == NULL) {

		printf("ERROR: Can't open file '%s'\n", fichero_costumes);

	}
	else {

		printf("File loaded with the following costumes\n\n");

		while (!feof(tp)) {
			fscanf(tp, "%c", &trash);

			fscanf(tp, "%d", &trajes[i].ID);

			fscanf(tp, "%c", &trash);

			fscanf(tp, "%c", &trash);

			fscanf(tp, "%c", &trash);

			fscanf(tp, "%c", &trajes[i].cat);

			fscanf(tp, "%c", &trash);

			fscanf(tp, "%c", &trash);

			fscanf(tp, "%c", &trash);

			fscanf(tp, "%d", &trajes[i].weight);

			fscanf(tp, "%c", &trash);

			fscanf(tp, "%c", &trash);

			fscanf(tp, "%c", &trash);

			fscanf(tp, "%s", trajes[i].size);

			fscanf(tp, "%c", &trash);

			i++;
		}


		while (j < i) {

			if (trajes[j].cat >= 'a' && trajes[j].cat <= 'j') {

				printf("<%d>-", trajes[j].ID);
				printf("<%c>-", trajes[j].cat);
				printf("<%d>-", trajes[j].weight);
				printf("<%s>\n", trajes[j].size);

			}
			j++;
		}

		flag_opt2 = 1;

		fclose(tp);
	}

	return(flag_opt2);
}


/***********************************************
*
* @Finalidad: Función de busqueda a partir de un fichero. Aqui usaremos los dos ficheros previamente cargados para buscar un disfraz adecuado a cada actor
* @Parametros:  in / out: busqueda[] = cargaremos el archivo de texto de busqueda y lo guardaremos en esta estructura del tipo Search
*				in : actor[] = Leeremos el tipo propio de actor previamente cargado para ver si coincide con nuestro archivo de busqueda
*				in : info[] = Leeremos el tipo propio de ContactInformation previamente cargado para ver si coincide con nuestro archivo de busqueda
*				in : size[] = Leeremos el tipo propio de CostumeSize previamente cargado para ver si coincide con nuestro archivo de busqueda
*				in : trajes[] = Leeremos el tipo propio de Costumes previamente cargado para ver si coincide con nuestro archivo de busqueda
*				in : flag_opt1 = variable auxiliar que nos permite ver si se ha completado la opción 1 satisfactoriamente
*				in : flag_opt2 = variable auxiliar que nos permite ver si se ha completado la opción 2 satisfactoriamente
* @Retorno: nada
*
************************************************/

void buscaCostumes(int flag_opt1, int flag_opt2, Search busqueda[MAX_ACTORS], Actor actor[MAX_ACTORS], ContactInformation info[MAX_ACTORS], CostumeSize size[MAX_ACTORS], Costumes trajes[MAX_COSTUMES]) {

	FILE* sp;
	char fichero_busqueda[MAX], trash;
	int i = 0, j = 0, c = 0, actor_found = 0, z = 0, dress_counter = 0;


	if (flag_opt1 != 0 && flag_opt2 != 0) {

		printf("\nType the name of the file: ");
		scanf("%s", fichero_busqueda);
		scanf("%c", &trash);
		sp = fopen(fichero_busqueda, "r");
		if (sp == NULL) {

			printf("ERROR: Can't open file '%s'\n", fichero_busqueda);

		}
		else {

			fscanf(sp, "%c", &busqueda[i].search_cat);

			fscanf(sp, "%c", &trash);

			fscanf(sp, "%c", &trash);

			fscanf(sp, "%c", &trash);

			fgets(busqueda[i].search_name, MAX_ACTOR_NAME_STRING_LENGTH, sp);

			while (!feof(sp)) {
				i++;

				fscanf(sp, "%c", &busqueda[i].search_cat);

				fscanf(sp, "%c", &trash);

				fscanf(sp, "%c", &trash);

				fscanf(sp, "%c", &trash);

				fgets(busqueda[i].search_name, MAX_ACTOR_NAME_STRING_LENGTH, sp);

			}

			while (j < i) {
				busqueda[j].search_name[strlen(busqueda[j].search_name) - 1] = '\0';
				j++;
			}

			j = 0;

			while (j < i) {

				c = 0;
				dress_counter = 0;
				actor_found = 0;
				z = 0;

				while (actor_found == 0 && z < MAX_ACTORS) {

					if (strcmp(busqueda[j].search_name, actor[z].name) == 0) {

						if ((compruebaArroba(actor, info, z) == 0) && (compruebaNumero(actor, info, z) == 0)) {

							actor_found = 1;
						}
						else {

							z++;
						}
					}
					else {

						z++;
					}
				}

				if (actor_found == 1) {

					printf("\nActor/Actress: %s\n", busqueda[j].search_name);
				}
				else {
					printf("\nActor/Actress %s not found\n", busqueda[j].search_name);

				}

				//c = encuentraOrden(j, busqueda, actor);

				while (c < MAX_COSTUMES && actor_found == 1) {

					if (busqueda[j].search_cat == trajes[c].cat) {

						if ((trajes[c].cat >= 'a') && (trajes[c].cat <= 'j') && (strcmp(trajes[c].size, actor[z].costume_size) == 0)) {

							dress_counter++;
						}

					}

					c++;

				}

				if (actor_found == 1) {
					printf("%d dresses found for dress category %c\n", dress_counter, busqueda[j].search_cat);
				}

				j++;
			}

			fclose(sp);
		}

	}
	else {
		printf("\nERROR: Either actors or costumes are not loaded\n");
	}

}

/***********************************************
*
* @Finalidad: Función de despedida
* @Parametros: nada
* @Retorno: nada
*
************************************************/

void exitProgram() {

	printf("\nBye!");

}

//int main

int main() {

	//declaración de variables
	char opt[MAX], trash;
	int flag_opt1 = 0, flag_opt2 = 0;
	Actor actor[MAX_ACTORS];
	ContactInformation info[MAX_ACTORS];
	CostumeSize size[MAX_ACTORS];
	Costumes trajes[MAX_COSTUMES];
	Search busqueda[MAX_SEARCH];

	printf("Welcome!\n");

	do {

		// llamada al procedimiento de printado de menu
		printaMenu();

		scanf("%s", opt);
		scanf("%c", &trash);

		// llamada al procedimiento de comprobación de opción de menu
		ComprobarOpt(opt);

		if (strcmp(opt, "actors") == 0 && flag_opt1 == 0) {

			//llamada a la funcion de carga de actores
			flag_opt1 = cargaActors(flag_opt1, actor, info, size);
		}
		else {

			if (strcmp(opt, "actors") == 0 && flag_opt1 == 1) {
				printf("\nAction already done\n");
			}
		}

		if (strcmp(opt, "costumes") == 0 && flag_opt2 == 0) {

			//llamada a la funcion de carga de disfraces
			flag_opt2 = cargaCostumes(flag_opt2, trajes);
		}
		else {

			if (strcmp(opt, "costumes") == 0 && flag_opt2 == 1) {

				printf("\nAction already done\n");

			}

		}

		if (strcmp(opt, "search") == 0) {

			////llamada al procedimiento de busqueda
			buscaCostumes(flag_opt2, flag_opt1, busqueda, actor, info, size, trajes);
		}

	} while ((strcmp(opt, "exit") != 0));



	if (strcmp(opt, "exit") == 0) {

		//llamada al procedimiento de despedida
		exitProgram();
	}

	return (0);
}


