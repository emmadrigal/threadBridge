/** @file carro.h
 *  @brief header for the carro object
 *
 * This file contains the necessary variables
 * for the carro object
 *
 * @author Emmanuel Madrigal
 * @author Jonatan Chaverri
 * @author Mauricio Montero
 *
 * @bug No known bugs
 *
*/

#ifndef _CARRO_H_
#define _CARRO_H_

#include <pthread.h>

#include <puente.h>

/** 
 *  @brief structure containing the variables for this object
 */
struct Carro{
	int velocidad;          /**< Speed of this car in number of car lenghts */
	unsigned char tipo;     /**< Type of car; 0 is normal, 1 is ambulance and 2 is radioactive*/
	int position;           /**< Type of car; 0 is normal, 1 is ambulance and 2 is radioactive*/
	int prioridad;			/**< Starts at 20 for radioactive, 30 for ambulances and 40 for regular cars*/
	
	struct Puente*  puente;
	struct Entrada* entrada;
	
	struct Scheduler* scheduler;
	
	char direccion;			/**< 1 es de izquierda a derecha y -1 es viceversa */
	
	pthread_t responsibleThread;
};

/** @brief Runs the loop in charge of the cars movement
 *
 *  @param car car to be handled
 *  @return void
 */
void *avanzar(void* car);

#endif
