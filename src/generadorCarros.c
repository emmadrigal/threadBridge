/** @file generadorCarros.c
 *  @brief Implementation for the car generator
 *
 * This is the implementation of the car generator
 * This function is in charge of creting new car and adding them to 
 * the entrada object
 *
 * @author Emmanuel Madrigal
 * @author Jonatan Chaverri
 * @author Mauricio Montero
 *
 * @bug No known bugs
 *
*/

#include <generadorCarros.h>

struct GeneradorCarros* crearGenerador(int media, int ambulancias, int radioactivos, struct Entrada* entrada, struct Puente* bridge, struct Scheduler* scheduler){
	struct GeneradorCarros* generador = malloc(sizeof(struct GeneradorCarros));
	
	//TODO checkear que lambda sea mayor a 0
	generador->media = media;
	generador->puente = bridge;
	
	//TODO check that this aren't over a 100
	generador->ambulancias = ambulancias;
	generador->radioactivos = radioactivos;
	
	generador->entrada = entrada;
	
	generador->scheduler = scheduler;
	
	//mypthread_create(&(generador->responsibleThread), NULL, generarCarro, (void*) generador, 0);
	pthread_create(&(generador->responsibleThread), NULL, generarCarro, (void*) generador);
	
	return generador;
	
}

//Según la la función de probabilidad agrega un nuevo carro a la cola de entrada.
void *generarCarro(void* generadorParam){

	struct GeneradorCarros* generador = (struct GeneradorCarros*) generadorParam;
	//TODO get car velocity from config file
	int velocidadMedia = 1;
	
	srand(time(NULL));   // should only be called once per thread
	
	float commulativeProv = 0.0f;
	int waitedTime = 0;
	
	while(1){
		struct Carro* carro = malloc(sizeof(struct Carro));
		
		commulativeProv += exp(-1*waitedTime/(generador->media))/(generador->media);
		
		//Generate a number between 1 and 100
		char percentageTime = rand() % 100 + 1;
		
		if(commulativeProv*100 > percentageTime	){
			commulativeProv = 0.0f;
			waitedTime      =    0;
			
			//Generate a number between 0 and 99
			char percentageCar = rand() % 100;
			
			if(percentageCar < generador->ambulancias){
				carro->tipo =  1;
				carro->prioridad = 30;
			}
			else if(percentageCar >= (100 - generador->radioactivos)){
				carro->tipo =  2;
				carro->prioridad = 20;
			}
			else{
				carro->tipo =  0;
				carro->prioridad = 40;
			}
			
			carro->velocidad = rand() % (velocidadMedia*2) + 1;
		
			carro->puente    = generador->puente;
			carro->entrada   = generador->entrada;
			carro->scheduler = generador->scheduler;
			
			//TODO prioridad inicial es 20 para radioactivos, 30 para ambulancias y 40 para carros
		
			//Inicia fuera en una entrada
			carro->position = -1;
	
			addCar(carro->scheduler, carro);
		
			//mypthread_create(&(carro->responsibleThread), NULL, avanzar, (void*) carro, 0);
			pthread_create(&(carro->responsibleThread), NULL, avanzar, (void*) carro);
		}
		else{
			waitedTime++;
		}
		
		//Every second
		usleep(1000000);
	}	
	
}
