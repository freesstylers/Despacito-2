#include "Pulsador.h"



Pulsador::Pulsador()
{
}


Pulsador::~Pulsador()
{
}

void Pulsador::handleInput(Uint32 time, const SDL_Event& event) {	// �handleinput en flechas?


}

int Pulsador::checkAccuracy(double xPosition) {
	//comprueba la precisi�n de la nota en la posici�n incluida como par�metro, devuelve un valor int que determina la precisi�n
	//0 bad, 1 good, 2 perfect? Y playstate calcula la puntuaci�n a partir de este valor seg�n la canci�n

	//esta funci�n es llamada por la flecha desde su handleInput
}

void Pulsador::update(Uint32 time) {


}

void Pulsador::render(Uint32 time) {


}
