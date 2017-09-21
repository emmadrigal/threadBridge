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
	
	entrada->colaCarros = g_array_new (FALSE, FALSE, sizeof (struct Carro));;
	entrada->semaforoEntrada = 0;
	
	
	//TODO initialize the car generator
	
	entrada->generador = crearGenerador(paramsGen[0], paramsGen[1], paramsGen[2], entrada);


	return entrada;
}


void agregarCarro(struct Entrada* entrada, struct Carro carro){
	g_array_append_val (entrada->colaCarros, carro);
	
	printf("There are now %d cars waiting\n", entrada->colaCarros->len);
}
