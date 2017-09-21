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
	
	puente->entradaIzquierda = createControlador(tipo[0], tiempo[0], maxCarros[0], puente, paramsGen,        1);
	puente->entradaDerecha   = createControlador(tipo[1], tiempo[1], maxCarros[1], puente, (paramsGen + 3), -1);
	
	//Esto es una serie de punteros hacia los carros
	puente->espacios = calloc(sizeof(struct Carro*)*largo, largo);
	
	return puente;
}

void avanzarCarros(struct Puente* puente){
	//TODO esto debería de estar dentro de un loop y refresecarse automáticamente

	//Último espacio libre desde la dirección que se está evaluando
	unsigned int furthestFree = 0;
	
	//FIXME puede que en lugar de 2if dentro de for, 2for dentro de 2if sea más eficiente
	for(int i = 0; i < puente->largo; i++){
		if(puente->flujo == 0)//Si no hay carros en el puente
			break;
		
		//Carros moviendose a la izquierda
		else if(puente->flujo == 1){
			if(puente->espacios[i] != 0){ //Si el espacio no está vacio
				int reach = i - puente->espacios[i]->velocidad;//Que tan lejos puede llegar
				if(furthestFree <= reach){//Si puede avanzar su max
					//Move hasta reach
					puente->espacios[reach] =  puente->espacios[i];
					puente->espacios[i]     =  0;

					//Se actualiza lo más lejos que se puede avanzar
					furthestFree = reach+1; 
				}
				else if((furthestFree == 0) && (reach < 0)){//Si puede salida del puente
					//Libera el espacio actual
					puente->espacios[i] = 0;
					
					//Saca el carro del puente
					aceptarCarro(puente->entradaIzquierda);
					
					//TODO liberar la memoria de carro
				}
				else if(furthestFree > reach){//Si no puede llegar hasta su alcance max
					//Mueve el carro a su alcance máximo
					puente->espacios[furthestFree] =  puente->espacios[i];
					puente->espacios[i]            =  0;
					
					//Se actualiza lo más lejos que se puede avanzar
					furthestFree = furthestFree+1;
				}
			}
		}
		
		//Carros moviendose a la derecha
		else if(puente->flujo == -1){
			if(puente->espacios[puente->largo -1 - i] != 0){ //Si el espacio no está vacio
				int reach = i - puente->espacios[puente->largo -1 - i]->velocidad;//Que tan lejos puede llegar
				if(furthestFree <= reach){//Si puede avanzar su max
					//Move hasta reach
					puente->espacios[puente->largo -1 - reach] =  puente->espacios[puente->largo -1 - i];
					puente->espacios[puente->largo -1 - i]     =  0;

					//Se actualiza lo más lejos que se puede avanzar
					furthestFree = reach+1; 
				}
				else if((furthestFree == 0) && (reach < 0)){//Si puede salid del puente
					//Libera el espacio actual
					puente->espacios[puente->largo -1 - i] = 0;
					
					//Saca el carro del puente
					aceptarCarro(puente->entradaDerecha);
					
					//TODO liberar la memoria de carro
				}
				else if(furthestFree > reach){//Si no puede llegar hasta su alcance max
					//Mueve el carro a su alcance máximo
					puente->espacios[puente->largo -1 - furthestFree] =  puente->espacios[puente->largo -1 - i];
					puente->espacios[puente->largo -1 - i]            =  0;
					
					//Se actualiza lo más lejos que se puede avanzar
					furthestFree = furthestFree+1; 
				}
			}
		}
	}
	
	//No hay más carros en el puente
	if(furthestFree == 0)
		puente->flujo = 0;
	
}

int min(int a, int b){
	if(a < b)
		return a;
	return b;
}


int recibirCarro(struct Puente* puente, char direccion, struct Carro* carro){
	if(puente->flujo == 0){//Si no hay carros en el puente
		//Si se recibe un carro de la derecha
		if(direccion == -1){
			puente->espacios[puente->largo - carro->velocidad];
			puente->flujo = -1;
		}
		//Si se recibe un carro de la izquierda
		else if(direccion == 1){
			puente->espacios[carro->velocidad - 1];
			puente->flujo = 1;
		}
		return 1;
	}
			
	//Hay carros llendo en la otra dirección
	else if(puente->flujo != direccion)
		return 0;
	
	else{
		int furthestFree = 0;
		int reach        = carro->velocidad - 1;
		int evaluaciones = min(reach ,puente->largo)	;
	
		for(int i = 0; i < evaluaciones; i++){
			//Flujo hacia la izquierda
			if(puente->flujo == 1)
				//Cuando se encuentre el 1er carro en la calle
				if(puente->espacios[puente->largo -1 - i] != 0){
					//Si el primer espacio está libre
					if(i != 0){
						puente->espacios[puente->largo - i] = carro;
						return 1;
					}
					break;
				}

			//Flujo hacia la derecha
			else if(puente->flujo == -1)
				//Cuando se encuentre el 1er carro en la calle
				if(puente->espacios[i] != 0){
					//Si el primer espacio está libre
					if(i != 0){
						puente->espacios[i - 1] = carro;
						return 1;
					}
					break;
				}
			furthestFree = i;
		}
		//This means that there is a car on the first position
		return 0;
	}
	
	return 0;
}
