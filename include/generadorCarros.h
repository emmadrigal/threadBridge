/** @file generadorCarros.h
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

#ifndef _GENERADORCARROS_H_
#define _GENERADORCARROS_H_

#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>


#include <carro.h>
#include <entrada.h>

/** 
 *  @brief structure containing the variables for this object
 */
struct GeneradorCarros{
	int media;         /**< Median for the exponential distribution of the generation time*/
	int ambulancias;   /**< Percentage of ambulances */
	int radioactivos;  /**< Percentage of radioactive cars */
	
	struct Entrada* entrada;
	struct Puente* puente;
	
	struct Scheduler* scheduler;
	
	pthread_t responsibleThread; /**< Thread in charge of this object */
};

/** @brief Creates the GeneradorCarros object
 *
 *  @param media Median for the exponential distribution of the generation time
 *  @param ambulancias Percentage of ambulances
 *  @param radioactivos Percentage of radioactive cars
 *  @param entrada pointer to the entrance where the cars will be added
 *  @return pointer to the created structure
 */
struct GeneradorCarros* crearGenerador(int media, int ambulancias, int radioactivos, struct Entrada* entrada, struct Puente* bridge, struct Scheduler* scheduler);

/** @brief generates new cars into an entrance
 *
 *  This function is called in a loop and according to an exponential distribution generates new cars
 *
 *  @param pointer to the generator to be in the loop
 *  @return void
 */
void *generarCarro(void* generador);

#endif
