/** @file main.c
 *  @brief main function
 *
 * This file contains the main file in charge of the base object creation
 *
 * @author Emmanuel Madrigal
 * @author Jonatan Chaverri
 * @author Mauricio Montero
 *
 * @bug No known bugs
 *
*/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <libconfig.h>


#include <puente.h>


int main(){
	config_t cfg;	
	
	config_init(&cfg);
	
	FILE * file;
	file = fopen("params.conf", "r");
	if (file){
	   fclose(file);
	   config_read_file(&cfg, "params.conf");
	}
	else{
		return 0;
	}
		

	int numBridges = 0;
	config_lookup_int(&cfg, "application.bridgeNumber", &numBridges);
	
	config_setting_t *setting =  config_lookup(&cfg, "application.puentes");
			

	for(int i = 0; i < config_setting_length(setting); ++i){
		config_setting_t *bridge = config_setting_get_elem(setting, i);

		int largo;
		int tipo[2];
		int tiempo[2];
		int maxCarros[2];
		int paramsGen[6];
		
		const char *sched;
		unsigned char scheduler;
		
		const char *left;
		const char *right;
		
		config_setting_t *leftGen = config_setting_get_member(bridge, "generatorLeft");
		config_setting_t *rightGen = config_setting_get_member(bridge, "generatorRight");


		if(!(config_setting_lookup_int(bridge, "largo", &largo)
			&& config_setting_lookup_string(bridge, "scheduler",  &sched)
			&& config_setting_lookup_string(bridge, "controllerLeft",  &left)
			&& config_setting_lookup_string(bridge, "controllerRight", &right)
			&& config_setting_lookup_int(bridge, "timeLeft",        (tiempo))
			&& config_setting_lookup_int(bridge, "timeRight",       (tiempo+1))
			&& config_setting_lookup_int(bridge, "maxCarrosLeft",   (maxCarros))
			&& config_setting_lookup_int(bridge, "maxCarrosRight",  (maxCarros+1))
			
			&& config_setting_lookup_int(leftGen, "time",        (paramsGen))
			&& config_setting_lookup_int(leftGen, "ambulances",  (paramsGen+1))
			&& config_setting_lookup_int(leftGen, "radioactive", (paramsGen+2))
			
			&& config_setting_lookup_int(rightGen, "time",        (paramsGen+3))
			&& config_setting_lookup_int(rightGen, "ambulances",  (paramsGen+4))
			&& config_setting_lookup_int(rightGen, "radioactive", (paramsGen+5))
			)){
				printf("param not found\n");		
				continue;
		}
		printf("creating bridge\n");
			
		if(strcmp(left, "traffic light"))
			tipo[0] = 0;
		else if(strcmp(left, "traffic officer"))
			tipo[0] = 1;
		else
			tipo[0] = 2;
			
		if(strcmp(right, "traffic light"))
			tipo[1] = 0;
		else if(strcmp(right, "traffic officer"))
			tipo[1] = 1;
		else
			tipo[1] = 2;
			
		if(strcmp(sched, "FIFO"))
			scheduler = 0;
		else if(strcmp(sched, "PRIORITY"))
			scheduler = 1;
		else if(strcmp(sched, "SJF"))
			scheduler = 2;
		else if(strcmp(sched, "RR"))
			scheduler = 3;
		else if(strcmp(sched, "RT"))
			scheduler = 4;
		else
			scheduler = 0;
		
			
		createPuente(largo, tipo, tiempo, maxCarros, paramsGen, i, scheduler);

	}
	
	//TODO print bridge loop, used for sending data to the arduino


    //Run for 1h
    usleep(3600000000);
	
	
	return 0;
}
