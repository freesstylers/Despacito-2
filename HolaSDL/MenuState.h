#pragma once
#include "GameState.h"

class MenuState : public GameState //Clase general para menus, he dejado los m�todos est�ticos para hacer los callbacks
{
public:
	MenuState(Game* g);
	~MenuState();

	static void play(Game * game);
	static void load(Game* game);
	static void exit(Game* game);

private:
	Game* game;
};