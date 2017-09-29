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

struct Entrada* crearEntrada(unsigned char paramsGen[3], struct Puente* puente, struct ControladorEntrada*  controlador){
	struct Entrada* entrada = malloc(sizeof(struct Entrada));
	
	entrada->colaCarros       = NULL;
	entrada->colaAmbulancias  = NULL;
	entrada->colaRadioactivos = NULL;
	entrada->semaforoEntrada  = 1;
	
	entrada->ctrl             = controlador;
	
	
	//TODO initialize the car generator here
	
	entrada->generador = crearGenerador(paramsGen[0], paramsGen[1], paramsGen[2], entrada, puente);


	return entrada;
}


struct Carro* getCarro(struct Entrada* entrada){
	//TODO add multiple queues
	
	//Only if green light
	if(entrada->semaforoEntrada){
		if(g_list_length(entrada->colaRadioactivos) > 0)
			//Return radioactive car
			return g_slist_nth_data(entrada->colaRadioactivos, 0);
		if(g_list_length(entrada->colaAmbulancias) > 0)
			//Return ambulance
			return g_slist_nth_data(entrada->colaAmbulancias, 0);
		//If there are cars waiting
		if(g_list_length(entrada->colaCarros) > 0)
			//Return car
			return g_slist_nth_data(entrada->colaCarros, 0);
	}

	return 0;
}

void agregarCarro(struct Entrada* entrada, struct Carro* carro){
	if(carro->tipo == 0)
		entrada->colaCarros = g_slist_append (entrada->colaCarros, carro);
	else if(carro->tipo == 1)
		entrada->colaCarros = g_slist_append (entrada->colaAmbulancias, carro);
	else if(carro->tipo == 2)
		entrada->colaCarros = g_slist_append (entrada->colaRadioactivos, carro);
	
}


int buscarCarro(GSList *colaCarros, struct Carro* carro){
	GSList* iterator = colaCarros;
	
	/*
	//HACK this isnt actual search but since in the algorithm it only matters when it is 0, the only check made is for the first element
	if(carro == iterator->data)
		return 0;
	else
		return -1;
	*/
	
	int i = 0;
	char found = 0;
	for (; iterator; iterator = iterator->next) {
		if(carro == iterator->data){
			found = 1;
			break;
		}
		i++;
	}
	if(found)
		return i;
	else
		return -1;
	
	
}





