/** @file puente.c
 *  @brief Implementation for the puente controller
 *
 * This is the implementation of the puente controller
 * This funcitions handle the movement of cars on the bridge
 * and recieving and sending them to either part of the bridge
 * Its also responsable for knowing the direction of the bridge flow
 *
 * @author Emmanuel Madrigal
 * @author Jonatan Chaverri
 * @author Mauricio Montero
 *
 * @bug No known bugs
 *
*/

#include <puente.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"



struct Puente* createPuente(int largo, unsigned char tipo[2], unsigned char tiempo[2], unsigned char maxCarros[2], unsigned char paramsGen[6]){
	struct Puente* puente = malloc(sizeof(struct Puente));
	puente->largo = largo;
	puente->flujo = 0;
	
	puente->entradaIzquierda = createControlador(tipo[0], tiempo[0], maxCarros[0], puente, paramsGen,        1);
	puente->entradaDerecha   = createControlador(tipo[1], tiempo[1], maxCarros[1], puente, (paramsGen + 3), -1);
	
	//Esto es una serie de punteros hacia los carros
	puente->espacios = calloc(sizeof(struct Carro*)*largo, largo);
	
	return puente;
}

void* chequearEstado(void* bridge){
	struct Puente* puente = (struct Puente*) bridge;
	

	while(1){
		//TODO obtener este valor desde el archivo de config
		usleep(100000);
		
		//Chequea si el puente está vacio
		int carros = 0;
		for(int i = 0; i < puente->largo; i++){
			if(puente->espacios[i] != 0)
				carros++;
		}
		if(carros == 0)
			puente->flujo = 0;
		
		if(puente->entradaIzquierda->entrada->semaforoEntrada == 1)
			printf(ANSI_COLOR_GREEN"X"ANSI_COLOR_RESET);
		else
			printf(ANSI_COLOR_RED"X"ANSI_COLOR_RESET);
		
		for(int i = 0; i < puente->largo; i++){
			if(puente->espacios[i] != 0){
				if(puente->espacios[i]->tipo == 0)
					printf(ANSI_COLOR_YELLOW"C"ANSI_COLOR_RESET);
				else if(puente->espacios[i]->tipo == 1)
					printf(ANSI_COLOR_RED"A"ANSI_COLOR_RESET);
				else if(puente->espacios[i]->tipo == 2)
					printf(ANSI_COLOR_GREEN"R"ANSI_COLOR_RESET);
			}
			else
				printf("0");
		}
		
		if(puente->entradaDerecha->entrada->semaforoEntrada == 1)
			printf(ANSI_COLOR_GREEN"X"ANSI_COLOR_RESET);
		else
			printf(ANSI_COLOR_RED"X"ANSI_COLOR_RESET);
		
		printf("\n");
		/*
		printf("izquierda\n\taceptados: %d\t enviados: %d\n", puente->entradaIzquierda->carrosAceptados, puente->entradaIzquierda->carrosEnviados);
		printf("derecha\n\taceptados: %d\t enviados: %d\n", puente->entradaDerecha->carrosAceptados, puente->entradaDerecha->carrosEnviados);
		*/
		/*
		printf("Entrada izquierda-> carros: %d\t ambulancias: %d\t radioactivos %d\n", g_slist_length(puente->entradaIzquierda->entrada->colaCarros), g_slist_length(puente->entradaIzquierda->entrada->colaAmbulancias), g_slist_length(puente->entradaIzquierda->entrada->colaRadioactivos));
		
		printf("Entrada derecha-> carros: %d\t ambulancias: %d\t radioactivos %d\n\n", g_slist_length(puente->entradaDerecha->entrada->colaCarros), g_slist_length(puente->entradaDerecha->entrada->colaAmbulancias), g_slist_length(puente->entradaDerecha->entrada->colaRadioactivos));
		*/
		

		
		
	}
}

int min(int a, int b){
	if(a < b)
		return a;
	return b;
}


int recibirCarro(struct Puente* puente, char direccion, struct Carro* carro){

	//Only one car can try to enter at the time
	pthread_mutex_lock(&(puente->puenteLock));
	
	int out = 0;

	if(puente->flujo == 0){//Si no hay carros en el puente
		//Si se recibe un carro de la derecha
		if(direccion == -1){
			puente->espacios[puente->largo - 1] = carro;
			puente->flujo = -1;
		}
		//Si se recibe un carro de la izquierda
		else if(direccion == 1){
			puente->espacios[0] = carro;
			puente->flujo = 1;
		}
		out = 1;
	}
			
	//Hay carros llendo en la otra dirección
	else if(puente->flujo == direccion){
		//Carros moviendose de izquierda a derecha
		if(puente->flujo == -1){
			//Cuando se encuentre el 1er carro en la calle
			if(puente->espacios[0] != 0)
				puente->espacios[0] = carro;
			
		}
		
		if(puente->flujo == 1){
			//Cuando se encuentre el 1er carro en la calle
			if(puente->espacios[puente->largo -1] != 0)
					puente->espacios[puente->largo -1] = carro;
		}
		out =  1;
	}
	
	//Chequear si el primer espacio está vacio se deja en valor default de 0
	pthread_mutex_unlock(&(puente->puenteLock));
	
	return out;
}


void askChange(struct Puente* puente, char direccion){
	//TODO implement this	
}




