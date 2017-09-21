/** @file puente.c
 *  @brief Implementation for the puente controller
 *
 * This is the implementation of the puente controller
 * This funcitions handle the movement of cars on the bridge
 * and recieving and sending them to either part of the bridge
 * Its also responsable for knowing the direction of the bridge flow
 *
 * @author Emmanuel Madrigal
 * @author Jonatan Chaverri
 * @author Mauricio Montero
 *
 * @bug No known bugs
 *
*/

#include <puente.h>

struct Puente* createPuente(int largo, unsigned char tipo[2], unsigned char tiempo[2], unsigned char maxCarros[2], unsigned char paramsGen[6]){
	struct Puente* puente = malloc(sizeof(struct Puente));
	puente->largo = largo;
	puente->flujo = 0;
	
	puente->entradaIzquierda = createControlador(tipo[0], tiempo[0], maxCarros[0], puente, paramsGen);
	puente->entradaDerecha   = createControlador(tipo[1], tiempo[1], maxCarros[1], puente, (paramsGen + 3));
	
	//Esto es una serie de punteros hacia los carros
	puente->espacios = malloc(sizeof(struct Carro)*largo);
	
	return puente;
}

void avanzarCarros(struct Puente* puente){
	//TODO implement this
}


int recibirCarro(struct Puente* puente, char direccion, struct Carro* carro){
	//TODO implement this
	
	return 0;
}
