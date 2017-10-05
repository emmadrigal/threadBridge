


#include <sched.h>

struct Scheduler* createScheduler(unsigned char metodo){
	struct Scheduler* scheduler = malloc(sizeof(struct Scheduler));
	
	scheduler->colaReady = NULL;
	scheduler->colaWaiting = NULL;
	
	scheduler->owner = 0;
	
	scheduler->method = metodo;
	
	return scheduler;
}


void carDone(struct Scheduler* scheduler, struct Carro* carro){
	scheduler->colaReady = g_slist_remove(scheduler->colaReady, carro);
	scheduler->colaWaiting = g_slist_remove(scheduler->colaWaiting, carro);

	scheduler->owner = 0;
	
	
	//If there are cars that can be scheduled
	if(g_slist_length(scheduler->colaReady) != 0){
		switch(scheduler->method){
			case 0:{ //FIFO
				scheduler->owner = scheduler->colaReady->data; //Primero en la lista avanza
				break;
			}
			case 1:{ //SJF
				//Look for the fastest car
				struct Carro* fastest = scheduler->colaReady->data;
			
				GSList* iterator = scheduler->colaReady;

				for (; iterator; iterator = iterator->next) {
					struct Carro* tmp = iterator->data;
					if(tmp->velocidad > fastest->velocidad){
						fastest = iterator->data;
					}
				}
			
				scheduler->owner = fastest;
				break;
			}
			case 2:{ //Prioridad, en el orden de radioactivo->ambulancia->carro
				//Look for the fastest car
				struct Carro* highestPriority = scheduler->colaReady->data;
			
				GSList* iterator = scheduler->colaReady;

				for (; iterator; iterator = iterator->next) {
					struct Carro* tmp = iterator->data;
					//If a car has highest priority
					if(tmp->prioridad < highestPriority->prioridad){
						highestPriority = iterator->data;
					}
					//Apply aging to all cars
					tmp->prioridad--;
				}
			
				scheduler->owner = highestPriority;
				break;
			}
			case 3:{ //Round Robin
				scheduler->owner = scheduler->colaReady->data; //Primero en la lista avanza
				break;
			}
			case 4:{ //RT
				//Goes though all cars, EDF and if no deadline FIFO
				//TODO iterate over all cars and if it has deadline(Radioactive or Ambulance)
				break;
			}
			default:{
				//Do FIFO
				scheduler->owner = scheduler->colaReady->data; //Primero en la lista avanza
				break;
			}
		}
	}

}



void addCar(struct Scheduler* scheduler, struct Carro* carro){
	//TODO implementar cola multinivel al poner los carros especiales al principio de la cola
	
	if(scheduler->owner == 0){//No car currently using the bridge, whoever asks may pass
		scheduler->owner = carro;
		scheduler->colaReady = g_slist_append(scheduler->colaReady, carro);
	}
	else//Adds car to ready in order for it to be scheduled when it is ready
		//scheduler->colaWaiting = g_slist_append(scheduler->colaReady, carro);
		scheduler->colaReady = g_slist_append(scheduler->colaReady, carro);
}

//Only works on RR, all others are only called when cars start or end
void* setCurrentOwner(void* calendarizador){
	struct Scheduler* scheduler = (struct Scheduler*) calendarizador;

	//Every quantum(needs to get it from the config file) sends the actual to the end of the list and new first is the second
	int quantum = 100000;//100ms
	while(1){
		
		usleep(quantum);
		//Only try if the list isn't empty
		
		if(g_slist_length(scheduler->colaReady) != 0){
				
				//Takes first away from the list
				scheduler->colaReady = g_slist_remove(scheduler->colaReady, scheduler->owner);
				
				//Puts it back at the end of the list
				scheduler->colaReady = g_slist_append(scheduler->colaReady, scheduler->owner);
				
				//New first of the list advances
				scheduler->owner = scheduler->colaReady->data;
		}
	}
}


void downgradeQueue(struct Scheduler* scheduler, struct Carro* carro){

	if(g_slist_find (scheduler->colaReady,  carro) == NULL ){
		scheduler->colaReady = g_slist_remove(scheduler->colaReady, carro);
		scheduler->colaWaiting = g_slist_append(scheduler->colaWaiting, carro);
	}
	
}

void upgradeQueue(struct Scheduler* scheduler, struct Carro* carro){
	//Remove from waiting queue
	if(g_slist_length(scheduler->colaReady) == 0){
		scheduler->colaWaiting = g_slist_remove(scheduler->colaWaiting, carro);
		scheduler->owner = carro;
	}
	
	else if(g_slist_find (scheduler->colaReady,  carro) == NULL ){
		scheduler->colaWaiting = g_slist_remove(scheduler->colaWaiting, carro);
		scheduler->colaReady = g_slist_append(scheduler->colaReady, carro);
	}
}

