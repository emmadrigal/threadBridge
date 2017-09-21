/** @file entrada.h
 *  @brief Header for the entrada object
 *
 * This file contains the struct containing the tributes for the class
 * and also contains the functions that handle this object
 *
 * @author Emmanuel Madrigal
 * @author Jonatan Chaverri
 * @author Mauricio Montero
 *
 * @bug No known bugs
 *
*/

#ifndef _ENTRADA_H_
#define _ENTRADA_H_

#include <stdlib.h>
#include <stdio.h>

#include <glib.h>
#include <carro.h>
#include <generadorCarros.h>

/** 
 *  @brief structure containing the variables for this object
 */
struct Entrada{
	GSList *colaCarros;                /**< Queue of cars waiting in this queue */
	unsigned char semaforoEntrada;     /**< Light indicating if currently advence is allowed */
	struct GeneradorCarros* generador; /**< pointer to the generator adding cars to this entrance */
};


/** @brief Creates the entrada object including the objects represented in its struct variables
 *
 *  @param paramsGen Params for the generation of either side, this include median, % of ambulances and % of radioactive cars
 *  @return pointer to the created structure
 */
struct Entrada* crearEntrada(unsigned char paramsGen[3]);


/** @brief Adds a new car into the queue
 *
 *  @param entrada pointer to the bridge connect to this entrance
 *  @param carro car being added to this queue
 *  @return void
 */
void agregarCarro(struct Entrada* entrada, struct Carro* carro);

/** @brief Gets the first car on the queue
 *
 *  @param entrada whose data is being used
 *  @return car with the highest priority
 */
struct Carro* getCarro(struct Entrada* entrada);

#endif
