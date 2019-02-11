#include "Flechas.h"


Flechas::Flechas()
{

}
Flechas::Flechas(SDL_Keycode key, SDLGame* game, double width, double height, Vector2D pos, Vector2D vel) :
	GameObject(game), texture(texture), key(key)
{
	setWidth(width);
	setHeight(height);
	setPosition(pos);
	setVelocity(vel);
	texture = getGame()->getServiceLocator()->getTextures()->getTexture(Resources::Flecha);
}

Flechas::~Flechas()
{

}

int Flechas::handleInput(Uint32 time, const SDL_Event& event, const GameObject& pulsador) {

	/*if(tecla correcta) --> par�metro pasado en su creaci�n?
	{
		return pulsador.checkAccuracy( posici�n Y );
	}

	else
		return 0; (es fallido)
	*/

	//el valor del return se tomar� en playstate para calcular los puntos a�adidos
}

void Flechas::update(Uint32 time) {
	position_.set(position_ + velocity_);
	if (position_.getX() < getGame()->getWindowWidth())
	{
		
	}
}

void Flechas::render(Uint32 time) {
	texture->render(getRect());
}

