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



struct Puente* createPuente(int largo, int tipo[2], int tiempo[2], int maxCarros[2], int paramsGen[6], int id){
	struct Puente* puente = malloc(sizeof(struct Puente));
	puente->largo = largo;
	puente->flujo = 0;
	
	
	
	puente->entradaIzquierda = createControlador(tipo[0], tiempo[0], maxCarros[0], puente, paramsGen,        1);
	puente->entradaDerecha   = createControlador(tipo[1], tiempo[1], maxCarros[1], puente, (paramsGen + 3), -1);
	
	//Esto es una serie de punteros hacia los carros
	puente->espacios = calloc(sizeof(struct Carro*)*largo, largo);
	
	puente->id = id;
	
	mypthread_create(&(puente->responsibleThread), NULL, chequearEstado, (void*) puente, 0);
	
	return puente;
}

void* chequearEstado(void* bridge){
	struct Puente* puente = (struct Puente*) bridge;
	

	while(1){
		//TODO obtener este valor desde el archivo de config
		usleep(250000);
		//pthread_mutex_lock(&(puente->puenteLock));
		{	
			char hayCarro = 0;
			for(int i = 0; i < puente->largo; i++){
				if(puente->espacios[i] != 0){
					hayCarro = 1;
					break;
				}
			}
			if(hayCarro == 0){
				puente->flujo = 0;
			}
		}
		
		unsigned char physSi[15];
		
		physSi[0] = g_slist_length(puente->entradaIzquierda->entrada->colaCarros);
		physSi[1] = g_slist_length(puente->entradaIzquierda->entrada->colaAmbulancias);
		physSi[2] = g_slist_length(puente->entradaIzquierda->entrada->colaRadioactivos);
		
		pthread_mutex_lock(&(printLock));
		if(puente->entradaIzquierda->entrada->semaforoEntrada == 1){
			printf(ANSI_COLOR_GREEN"X"ANSI_COLOR_RESET);
			physSi[3] = "s";
		}
		else{
			printf(ANSI_COLOR_RED"X"ANSI_COLOR_RESET);
			physSi[3] = "S";
		}
		
		for(int i = 0; i < puente->largo; i++){
			if(puente->espacios[i] != 0){
				if(puente->espacios[i]->tipo == 0){
					printf(ANSI_COLOR_YELLOW"C"ANSI_COLOR_RESET);
					physSi[4 + i] = "c";
				}
				else if(puente->espacios[i]->tipo == 1){
					printf(ANSI_COLOR_RED"A"ANSI_COLOR_RESET);
					physSi[4 + i] = "a";
				}
				else if(puente->espacios[i]->tipo == 2){
					printf(ANSI_COLOR_GREEN"R"ANSI_COLOR_RESET);
					physSi[4 + i] = "r";
				}
			}
			else{
				printf("0");
				physSi[4 + i] = 0;
			}
		}
		
		if(puente->entradaDerecha->entrada->semaforoEntrada == 1){
			printf(ANSI_COLOR_GREEN"X"ANSI_COLOR_RESET);
			physSi[11] = "s";
		}
		else{
			printf(ANSI_COLOR_RED"X"ANSI_COLOR_RESET);
			physSi[11] = "S";
		}
		
		printf("\n");

		printf("Entrada izquierda-> carros: %d\t ambulancias: %d\t radioactivos %d\n", g_slist_length(puente->entradaIzquierda->entrada->colaCarros), g_slist_length(puente->entradaIzquierda->entrada->colaAmbulancias), g_slist_length(puente->entradaIzquierda->entrada->colaRadioactivos));
		
		printf("Entrada derecha-> carros: %d\t ambulancias: %d\t radioactivos %d\n\n", g_slist_length(puente->entradaDerecha->entrada->colaCarros), g_slist_length(puente->entradaDerecha->entrada->colaAmbulancias), g_slist_length(puente->entradaDerecha->entrada->colaRadioactivos));
		
		physSi[12] = g_slist_length(puente->entradaDerecha->entrada->colaCarros);
		physSi[13] = g_slist_length(puente->entradaDerecha->entrada->colaAmbulancias);
		physSi[14] = g_slist_length(puente->entradaDerecha->entrada->colaRadioactivos);
		
		for(int i = 0; i < 15; i++){
			printf("%u ", physSi[i]);
		}
		printf("\n");
		
		pthread_mutex_unlock(&(printLock));
		//pthread_mutex_unlock(&(puente->puenteLock));
	}
}



int recibirCarro(struct Puente* puente, char direccion, struct Carro* carro){

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
			//Si no hay un carro en la primera dirección
			if(puente->espacios[0] != 0){
				puente->espacios[0]	 = carro;
				out =  1;
			}
		}
		else if(puente->flujo == 1){
			//Si no hay un carro en la primera dirección
			if(puente->espacios[puente->largo -  1] != 0){
				puente->espacios[puente->largo - 1] = carro;
				out =  1;
			}
		}
	}
	
	//Chequear si el primer espacio está vacio se deja en valor default de 0
	//pthread_mutex_unlock(&(puente->puenteLock));
	
	return out;
}


void askSemaforo(struct Puente* puente){
	forceChange(puente->entradaDerecha);
	forceChange(puente->entradaIzquierda);
}




