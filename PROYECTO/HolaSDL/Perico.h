#pragma once
#include "GameObject.h"
class Perico: public GameObject
{
public:
	Perico();
	virtual ~Perico();
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);
	virtual void handleInput(Uint32 time, const SDL_Event& event);

	void doAnimation() {} //PLACEHOLDER, queremos una funci�n as� en la clase
};

