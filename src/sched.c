

void carDone(struct Scheduler* scheduler){
	switch(scheduler->method){
		case 0: //FIFO
			if(g_slist_length(scheduler->colaReady) != 0)
				scheduler->owner = scheduler->data; //Primero en la lista avanza
			break;
		case 1: //SJF
			//TODO iterate over all cars
			break;
		case 2: //Prioridad
			//TODO iterate over all cars
			break;
		case 3: //Round Robin
			if(g_slist_length(scheduler->colaReady) != 0)
				scheduler->owner = scheduler->data; //Primero en la lista avanza
				//TODO take control away after quantum
			break;
		case 4: //RT
			break;
		default:
			//Do nothing
			break;
	}

}



void addCar(struct Scheduler* scheduler, struct* Carro carro){
	//No car currently using the bridge, all may pass
	if(scheduler->owner == -1){
		scheduler->owner = carro;
	}
	else{
		//Adds car to ready in order for it to be scheduled when it is ready
		g_slist_append(scheduler->colaReady, carro);
	}
}


void* setCurrentOwner(struct Scheduler* scheduler){
	
}
