/** @file entrada.c
 *  @brief Implementation for the entrada object
 *
 * This is the implementation of the entrada object
 * This functions handle the acepting of cars into the queue
 *
 * @author Emmanuel Madrigal
 * @author Jonatan Chaverri
 * @author Mauricio Montero
 *
 * @bug No known bugs
 *
*/

#include <entrada.h>

struct Entrada* crearEntrada(int paramsGen[3], struct Puente* puente, struct Scheduler* scheduler, struct ControladorEntrada* ctrl){
	struct Entrada* entrada = malloc(sizeof(struct Entrada));
	
	entrada->semaforoEntrada  = 1;
	
	entrada->ctrl = ctrl;
	
	//TODO initialize the car generator here
	crearGenerador(paramsGen[0], paramsGen[1], paramsGen[2], entrada, puente, scheduler);

	return entrada;
}







