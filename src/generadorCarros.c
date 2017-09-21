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

struct GeneradorCarros* crearGenerador(unsigned char media, unsigned char ambulancias, unsigned char radioactivos, struct Entrada* entrada){
	struct GeneradorCarros* generador = malloc(sizeof(struct GeneradorCarros));
	
	//TODO checkear que lambda sea mayor a 0
	generador->media = media;
	
	//TODO check that this aren't over a 100
	generador->ambulancias = ambulancias;
	generador->radioactivos = radioactivos;
	
	generador->entrada = entrada;
	
	return generador;
	
}

//Según la la función de probabilidad agrega un nuevo carro a la cola de entrada.
void *generarCarro(void* generadorParam){

	struct GeneradorCarros* generador = (struct GeneradorCarros*) generadorParam;
	//TODO implement exponential function
	//TODO implement function to change car type
	//TODO implement function to change car velocity
	
	while(1){
		struct Carro* carro = malloc(sizeof(struct Carro));
		
		carro->velocidad = 10;
		carro->tipo      =  0;
	
		//TODO put mutex lock on entrada
		agregarCarro(generador->entrada, carro);
		
		//Sleep 1 second
		usleep(500000);
	}	
	
}
