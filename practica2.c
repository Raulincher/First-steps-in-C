//En este programa se pretende crear una asimilacion del videojuego amongUS donde el usuario deberá completar 3 pruebas para superar el juego//
//Raúl Luque Sanmartín//
//05/12/2020//
//05/12/2020//



#include <stdio.h>

//funcion que printa el menu//
//no tienen parametros ya que es una funcion que me printa el menu//
//no devuelve nada ya qie es un void//
void printaMenu(){
	printf("\nWhat task would you like to do?\n");

	printf("\n1. Guess divisors | 2. The reverse password | 3. The labyrinth | 4. Exit\n");

	printf("Selected action: ");
	

}

//funcion que comprueba que el numero introducido sea positivo y que contenga menos de 7 cifras//
//parametros: in: number = valor a comprobar//
//Retorno: out: number = devuelve el numero comprobado//

int comprobarCifras(int number){

	while(number < 1 || number > 9999999){

		printf("\nEnter number: ");
		scanf("%d",&number);

	}

return(number);
}


//funcion que comprueba que el numero introducido no sea primo//
//parametros: in: number = valor a comprobar//
//Retorno: out: number = devuelve el numero comprobado//

int comprobarPrimo(int number){

	int i = 1, comprobacion = 0;

	while(i <= number){

		if(number % i == 0){

			comprobacion++;

		}

		i++;

	}

	return(comprobacion);
}

//funcion que invierte number y comprueba que sea igual a password//
//parametros: in: password = contraseña a verificar
	      in: number = numero introducido por el ususario
//Retorno: out: verificacion = devuelve 1 o 0 dependiendo del resultado de la comprobacion//

int verificarPassword(int password, int number){

	int verificacion = 0, last_digit = 0, new_number = 0;

	while(number != 0){

		last_digit = number % 10;

		number = number / 10;

		new_number = (new_number * 10) + last_digit;

	}

	if(password == new_number){

		verificacion = 1;

	}else{

		verificacion = 0;

	}

	return(verificacion);
}

//funcion que comprueba que el caracter movement sea correcto//
//parametros: in: movement = caracter introducido por el usuario para verificar
//Retorno: out: movement = devuelve el caracter comprobado//
char comprobarMove(char movement){

	char trash;
	
	while((movement != 'N') && (movement != 'W') && (movement != 'S') && (movement != 'E')){
		scanf("%c",&trash);
		printf("\nError, to move use the keys N,S,E,W\n");
		printf("\nEnter key to move: ");
		scanf("%c", &movement);
	}
	return(movement);
}

