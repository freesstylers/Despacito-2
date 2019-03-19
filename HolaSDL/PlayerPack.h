#pragma once
#include "Point.h"
#include "Note.h"
#include "Squares.h"
#include "Vector2D.h"
#include "GameObject.h"
#include <list>
class PlayerPack : public GameObject
{
protected:
	Vector2D leftNotesVector;
	Vector2D rightNotesVector;
	Point* leftPoint;
	Point* rightPoint;
	Squares* leftNoteBar;
	Squares* rightNoteBar;

public:
	PlayerPack();
	PlayerPack(SDLGame* manager, int leftNotesPos, int rightNotesPos, int pointSize, int squareWidth);
	~PlayerPack();
	virtual void render(Uint32 time, bool beatSync);
	virtual void update(Uint32 time);
	virtual bool handleInput(Uint32 time, const SDL_Event& event);
	Point* getLeftPoint() { return leftPoint; }
	Point* getRightPoint() { return rightPoint; }
	std::list<Note*> screenArrows_;
	std::list<Note*> screenButtons_;

};
