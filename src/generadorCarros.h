#include <carro.h>
#include <entrada.h>

struct GeneradorCarros{
	unsigned char media;
	unsigned char ambulancias; //Porcentaje de ambulancias
	unsigned char radioactivos; //Porcentaje de carros radioactivos
	
	Entrada* entrada;
};

//FIXME esta función podría ser llamada por un hilo para que automáticamente se agreguen los carros a la cola
void generarCarro(GeneradorCarros generador);
