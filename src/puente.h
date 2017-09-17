#include <controladorEntrada.h>
#include <carro.h>

/*
	flujo:
		 0: no hay carros
		 1: hacia la "derecha"
		-1: hacia la "izquierda"
*/
struct Puente{
	int largo;
	ControladorEntrada entradas[2];
	char flujo;
	Carro* espacios; //Esto representa una arreglo de tamaño "largo"
};

void avanzarCarros(struct Puente puente);
void updateDireccionFlujo(struct Puente puente);
int recibirCarro(struct Puente puente, char direccion, struct Carro carro);
