#include <entrada.h>
#include <puente.h>

/*
	tipo:
		0: semáforo
		1: oficial de tráfico
		2: ley de la jungla
*/
struct ControladorEntrada{
	unsigned char tipo;
	unsigned char tiempo;
	unsigned char maxCarros;
	
	Entrada entrada;
	Puente puente;
};

void updateSemaforo(struct ControladorEntrada ctrl);
void recibirCarro(struct ControladorEntrada ctrl);
void enviarCarro(struct ControladorEntrada ctrl);
void updateCola(struct ControladorEntrada ctrl);
