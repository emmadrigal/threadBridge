/** @file puente.h
 *  @brief Header for the puente controller
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

#ifndef _PUENTE_H_
#define _PUENTE_H_


#include <stdlib.h>


#include <controladorEntrada.h>
#include <carro.h>


/** 
 *  @brief structure containing the variables for this object
 */
struct Puente{
	int largo;                                   /**< Lenght of the bridge representing how many cars it can hold */
	struct ControladorEntrada* entradaIzquierda; /**< pointer to the controller on the left side*/
	struct ControladorEntrada* entradaDerecha;   /**< pointer to the controller on the right side*/
	char flujo;                                  /**< char indicating the direction of the flux; 0 is no cars on the bridge, 1 is to the right and -1 is to the left*/
	struct Carro* espacios;                      /**< array holding the cars currently on the bridge*/
};

/** @brief Creates the puente object including the objects represented in its struct variables
 *
 *  @param largo lenght of the brige in number of cars
 *  @param tipo tipe of traffic controller on either side of the bridge
 *  @param tiempo time for the traffic light to stay in either state, this is ignored if the type isn't traffic light
 *  @param maxCarros max number of cars that a traffic officer will allow to pass before allowing new cars to pass
 *  @param paramsGen Params for the generation of either side, this include median, % of ambulances and % of radioactive cars
 *  @return pointer to the created structure
 */
struct Puente* createPuente(int largo, unsigned char tipo[2], unsigned char tiempo[2], unsigned char maxCarros[2], unsigned char paramsGen[6]);

/** @brief Moves the cars along the bridge
 * 
 * This function is handled in a thread and automatically changes the state of the bridge flux and the position of the cars
 * 
 * @param puente Object that will be controlled
 * @return void
 */
void avanzarCarros(struct Puente* puente);

/** @brief Accepts or denies new cars onto the bridge
 *
 * Whenever a traffic controller wants to move a car onto the bridge
 * the ask this function which will check whether there are space on the bridge
 * and if the flow is moving in the correct direction
 * 
 * @param puente object to be updated
 * @param direccion direction from which the car is being recieved
 * @param carro car to be added
 *
 * @return 1 if accepted car and 0 if rejected
 */
int recibirCarro(struct Puente* puente, char direccion, struct Carro* carro);

#endif
