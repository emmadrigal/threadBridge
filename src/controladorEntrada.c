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

struct ControladorEntrada* createControlador(unsigned char tipo, unsigned char tiempo, unsigned char maxCarros, struct Puente* puente, unsigned char paramsGen[3], char lado){
	struct ControladorEntrada* controlador = malloc(sizeof(struct ControladorEntrada));
	controlador->puente = puente;
	
	controlador->entrada = crearEntrada(paramsGen);
	controlador->side = lado;
	
	return controlador;
}


void updateSemaforo(struct ControladorEntrada* ctrl){
	//TODO implement this
}

void aceptarCarro(struct ControladorEntrada* ctrl){
	//TODO put mutex lock on this
	ctrl->carrosAceptados++;
}

void enviarCarro(struct ControladorEntrada* ctrl){
	struct Carro* carro = getCarro(ctrl->entrada);
	char aceptado = recibirCarro(ctrl->puente, ctrl->side, carro);
	
	//FIXME this could be done in a function inside entrada
	if(aceptado)
		ctrl->entrada->colaCarros = g_list_remove(ctrl->entrada->colaCarros, carro);
}

void updateCola(struct ControladorEntrada* ctrl){
	//TODO implement this
}
