#include "QTEManager.h"
#include "PlayState.h"



QTEManager::QTEManager(PlayState* l, int proba)
{
	prob = proba;
	level = l;
	timer = Timer::Instance();
	timer->Reset();
}


QTEManager::~QTEManager()
{
}

void QTEManager::handleInput(Uint32 time, const SDL_Event& event) {
	if (flecha != nullptr)
	{
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == flecha->getKey()/* && keyup*/)
		{
			activo = false;
			cout << "ejej";
			delete(flecha);
			flecha = nullptr;
			timer->Reset();
		}
		//if (event.type == SDL_KEYUP) keyup = true;
	}

}

void QTEManager::update(Uint32 time) {
	timer->Update();
	if (timer->DeltaTime() > 0.5f && flecha == nullptr)
	{
		if (rand() % 1000 + 1 > 20 && rand() % 1000 + 1 < prob && !activo) {
			flecha = new Flechas(SDL_CONTROLLER_BUTTON_DPAD_LEFT, level, 50, 50, Vector2D(500, 300), Vector2D(0, 0));
			activo = true;
		}
	}

}

void QTEManager::render(Uint32 time) {
	if (flecha != nullptr) flecha->render(time);
}