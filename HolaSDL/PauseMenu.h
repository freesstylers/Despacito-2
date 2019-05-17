#pragma once
#include "GameObject.h"
#include "EmptyObject.h"
#include "Timer.h"
#include "TextObject.h"
#include <list>
#include <string>
#include "checkML.h"

//Pause menu during levels

class TutorialState;
class PlayState;

class PauseMenu :
	public GameObject
{
private:
	bool isXbox;

	Timer* timer;
	SDL_GameController* controller = NULL;

	PlayState* level;

	EmptyObject* bg;
	EmptyObject* options;
	EmptyObject* resume;
	EmptyObject* restart;
	EmptyObject* exit;

	EmptyObject* op_bg;
	EmptyObject* music;
	EmptyObject* musicSelect;
	EmptyObject* sounds;
	EmptyObject* soundsSelect;
	EmptyObject* controls;
	EmptyObject* controlsSelect;
	EmptyObject* op_exit;

	EmptyObject* selection;

	TextObject* musicTxt;
	TextObject* soundTxt;
	TextObject* controlTxt;

	vector<EmptyObject*> menuButtons;
	vector<EmptyObject*> optionsButtons;

	int selectedButton = 0;
	bool optionsOpen = false;

	void resumeSong();
	void toggleOptions();
	void restartSong();
	void exitSong();
	void updateMusic(bool raise);
	void updateSound(bool raise);
	
	void updateTxt();

public:
	PauseMenu(SDLGame* game, PlayState* ps, bool isXbox);
	~PauseMenu();

	void activate();
	void updateControls();

	virtual bool handleInput(Uint32 time, const SDL_Event& event);
	virtual void update(Uint32 time) {};
	virtual void render(Uint32 time, bool beatSync = false);
};