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

struct Entrada* crearEntrada(unsigned char paramsGen[3]){
	struct Entrada* entrada = malloc(sizeof(struct Entrada));
	
	entrada->colaCarros = NULL;
	entrada->semaforoEntrada = 0;
	
	
	//TODO initialize the car generator here
	
	entrada->generador = crearGenerador(paramsGen[0], paramsGen[1], paramsGen[2], entrada);


	return entrada;
}


struct Carro* getCarro(struct Entrada* entrada){
	return g_slist_nth_data(entrada->colaCarros, 0);
}

void agregarCarro(struct Entrada* entrada, struct Carro* carro){
	entrada->colaCarros = g_slist_append (entrada->colaCarros, carro);
	
	printf("There are now %d cars waiting\n", g_slist_length (entrada->colaCarros));
}
