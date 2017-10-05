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
#include <sched.h>

//Solo un puente puede imprimir a la vez
pthread_mutex_t printLock;

/** 
 *  @brief structure containing the variables for this object
 */
struct Puente{
	int largo;                                   /**< Lenght of the bridge representing how many cars it can hold */
	struct ControladorEntrada* entradaIzquierda; /**< pointer to the controller on the left side*/
	struct ControladorEntrada* entradaDerecha;   /**< pointer to the controller on the right side*/
	char flujo;                                  /**< char indicating the direction of the flux; 0 is no cars on the bridge, -1 is to the right and 1 is to the left*/
	struct Carro** espacios;                     /**< array holding the cars currently on the bridge*/
	
	int id;
	
	pthread_t responsibleThread; /**< Thread in charge of this object */
	pthread_mutex_t puenteLock;					 /**< Lock for the current bridge*/
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
struct Puente* createPuente(int largo, int tipo[2], int tiempo[2], int maxCarros[2], int paramsGen[6], int id, unsigned char method);


/** @brief Iterates through the bridge and sets its state to empty if that's the case
 *
 *	This function is also in charge of printing the data to the terminal
 *
 * @param bridge to be monitored
 * @return void
 */
void* chequearEstado(void* bridge);

/** @brief Asks for a change in the traffic light in order to advance radioactive cars
 *
 * If there are radioactive cars are in the queue then they ask for a change from the other side of the bridge
 * 
 * @param puente whose entrances are going to be changed
 * @return void
 */
void askSemaforo(struct Puente* puente);

/** @brief When a car tries to enter this function checks wheter the car can get on the brdige
 *
 * @param puente where check is being made
 * @param direccion from where the car is being recieved
 * @param carro being recieved
 * @return 1 if success and 0 if failure
 */
int recibirCarro(struct Puente* puente, char direccion, struct Carro* carro);

/** @brief Checks wherever the resource is available
 *
 * @param puente where check is being made
 * @param direccion from where the car is being recieved
 * @param current position of the car
 * @return 1 if success and 0 if failure
 */
int checkResource(struct Puente* puente, char direccion, int position);


#endif
