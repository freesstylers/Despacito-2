#pragma once
#include "GameObject.h"
class BarraPuntos : public GameObject
{
private:
	Texture*texture;
	int numNotas_;
	int maxBarra_;
public:
	BarraPuntos(SDLGame* game, double width, double height, Vector2D pos, int numNotas, int maxBarra);
	virtual bool handleInput(Uint32 time, const SDL_Event& event);
	virtual void update(Uint32 time);
	void avanza(int punt);
	virtual ~BarraPuntos();
};

