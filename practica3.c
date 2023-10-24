/*raul luque sanmartin
fecha de creacion: 19/12/20
ultima modificacion: 22/12/2020
programa que te permitira guardar 10 localizaciones ditintas. Una veza guardadas las podrás ver o dejar que el programa te sugiera alguna de ellas
*/


#include <stdio.h>
#include <string.h>
#include <math.h>


#define MAX_LOCATION 10
#define MAX_CHAR 50
#define MAX_ARRAY 500
#define MAX_AUX 10
#define PI 3.14159

//mi estructura para guardar toda la info de la localizacion//

typedef struct{

	char name[MAX_CHAR];
	char location_type[MAX_CHAR];
	int score;
	float latitude;
	float longitude;
	int opening_hour;
	int close_hour;
	float distance;

}Location;

//procedimiento que me ayuda a printar el menu cada vez que lo necesito//

void printaMenu(){

	printf("\n1. Add location | 2. List locations | 3. Show suggestions | 4. Exit\n");
	printf("Selected action: ");

}

//implementacion de un ATOF//

float myAtof(char cadena_chars[10]){

	
	float number = 0;
	int i = 0, j = 0, aux_punto = 0, flag = 0;

	while(cadena_chars[i] != '\0'){

		
		if(cadena_chars[i] != '.'){
			if(cadena_chars[i] == '-'){

				i++;
				flag = 1;
	
			}else{
				number = (number * 10) + (cadena_chars[i] - '0');

				i++;

			if(aux_punto == 1){

				j--;

			}}

		}else{
			
			aux_punto = 1;

			i++;

		}

	}

	number = number * pow(10,j);

	if(flag == 1){

		number = -number;

	}

	return (number);

}


//implmentacion de un ATOI//

int myAtoi(char cadena_chars[10]){

	int number = 0, i = 0;
	
	for(i = 0; cadena_chars[i] != '\0'; i++ ){

		number = number * 10 + cadena_chars[i] - '0';

	}


	return(number);
}

//funcion que me tocea la cadena introducida y ademas me guarda la info en mi struct//

Location troceaCadenas(char location_array[MAX_ARRAY]){

	int i = 0, j = 0;
	char score_aux[MAX_AUX],latitude_aux[MAX_AUX],longitude_aux[MAX_AUX],opening_hour_aux[MAX_AUX],close_hour_aux[MAX_AUX];
	Location location;


	while(location_array[i] != '\0') {

		while(location_array[i] != '#'){

			location.name[j] = location_array[i];
			i++;
			j++;
		}

		location.name[j] = '\0';

		i++;
		j = 0;

		while(location_array[i] != '#'){

			location.location_type[j] = location_array[i];
			i++;
			j++;
		}

		location.location_type[j] = '\0';

		i++;
		j = 0;

		while(location_array[i] != '#'){

			score_aux[j] = location_array[i];
			i++;
			j++;

		}

		score_aux[j] = '\0';

		location.score = myAtoi(score_aux);

		j = 0;
		i++;
			
		while(location_array[i] != '|'){

			latitude_aux[j] = location_array[i];
			i++;
			j++;

		}
		
		latitude_aux[j] = '\0';

		location.latitude = myAtof(latitude_aux);	

		i++;
		j = 0;

		while(location_array[i] != '#' ){
			
			longitude_aux[j] = location_array[i];
			i++;
			j++;
	
		}

		longitude_aux[j] = '\0';

		location.longitude = myAtof(longitude_aux);

		i++;
		j = 0;

		while(location_array[i] != '-'){

			opening_hour_aux[j] = location_array[i];
			i++;
			j++;

		}

		opening_hour_aux[j] = '\0';

		location.opening_hour = myAtoi(opening_hour_aux);

		i++;
		j = 0;

		while(location_array[i] != '\n'){

			close_hour_aux[j] = location_array[i];
			i++;
			j++;

		}

		close_hour_aux[j] = '\0';

		location.close_hour = myAtoi(close_hour_aux);

		i++;
		j = 0;

	}

	return(location);
}

//funcion auxiliar que me ayuda a identificar errores en los datos//

int localizarError (Location locations[MAX_LOCATION], int location_counter){

	int comprobacion = 0;


	if((locations[location_counter].score < 0) || (locations[location_counter].score > 5)){

		comprobacion = 1;

	}

	if((locations[location_counter].latitude < -91) || (locations[location_counter].latitude > 90.001)){

		comprobacion = 1;

	}


	if((locations[location_counter].longitude < -181) || (locations[location_counter].longitude > 180.001)){

		comprobacion = 1;

	}

	if((locations[location_counter].opening_hour < 0) ||  (locations[location_counter].opening_hour > 24)){

		comprobacion = 1;

	}

	if((locations[location_counter].close_hour < 0) || (locations[location_counter].close_hour > 24)){

		comprobacion = 1;

	}

	return(comprobacion);
}

//Esta funcion calcula la distancia entre tu posicion y el lugar//

float calculaDistance(float lat2, float long2, float lat1[MAX_LOCATION], float long1[MAX_LOCATION], int rad_position){
	
	float distance = 0;
	
	distance = 6378.137 * acos(sin(lat1[rad_position]) * sin(lat2) + cos(lat1[rad_position]) * cos (lat2) * cos(long2 - long1[rad_position]));


	return(distance);

}



