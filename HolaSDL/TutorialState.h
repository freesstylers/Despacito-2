#pragma once
#include "PlayState.h"
#include "checkML.h"

class GameManager;

class TutorialState :
	public PlayState
{
private:
	double pauseAmount = 6;

	//general
	EmptyObject* tutorialBox;
	EmptyObject* tutoFiltro;

	//first stop
	EmptyObject* note1;
	EmptyObject* note2;
	EmptyObject* note3;
	EmptyObject* circle1;
	EmptyObject* circle2;

	//second stop
	EmptyObject* barraPuntos;

	//third stop
	EmptyObject* barraAmarilla;
	EmptyObject* nota;

	//fourth stop
	EmptyObject* bomba;

	int auxTime = 0;
	int numStops = 0;
	int tutorialBoxAnim = Resources::AButton1;
	bool isTutorialPaused = false;
	SDL_GameController* controller = NULL;

public:
	TutorialState(GameManager* g);
	~TutorialState();

	virtual void restart();
	virtual void exit();
	virtual void update(Uint32 time);
	virtual bool handleEvent(Uint32 time, SDL_Event e);
	virtual bool pauseTutorial();
	virtual void resumeTutorial(GameManager* g, unsigned int timePaused);

};

