#pragma once
#include "GameObject.h"
#include "checkML.h"

//Objeto que s�lo posee un sprite

class EmptyObject :
	public GameObject
{
public:
	EmptyObject() {}
	EmptyObject(SDLGame* game, Vector2D pos, int width, int height, int textura);
	virtual bool handleInput(Uint32 time, const SDL_Event& event) { return false; };
	virtual void update(Uint32 time) {};
	virtual void render(Uint32 time, bool beatSync = true);
	void changeFrame();
	virtual ~EmptyObject();
};

