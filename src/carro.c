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
	int quantum = 250000;//250ms
	
	while(1){
		usleep(quantum);
		
		//printf("%p\t%p\t %d\n", carro->scheduler->owner,  carro, (carro->scheduler->owner == carro));
		//Car is on the ready queue
		if(carro->scheduler->owner == carro){
			//If not on bridge
			if(carro->position < 0){
				if(carro->entrada->semaforoEntrada == 1){
					//This function takes charge of changing the position so the correct data is represented
					enviarCarro(carro->entrada->ctrl, carro);
				}
				else if((carro->tipo == 2)){
					askSemaforo(carro->puente);
				}
			}
			
			//If on bridge
			if(carro->position >= 0){
				//Advance as far as it can
				for(int i = 0; i < carro->velocidad; i++){
					//De izquierda a derecha
					if(carro->direccion == 1){
						//El carro se encuentra al final del puente y ya puede salir
						if((carro->position + 1) > (carro->puente->largo -1)){
							carro->puente->espacios[carro->position] = 0;

							aceptarCarro(carro->puente->entradaDerecha);

							pthread_t thread = carro->responsibleThread;
							
							carDone(carro->scheduler, carro);
							free(carro);
							
							//mythread_exit(&thread);	
							pthread_exit(&thread);
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
							carro->puente->espacios[0] = 0;
							aceptarCarro(carro->puente->entradaIzquierda);

							pthread_t thread = carro->responsibleThread;
							
							carDone(carro->scheduler, carro);
							free(carro);
							
							//mythread_exit(&thread);
							pthread_exit(&thread);
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
				//TODO log if it made any changes
			}
		}
		
		//Car is on the waiting queue, check if resource is available
		else{
			//If resource is available
			if(checkResource(carro->puente, carro->entrada->ctrl->side, carro->position))
				upgradeQueue(carro->scheduler, carro);
			//If resource is not available
			else
				downgradeQueue(carro->scheduler, carro);
		}
			
	}
}
