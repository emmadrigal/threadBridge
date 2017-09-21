/** @file controladorEntrada.c
 *  @brief Implementation for the entrada controller
 *
 * This is the implementation of the puente controller
 * This functions are responsable for allowing cars to advance to the bridge
 *
 * @author Emmanuel Madrigal
 * @author Jonatan Chaverri
 * @author Mauricio Montero
 *
 * @bug No known bugs
 *
*/

#include <controladorEntrada.h>

struct ControladorEntrada* createControlador(unsigned char tipo, unsigned char tiempo, unsigned char maxCarros, struct Puente* puente, unsigned char paramsGen[3]){
	struct ControladorEntrada* controlador = malloc(sizeof(struct ControladorEntrada));
	controlador->puente = puente;
	
	controlador->entrada = crearEntrada(paramsGen);
	
	return controlador;
}


void updateSemaforo(struct ControladorEntrada* ctrl){
	//TODO implement this
}

void aceptarCarro(struct ControladorEntrada* ctrl){
	//TODO implement this
}

void enviarCarro(struct ControladorEntrada* ctrl){
	//TODO implement this
}

void updateCola(struct ControladorEntrada* ctrl){
	//TODO implement this
}
