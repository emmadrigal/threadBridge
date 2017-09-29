/** @file main.c
 *  @brief main function
 *
 * This file contains the main file in charge of the base object creation
 *
 * @author Emmanuel Madrigal
 * @author Jonatan Chaverri
 * @author Mauricio Montero
 *
 * @bug No known bugs
 *
*/

#include <pthread.h>
#include <stdio.h>

#include <carro.h>
#include <controladorEntrada.h>
#include <entrada.h>
#include <generadorCarros.h>
#include <puente.h>

int main(int argc, char** argv){
	printf("Hello World!!!\n");

	
    pthread_t threads[7];

	//TODO get values from config file
	unsigned char tipo[2] = {0,0};
	unsigned char tiempo[2] = {5,5};
	unsigned char maxCarros[2] = {8,6};
	unsigned char paramsGen[6] = {1,2,3,4,5,6};
	int largo = 20;
	
	struct Puente* puente = createPuente(largo, tipo, tiempo, maxCarros, paramsGen);
	
	//TODO move this to the creation of objects
	pthread_create(&threads[0], NULL, generarCarro, (void*) puente->entradaIzquierda->entrada->generador);
	pthread_create(&threads[1], NULL, generarCarro, (void*) puente->entradaDerecha->entrada->generador);
	
	pthread_create(&threads[2], NULL, updateSemaforo, (void*) puente->entradaIzquierda);
	pthread_create(&threads[3], NULL, updateSemaforo, (void*) puente->entradaDerecha);
	
	
	pthread_create(&threads[4], NULL, chequerEstado, (void*) puente);
	
    
    usleep(180000000);
	
	
	return 0;
}
