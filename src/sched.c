

void carDone(struct Scheduler* scheduler, struct Carro* carro){
	//Car is done, must free data??
	g_slist_remove(scheduler->colaReady, carro);
	
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
			//Goes though all cars, EDF and if no deadline FIFO
			//TODO iterate over all cars and if it has deadline(Radioactive or Ambulance)
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

//Only works on RR, all others are only called when cars start or end
void* setCurrentOwner(struct Scheduler* scheduler){
	//Every quantum(needs to get it from the config file) sends the actual to the end of the list and new first is the second
	int quantum = 100000;//100ms
	while(1){
		usleep(quantum);
		//Only try if the list isn't empty
		if(g_slist_length(scheduler->colaReady) != 0){
				//Takes first away from the list
				scheduler->colaReady = g_slist_remove(scheduler->colaReady, carro);
				
				//Puts it back at the end of the list
				g_slist_append(scheduler->colaReady, scheduler->owner);
				
				//New first of the list advances
				scheduler->owner = scheduler->data;
		}
		
	}
}
