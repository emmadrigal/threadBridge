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
#include <glib.h>

#include <puente.h>
#include <carro.h>
#include <generadorCarros.h>
#include <sched.h>

struct Puente;
struct Carro;

/** 
 *  @brief structure containing the variables for this object
 */
struct Entrada{
	unsigned char semaforoEntrada;     /**< Light indicating if currently advence is allowed; 0 is red and 1 is green */
	struct GeneradorCarros* generador; /**< pointer to the generator adding cars to this entrance */
	
	struct ControladorEntrada* ctrl;   /**< pointer to the controler of the traffic at this entrance */
	
	char side;                         /**< Dirección being controlled, -1 is right and 1 is left */
};


/** @brief Creates the entrada object including the objects represented in its struct variables
 *
 *  @param paramsGen Params for the generation of either side, this include median, % of ambulances and % of radioactive cars
 *  @return pointer to the created structure
 */
struct Entrada* crearEntrada(int paramsGen[3], struct Puente* puente, struct Scheduler* scheduler, struct ControladorEntrada* ctrl);


#endif
