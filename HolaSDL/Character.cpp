#include "Character.h"



Character::Character(SDLGame* game, double width, double height, Vector2D pos, int i) :
	GameObject(game)
{
	setWidth(width);
	setHeight(height);
	setPosition(pos);
	setVelocity(Vector2D(0, 0));


	animation = *getGame()->getServiceLocator()->getTextures()->getAnimation(i);
	
	isAnimationSyncedToMusic = true;
	animation.currentFrame = 1;
}


Character::~Character()
{
}

bool Character::handleInput(Uint32 time, const SDL_Event& event) {

	return false;
}

void Character::update(Uint32 time) {


}

