#include "Note.h"

Note::Note(SDL_GameControllerButton key, SDLGame* game, double width, double height, Vector2D pos, Vector2D vel, bool isXbox) :
	GameObject(game), key(key)
{
	setWidth(width);
	setHeight(height);
	setPosition(pos);
	setVelocity(vel/1000.0);
	changeController(isXbox); //Xbox controller by default, as it's the official controller for PC
}

Note::~Note()
{
	game_ = nullptr;
}

void Note::update(Uint32 time) {
	double deltaTime = getGame()->deltaTime;
	position_.set(position_ + velocity_ * deltaTime);
}

void Note::changeController(bool isXbox) //Animation changed between Xbox controller and PlayStation controller layouts
{
	if (isXbox) {
		switch (key) {
		case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
			animation = *getGame()->getServiceLocator()->getTextures()->getAnimation(Resources::LeftArrow);
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
			animation = *getGame()->getServiceLocator()->getTextures()->getAnimation(Resources::RightArrow);
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_UP:
			animation = *getGame()->getServiceLocator()->getTextures()->getAnimation(Resources::UpArrow);
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
			animation = *getGame()->getServiceLocator()->getTextures()->getAnimation(Resources::DownArrow);
			break;
		case SDL_CONTROLLER_BUTTON_A:
			animation = *getGame()->getServiceLocator()->getTextures()->getAnimation(Resources::AButton);
			break;
		case SDL_CONTROLLER_BUTTON_B:
			animation = *getGame()->getServiceLocator()->getTextures()->getAnimation(Resources::BButton);
			break;
		case SDL_CONTROLLER_BUTTON_X:
			animation = *getGame()->getServiceLocator()->getTextures()->getAnimation(Resources::XButton);
			break;
		case SDL_CONTROLLER_BUTTON_Y:
			animation = *getGame()->getServiceLocator()->getTextures()->getAnimation(Resources::YButton);
			break;
		case SDL_CONTROLLER_BUTTON_INVALID:
			animation = *getGame()->getServiceLocator()->getTextures()->getAnimation(Resources::FlechaEspBomba);
			break;
		}
	}
	else {
		switch (key) {
		case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
			animation = *getGame()->getServiceLocator()->getTextures()->getAnimation(Resources::LeftArrowPlay);
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
			animation = *getGame()->getServiceLocator()->getTextures()->getAnimation(Resources::RightArrowPlay);
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_UP:
			animation = *getGame()->getServiceLocator()->getTextures()->getAnimation(Resources::UpArrowPlay);
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
			animation = *getGame()->getServiceLocator()->getTextures()->getAnimation(Resources::DownArrowPlay);
			break;
		case SDL_CONTROLLER_BUTTON_A:
			animation = *getGame()->getServiceLocator()->getTextures()->getAnimation(Resources::XButtonPlay);
			break;
		case SDL_CONTROLLER_BUTTON_B:
			animation = *getGame()->getServiceLocator()->getTextures()->getAnimation(Resources::BButtonPlay);
			break;
		case SDL_CONTROLLER_BUTTON_X:
			animation = *getGame()->getServiceLocator()->getTextures()->getAnimation(Resources::SquareButtonPlay);
			break;
		case SDL_CONTROLLER_BUTTON_Y:
			animation = *getGame()->getServiceLocator()->getTextures()->getAnimation(Resources::TriangleButtonPlay);
			break;
		case SDL_CONTROLLER_BUTTON_INVALID:
			animation = *getGame()->getServiceLocator()->getTextures()->getAnimation(Resources::FlechaEspBomba);
			break;
		}
	}
}