int main () {
	
	int opt = 0,e = 0, i= 0, location_counter = 0, comprobar_error = 0,locations_aux = 0, counter_rads = 0, recorre_struct = 0, introduced_time = 0;
	float introduced_latitude = 0, introduced_longitude = 0, rad_introduced_lat = 0 , rad_introduced_long = 0, rad_latitude[MAX_LOCATION], rad_longitude[MAX_LOCATION];
	char location_array[MAX_ARRAY], trash;

	Location locations[MAX_LOCATION];
	Location locations_aux2;
	Location locations_copia[MAX_LOCATION];

	printf("Welcome to LS Maps!\n");
	
	do{
	printaMenu();

	scanf("%d", &opt);

	switch (opt){

		case 1:
			
			if(location_counter != 9){

				scanf("%c",&trash);

				//en esta parte del codigo cogemos la cadena la pasamos a la duncion de troceo y de deteccion de errores y printamos un mensaje de verificacion//

				do{
					printf("\nLocation information: ");
					fgets(location_array, MAX_ARRAY, stdin);

					locations[location_counter] = troceaCadenas(location_array);

					comprobar_error = localizarError(locations, location_counter);

					if(comprobar_error == 1){
						
						printf("\nERROR: Wrong information! Try again!\n");

					}

				}while(comprobar_error != 0);

				printf("\nLocation added successfully\n");

				location_counter ++;


			}else{

				printf("\nThe system has reached the maximum number of locations\n");

			}

			break;

		case 2:

			if(location_counter != 0){

				recorre_struct = 0;

				//aqui simplemente printamos toda la informacion guardada por el usuario//

				while(recorre_struct != location_counter){
					
					printf("\nLocation %d", recorre_struct + 1);

					printf("\n\tName: %s",locations[recorre_struct].name);
					printf("\n\tType of location: %s", locations[recorre_struct].location_type);
					printf("\n\tQualification: %d", locations[recorre_struct].score);
					printf("\n\tLatitude: %.3f",locations[recorre_struct].latitude);
					printf("\n\tLongitude: %.3f", locations[recorre_struct].longitude);
					printf("\n\tOpening hours: %dh - %dh\n", locations[recorre_struct].opening_hour, locations[recorre_struct].close_hour);
						
					recorre_struct++;

				}

			}else{

				printf("\nERROR: No locations to show\n");

			}

			break;


		case 3:

			if(location_counter != 0){

				e = 0;
				i = 0;
				recorre_struct = 0;
				locations_aux = 0;
				counter_rads = 0;

				//aqui pedimos tanto el horario como la localizacion del usuario//
				do{
					printf("\nIntroduce time:  ");
					scanf("%d",&introduced_time);
					if( introduced_time < 0 || introduced_time > 24 ){

						printf("\nERROR: Wrong value\n");

					}

				}while((introduced_time < 0) || (introduced_time > 24));

				
				do{

					printf("\nIntroduce latitude: ");
					scanf("%f",&introduced_latitude);
					if((introduced_latitude < -90) || (introduced_latitude > 90)){

						printf("\nERROR: Wrong value\n");

					}

				}while((introduced_latitude < -90) || (introduced_latitude > 90));


				do{

					printf("\nIntroduce longitude: ");
					scanf("%f",&introduced_longitude);
					if((introduced_longitude < -180) || (introduced_longitude > 180)){

						
						printf("\nERROR: Wrong value\n");

					}

				}while((introduced_longitude < -180) || ( introduced_longitude > 180));



				//transformacion de grados a radianes//

				while(locations_aux != location_counter){

					rad_latitude[counter_rads] = (locations[locations_aux].latitude * PI) / 180;
	
					rad_longitude[counter_rads] = (locations[locations_aux].longitude * PI) / 180;
					
					locations_aux++;

					counter_rads++;
				}

					rad_introduced_lat = (introduced_latitude * PI) / 180;

					rad_introduced_long = (introduced_longitude * PI) / 180;

				
				recorre_struct = 0;

				//calculamos la distancia//

				while(recorre_struct != location_counter){

					locations[recorre_struct].distance = calculaDistance(rad_introduced_lat, rad_introduced_long, rad_latitude, rad_longitude, recorre_struct);
					
					recorre_struct++;

				}

				i = 0;

				//creamos un array copia modificable//

				while(i != location_counter){
					
					locations_copia[i] = locations[i];

					i++;
				};

				//ordenamos nuestra informacion de menor a mayor//

				for(i = 0;i < location_counter; i++){

					while(( e < location_counter - 1) && (location_counter != 0)){

						if(locations_copia[e].distance > locations_copia[e + 1].distance){

							locations_aux2 = locations_copia[e];

							locations_copia[e] = locations_copia[e + 1];

							locations_copia[e + 1] = locations_aux2;

							if(e != 0){

								e--;

							}

						}else{
							
							e++;

						}

					}

				}

				recorre_struct = 0;
              			i = 1;

				//printado de nuestra info filtrada//

				while(recorre_struct != location_counter){
					    
					if((introduced_time >= locations_copia[recorre_struct].opening_hour) && (introduced_time <= locations_copia[recorre_struct].close_hour)){

					printf("\nLocation %d:",i);

					printf("\n\tName: %s",locations_copia[recorre_struct].name);
					printf("\n\tDistance: %.3f Km\n",locations_copia[recorre_struct].distance);
					i++;

					}

					recorre_struct++;

				}

			}else{

				printf("\nERROR: No locations to show\n");

			}

			
			break;



		case 4:

			printf("\nBye!\n");

			break;


	
		default:

			printf("\nERROR: Wrong action number\n");
			break;


	}
	}while(opt != 4);



	
	return (0);

}