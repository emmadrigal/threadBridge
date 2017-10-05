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
	GSList *colaWaiting;  /**< Holds all cars that are waiting for a resource */
	
	void* owner;			  /**< Represents the car currently owning the processor */
	
	unsigned char method; /**< Holds the method that handles this process */
	
	pthread_t responsibleThread; /**< Thread in charge of this object */
};


/** @brief 
 *
 *  @param 
 *  @return void
 */
struct Scheduler* createScheduler(unsigned char metodo);

/** @brief 
 *
 *  @param 
 *  @return void
 */
void carDone(struct Scheduler* scheduler, struct Carro* carro);

/** @brief 
 *
 *  @param 
 *  @return void
 */
void addCar(struct Scheduler* scheduler, struct Carro* carro);

/** @brief 
 *
 *  @param 
 *  @return void
 */
void* setCurrentOwner(void* calendarizador);


#endif
