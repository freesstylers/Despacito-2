#pragma once

#include <string>

#include"Vector2D.h"
#include"SRandBasedGenerator.h"


using namespace std;

class PlayState;
class SDLGame;

class Level
{
public:
	Level(PlayState* l, SDLGame* gam, string n);
	~Level();

	void playSong();

	void init();

	int bpm;
	int probqte;
	double songLength;
	int song;
	int maxScore;
	int noteAmount;
	SRandBasedGenerator random;

protected:
	string name;
	Vector2D noteVel;

	PlayState* level;
	SDLGame* gm;
};

