#pragma once
#include "MiniGame.h"
#include "ScoreBar.h"
#include "GameObject.h"

class PlayState;

class LevelInputManager
{
public:
	LevelInputManager(PlayState* l, int numctrl);
	~LevelInputManager();

	void handleInput(Uint32 time, const SDL_Event& event);

	bool getFailed() { return failed; }

	void update();

	void setMinigameActive(bool active) { 
		minigameActive = active;
	}
private:
	int numctrl_;
	bool failed = false;
	bool minigameActive = false;
	const Uint8 *keystates;
	bool keyup = true;
	bool keyup2 = true;
	bool pressed = false;
	PlayState* level;
	SDL_GameController* controller = NULL;
	
};

