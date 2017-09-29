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
	
	controlador->puente  = puente;
	controlador->entrada = crearEntrada(paramsGen, puente, controlador);
	controlador->side    = lado;
	
	controlador->tipo      = tipo;
	controlador->tiempo    = tiempo;
	controlador->maxCarros = maxCarros;
	
	//If it isn't jungle law, traffic lights must be different
	if(controlador->tipo != 2)
		//If this is the left side
		if(controlador->side == 1)
			//Change the value of the light
			controlador->entrada->semaforoEntrada = 0;
	
	
	controlador->carrosAceptados = 0;
	controlador->carrosEnviados  = 0;
	
	return controlador;
}


void updateSemaforo(void* entrance){
	struct ControladorEntrada* ctrl = (struct ControladorEntrada*) entrance;
	
	clock_t start_t, end_t;
	
	start_t = clock();
		
	while(1){
		//TODO get this value from config file??
		usleep(100000);
		
		//Traffic Light
		if(ctrl->tipo == 0){
			//Get current time and compare to last update
			end_t = clock();
			double elapsedTime = (double)(end_t - start_t) / CLOCKS_PER_SEC * 1000;
			if(elapsedTime > ctrl->tiempo){
				//Last change to the traffic light is now
				start_t = end_t;
				
				//Change the state of the traffic lights
				ctrl->entrada->semaforoEntrada = ctrl->entrada->semaforoEntrada^1;			
			}
		}
		//Traffic Officer
		else if(ctrl->tipo == 1){
			//If count se excedió
			if(ctrl->carrosAceptados > ctrl->maxCarros){
				ctrl->carrosAceptados = 0;

				ctrl->entrada->semaforoEntrada = ctrl->entrada->semaforoEntrada^1;
				
			}
			else if(ctrl->carrosEnviados > ctrl->maxCarros){
				ctrl->carrosEnviados = 0;

				ctrl->entrada->semaforoEntrada = ctrl->entrada->semaforoEntrada^1;
			
			}
			else if(ctrl->puente->flujo == 0){
				ctrl->carrosAceptados = 0;
				ctrl->carrosEnviados = 0;
				
				ctrl->entrada->semaforoEntrada = ctrl->entrada->semaforoEntrada^1;
			}
		}
		//Jungle Law
		else if(ctrl->tipo == 2){
			//Traffic light is always on, pass is determined if the bridge is free
			//FIXME si el tipo es 2, se podría salir del loop inmediatamente
		}
	}
	
}

void aceptarCarro(struct ControladorEntrada* ctrl){
	//TODO put mutex lock on this
	ctrl->carrosAceptados = ctrl->carrosAceptados + 1;
}

char enviarCarro(struct ControladorEntrada* ctrl, struct Carro* carro){
	//TODO put mutex around this call to avoid multpli cars
	char aceptado = recibirCarro(ctrl->puente, ctrl->side, carro);

	

	//FIXME this could be done in a function inside entrada
	if(aceptado){
		if(carro->tipo == 2)
			ctrl->entrada->colaRadioactivos = g_list_remove(ctrl->entrada->colaRadioactivos,  carro);
		else if(carro->tipo == 1)
			ctrl->entrada->colaAmbulancias = g_list_remove(ctrl->entrada->colaAmbulancias, carro);
		else if(carro->tipo == 0){
			ctrl->entrada->colaCarros = g_list_remove(ctrl->entrada->colaCarros, carro);
		}
		
		//Indicar al carro que ahora se encuentra en la primera posición de espera
		if(ctrl->side == 1){
			carro->position = 0;
			carro->direccion = 1;
		}
		if(ctrl->side == -1){
			carro->position = ctrl->puente->largo -1;
			carro->direccion = -1;
		}
			
		ctrl->carrosEnviados++;
	}
	
	return aceptado;
	//This could call the update after sending data
}
