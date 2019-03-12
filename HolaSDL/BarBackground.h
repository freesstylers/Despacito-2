#pragma once
#include "GameObject.h"
class BarBackground : public GameObject
{
private:
	double vel_;
public:
	BarBackground(SDLGame* game, double width, double height, Vector2D pos, double vel, int texture);
	virtual bool handleInput(Uint32 time, const SDL_Event& event);
	virtual void update(Uint32 time) {};
	virtual ~BarBackground();
};