int main () {

	int aux_opt3_done = 0, comp_maze = 0, x = 0, y = 0, correct = 0, password = 0, opt = 0, aux_exit = 0, aux_opt1 = 0, tasks_done = 0, number = 0, i = 0, primo = 0, divisor = 0, comprueba_divisor = 0, divisor1 = 0, divisor2 = 0, divisor3 = 0, aux_opt2_done = 0, aux_opt1_done = 0;
	
	char movement, trash;

	printf("Welcome to amongLs\n");

	do{

	//función void para printar el menu//

	printaMenu();
	
	scanf("%d",&opt);

	//comprobación de menu//

	while(opt < 1 || opt > 4){

		printf("\nERROR: The correct actions are between [1, 4]\n");
		
		printaMenu();

		scanf("%d",&opt);

	}

	switch(opt){

		case 1:
			
			//comprobamos si la tarea se ha realizado con anterioridad//

			if(aux_opt1_done == 0){
			
			//reinicio variables//
			aux_opt1 = 0;
			i = 0;

			printf("\nEnter number: ");
			scanf("%d",&number);

			//llamamos a comprobarCifras// 

			number = comprobarCifras(number);
			
			if(number != 1){
			//llamamos a comprobarPrimo//
			primo = comprobarPrimo(number);
			}

			//comprobamos que el numero no sea ni primo ni uno//
			
			if((number == 1) || (primo == 2)){
				
				aux_opt1 = 1;
				printf("\nNumber not valid.\n");

			}
			
			while((i < 3) && aux_opt1 != 1 ){
					
					printf("\nDivisor %d.\n", i + 1);

					printf("\nEnter number: ");

					scanf("%d",&divisor);

					comprueba_divisor = number % divisor;

					//comprobamos que el divisor introducido sea ciertamente un divisor de nuestro number//

					if(comprueba_divisor != 0){
						
						printf("\n%d is not a divisor of %d!\n",divisor,number);
						aux_opt1 = 1;
					}

					//alamcenamos los digitos usados para comprobarlos mas adelante//

					if(i == 0){
						
						divisor1 = divisor;
					}

					if(i == 1){

						divisor2 = divisor;

					}

					if(i == 2){

						divisor3 = divisor;

					}

					//comprobamos que nuestros 3 digitos sean diferentes entre si//

					if(i == 1 && divisor1 == divisor2){

						printf("\nYou have already tried that number!\n");
						aux_opt1 = 1;

					}

					if(i == 2 && divisor2 == divisor3){

						printf("\nYou have already tried that number!\n");
						aux_opt1 = 1;

					}
					if(i == 2 && divisor1 == divisor3) {
						
						printf("\nYou have already tried that number!\n");
						aux_opt1 = 1;

					}

					i++;
			}

			//comprobamos si la tarea realizada se ha terminado con exito o si por el contrario ha fallado//
			
			if (aux_opt1 == 1){

				printf("\nTask failed!\n");
				

			}else{

				printf("\nTask done!\n");
				aux_opt1_done = 1;
				tasks_done++;

			}}else{
			    
			    printf("\nTask already done\n");
			    
			}

			break;
		
		case 2: 

			//comprobamos si esta tarea se ha relizado con anterioridad//

			if(aux_opt2_done == 0){

				printf("\nEnter number: ");
				scanf("%d",&number);

				//llamamos a comprobarCifras//

				number = comprobarCifras(number);
		
				printf("\nPassword: ");
				scanf("%d",&password);
				
				//llamamos a verificar password//

				correct = verificarPassword(password, number);

				//comprobamos si la terea se ha relizado con exito//

				if(correct == 1 ){

					printf("\nTask done!\n");
					aux_opt2_done = 1;
					tasks_done ++;

				}else{

					printf("\nTask failed!\n");

				}

			}else{
			    
			    printf("\nTask already done\n");
			    
			}
			break;




		case 3:

			//comprobamos si la tarea se ha realizado con anterioridad//

			if(aux_opt3_done == 0){

				//reinicio variables//
				
				i = 0, x = 0, y = 0;

				printf("\nYou are located at the coordinates (0,0) of the maze. The coordinates to exit are (3,4)\n");

				printf("\nMove around the map using cardinal keys N,S,E,W\n");

				while(i < 10 && comp_maze != 1){
					
					scanf("%c",&trash);

					printf("\nEnter key to move: ");
					
					scanf("%c", &movement);

					//llamamos a comprobarMove//

					movement = comprobarMove(movement);

					//Aplicamos el movimiento dependiendo de la letra pulsada//
										
					if(movement == 'W'){

						x = x - 1;
					}

					if(movement == 'S'){

						y = y - 1;
					}

					if(movement == 'N'){

						y = y + 1;
					}

					if(movement == 'E'){

						x = x + 1;
					}

					printf("\nYou are in (%d,%d) of the maze\n", x,y);

					//comprobamos si hemos llegado a nuestro destino//

					if(x == 3 && y== 4){
						comp_maze = 1;
					}
					i++;
				}


				//comprobamos si la tarea se ha relizado con exito//

				if (x == 3 && y == 4){
					
					aux_opt3_done = 1;
					tasks_done++;
					printf("\nTask done!\n");

				}else{

					printf("\nTask failed!\n");
				}
			}else{
			    
			    printf("\nTask already done\n");
			    
			}

			break;

		case 4:

			//caso de finalizacion del programa//

			printf("\nThanks for playing!\n");

			aux_exit = 1;

			break;


}
}while(tasks_done != 3 && opt != 4);

//comprobamos que hemos terminado el programa por haber realizado 3 tareas y no por haber pulsado exit//

	if(aux_exit == 0){

		printf("\nAll tasks done! You completed 3 tasks!\n");


		printf("\nThanks for playing!\n");


	}
return (0);
}
