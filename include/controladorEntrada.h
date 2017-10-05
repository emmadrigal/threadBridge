/** @file controladorEntrada.h
 *  @brief Header for the entrada controller
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

#ifndef _CONTROLADORENTADA_H_
#define _CONTROLADORENTADA_H_

#include <stdlib.h>
#include <time.h>
#include <pthread.h>


#include <puente.h>
#include <entrada.h>
#include <sched.h>


/** 
 *  @brief structure containing the variables for this object
 */
struct ControladorEntrada{
	int tipo;           /**< Type of traffic controller, 0 for traffic light, 1 for traffic officer and 2 for jungle law*/
	int tiempo;         /**< Time that the traffic light will stay on either state */
	int maxCarros;      /**< Max number of cars that the traffic officer will allow through before stopping traffic*/
	
	int carrosAceptados;/**< Cars that have been currently accepted*/
	int carrosEnviados; /**< Cars that have been currently sent*/
	
	struct Entrada *entrada;      /**< pointer to the entrance being controlled */
	struct Puente *puente;        /**< pointer to the bridge begin connected */
	
	char side;                    /**< Dirección being controlled, -1 is right and 1 is left */
	
	clock_t start_t, end_t;		  /**< Holds the time variables */
	
	pthread_t responsibleThread; /**< Thread in charge of this object */
	pthread_mutex_t ctrlLock;					 /**< Lock for the current bridge*/
};

/** @brief Creates the ControladorEntrada object including the objects represented in its struct variables
 *
 *  @param tipo tipe of traffic controller on either side of the bridge
 *  @param tiempo time for the traffic light to stay in either state, this is ignored if the type isn't traffic light
 *  @param maxCarros max number of cars that a traffic officer will allow to pass before allowing new cars to pass
 *  @param pointer to the bridge connect to this entrance
 *  @param paramsGen Params for the generation of either side, this include median, % of ambulances and % of radioactive cars
 *  @return pointer to the created structure
 */
struct ControladorEntrada* createControlador(int tipo, int tiempo, int maxCarros, struct Puente* puente, int paramsGen[3], char lado, struct Scheduler* scheduler);

/**
 * @brief Control loop
 *
 * This function is called by a loop and according to the controller type it will
 * allow or restrict new cars from accessing the bridge
 *
 * @param ctrl object whose traffic light is being controlled
 * @return void
 */
void* updateSemaforo(void* ctrl);

/**
 * @brief accepts cars from the bridge
 *
 * This function is used for the traffic officer to restrict the number of cars to pass
 *
 * @param ctrl controler being updated
 * @return void
 */
void aceptarCarro(struct ControladorEntrada* ctrl);

/**
 * @brief This function tries to send a new car onto the bridge
 *
 * Asks the bridge for its current state and tries to periodically advance the cars
 *
 * @param ctrl controler being updated
 * @return void
 */
char enviarCarro(struct ControladorEntrada* ctrl, struct Carro* carro);


/**
 * @brief Changes the state of the light in order to allow a radioactive car to pass
 *
 *
 * @param ctrl controler being updated
 * @return void
 */
void forceChange(struct ControladorEntrada* ctrl);

#endif

