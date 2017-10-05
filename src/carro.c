/** @file puente.c
 *  @brief Implementation for the carro object
 *
 * This is the implementation of the carro controller
 * This funcitions handle the movement of cars 
 *
 * @author Emmanuel Madrigal
 * @author Jonatan Chaverri
 * @author Mauricio Montero
 *
 * @bug No known bugs
 *
*/

#include <carro.h>

void* avanzar(void* car){
	struct Carro* carro = (struct Carro*) car;
	
	//TODO get this from config file
	int quantum = 100000;//100ms
	
	while(1){
		usleep(quantum);
		
		//TODO check if this is owner
		if(true){
			//If not on bridge
			//TODO try to get on bridge
			
			
			//If on bridge
			//TODO Advance as far as it can
		}
	}
}
