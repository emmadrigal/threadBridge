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
	
	while(1){
		//TODO get this number from config file
		usleep(100000);
		
		
		//Si ya se encuentra en el puente
		if(carro->position >= 0){
			//Advance as far as it can
			for(int i = 0; i < carro->velocidad; i++){
				//De izquierda a derecha
				if(carro->direccion == 1){	
					//El carro se encuentra al final del puente y ya puede salir
					if((carro->position + 1) > (carro->puente->largo -1)){
						carro->puente->espacios[carro->position] = 0;
						
						aceptarCarro(carro->puente->entradaDerecha);
						break;
						//TODO matar el loop de while(1)
						//TODO liberar memoria
					}
					//La posición de adelante está libre
					else if(carro->puente->espacios[carro->position + 1] == 0){
						carro->puente->espacios[carro->position] = 0;
						carro->puente->espacios[carro->position + 1] = carro;
						carro->position++;
					}
					//Hay un carro adelante, no puede avanzar más
					else{
						break;
					}
				}
				
				//De derecha a izquierda
				else if(carro->direccion == -1){
					//El carro se encuentra al final del puente y ya puede salir
					if((carro->position - 1) < 0){
						carro->puente->espacios[carro->position] = 0;
						
						aceptarCarro(carro->puente->entradaIzquierda);
						
						break;
						//TODO matar el loop de while(1)
						//TODO liberar memoria
					}
					//La posición de adelante está libre
					else if(carro->puente->espacios[carro->position - 1] == 0){
						carro->puente->espacios[carro->position] = 0;
						carro->puente->espacios[carro->position - 1] = carro;
						carro->position--;
					}
					//Hay un carro adelante, no puede avanzar más
					else{
						break;
					}
				}
			}
		}
		
		//Si todavía se encuentra en una entrada
		else{			
			//Si el carro es radioactivo y es el primero en la cola
			if((buscarCarro(carro->entrada->colaRadioactivos, carro) == 0) && (carro->tipo == 2)){
				//TODO solicitar el cambio de semáforo aquí
				enviarCarro(carro->entrada->ctrl, carro);
			}
			//Si la lista de radioactivos está vacia otros carros pueden avanzar
			else if(g_slist_length(carro->entrada->colaRadioactivos) == 0){
				//Si el carro es una ambulancia y es el primero en la cola
				if((buscarCarro(carro->entrada->colaAmbulancias, carro) == 0)  && (carro->tipo == 1)){
					enviarCarro(carro->entrada->ctrl, carro);
				}
				//Si la lista de ambulancias está vacia otros carros pueden avanzar
				else if(g_slist_length(carro->entrada->colaAmbulancias) == 0){
					//Si el carro es el primero en la lista
					if(buscarCarro(carro->entrada->colaCarros, carro) == 0){
						enviarCarro(carro->entrada->ctrl, carro);	
					}
				}
			}
		}
	}
}
