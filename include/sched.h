/** @file sched.h
 *  @brief Header for the scheduler
 *
 *This structure emulates the scheduler
 *
 * @author Emmanuel Madrigal
 * @author Jonatan Chaverri
 * @author Mauricio Montero
 *
 * @bug No known bugs
 *
*/


#ifndef _SCHED_H_
#define _SCHED_H_

#include <glib.h>
#include <stdlib.h>

#include <carro.h>

/** 
 *  @brief structure containing the variables for this object
 */
struct Scheduler{
	GSList *colaReady;    /**< Holds all the cars that are ready for advance  */
	GSList *colaWaiting;  /**< Holds all cars that are waiting for a resource(bridge) */
	
	void* owner;			  /**< Represents the car currently owning the processor */
	
	unsigned char method; /**< Holds the method that handles this process */
	
	pthread_t responsibleThread; /**< Thread in charge of this object */
};

/** @brief called by a car when its resource its not available so it passes to the waiting queue
 *
 *  @param scheduler which handles this car
 *  @param carro to be moved
 *  @return void
 */
void downgradeQueue(struct Scheduler* scheduler, struct Carro* carro);

/** @brief called by a car when its resource its available
 *
 *  @param scheduler which handles this car
 *  @param carro to be moved
 *  @return void
 */
void upgradeQueue(struct Scheduler* scheduler, struct Carro* carro);

/** @brief creates a new scheduler and inits its variables
 *
 *  @param metodo method with which it will be handled
 *  @return created scheduler
 */
struct Scheduler* createScheduler(unsigned char metodo);

/** @brief Called by a car when it exists the bridge in order to no longer be scheduled
 *
 *  @param scheduler from where it's removed
 *  @param carro to be removed from the queue
 *  @return void
 */
void carDone(struct Scheduler* scheduler, struct Carro* carro);

/** @brief Called when a car is created in order to be scheduled when it's turn comes
 *
 *  @param scheduler to be added to
 *  @param carro to be added to the queue
 *  @return void
 */
void addCar(struct Scheduler* scheduler, struct Carro* carro);

/** @brief Call every quantum to schedule applying the round robin algorithm
 *
 *  @param calendarizador to be handled
 *  @return void
 */
void* setCurrentOwner(void* calendarizador);


#endif
