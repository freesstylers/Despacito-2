#pragma once
#include <stack>
#include "GameState.h"
#include "checkML.h"

using namespace std;

class GameStateMachine
{
public:
	stack<GameState*> stack;

	GameStateMachine();
	~GameStateMachine();

	GameState* currentState();
	void changeState(GameState* state);
	void pushState(GameState* state);
	void popState();
};

