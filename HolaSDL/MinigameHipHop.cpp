#include "MinigameHipHop.h"
#include "GameManager.h"

MinigameHipHop::MinigameHipHop(GameManager * g, PlayState * p): MiniGame(g, p)
{
	manager = g;
	playS = p;
	fback = new Feedback(g, 150, 150, Vector2D(g->getWindowWidth() / 2 - 150 / 2, g->getWindowHeight() / 2 - 150 / 2));
	timer = new TimerNoSingleton();
	mira = new Crosshair(g, 50, 50, Vector2D(300, 400));
	createList();

	/*
	Objetos a incluir:

	Mira
	Fondo alternativo
	Notas (objetivos)

	*/
}

MinigameHipHop::~MinigameHipHop()
{
	delete mira;
}

void MinigameHipHop::render(Uint32 time)
{
	for (Note* o : screenButtons_)
	{
		o->render(time);
	}
	fback->render(time);
	mira->render(time);
}

void MinigameHipHop::update(Uint32 time)
{
	if (!screenButtons_.empty()) {

		for (Note* o : screenButtons_)
		{
			o->update(time);
		}
	}

	mira->update(time);

	Timer::Instance()->Update();
	timer->Update();
	if (timer->DeltaTime() > (playS->bh->getBeatTime() / 1000.0) && noteAmount > 0)
	{
		generateButtons();

		timer->Reset();

		noteAmount--;
	}
	if (Timer::Instance()->DeltaTime() > (playS->bh->getBeatTime() / 1000.0)*(maxNotes + 4)) {
		failed = true;
	}
}

void MinigameHipHop::handleInput(Uint32 time, SDL_Event e)
{
	for (Note* o : screenButtons_)
	{
		if (SDL_HasIntersection(&o->getRect(), &mira->getRect()))
			mira->superpuesto = true;
		else
			mira->superpuesto = false;

		mira->handleInput(time, e, o);

	}
}

void MinigameHipHop::generateButtons()
{
	if (!levelButtons_.empty()) {
		if (levelButtons_.back() != nullptr) {
			screenButtons_.push_back(levelButtons_.back());
		}
		levelButtons_.pop_back();
	}
}

void MinigameHipHop::createList()
{
	{
		int newpos;
		int aux;
		failed = false;
		noteAmount = 5;
		maxNotes = noteAmount;
		int select = 0;
		Note* note;
		for (int i = 0; i < 8; i++) {
			aux = rand() % 8;

			Vector2D pos = Vector2D(double(manager->getServiceLocator()->getRandomGenerator()->nextInt(1, manager->getWindowWidth())), double(manager->getServiceLocator()->getRandomGenerator()->nextInt(1, manager->getWindowHeight())));
			
			Vector2D vel = Vector2D(double(manager->getServiceLocator()->getRandomGenerator()->nextInt(-pos.getX() / 10, pos.getX() / 10)), double(manager->getServiceLocator()->getRandomGenerator()->nextInt(-pos.getX() / 10, pos.getX() / 10)));

			switch (aux) {
			case 0:
				note = new Note(SDL_CONTROLLER_BUTTON_A, manager, 75, 75, pos, vel);
				break;
			case 1:
				note = new Note(SDL_CONTROLLER_BUTTON_B, manager, 75, 75, pos, vel);
				break;
			case 2:
				note = new Note(SDL_CONTROLLER_BUTTON_X, manager, 75, 75, pos, vel);
				break;
			case 3:
				note = new Note(SDL_CONTROLLER_BUTTON_Y, manager, 75, 75, pos, vel);
				break;
			case 4:
				note = new Note(SDL_CONTROLLER_BUTTON_A, manager, 75, 75, pos, vel);
				break;
			case 5:
				note = new Note(SDL_CONTROLLER_BUTTON_B, manager, 75, 75, pos, vel);
				break;
			case 6:
				note = new Note(SDL_CONTROLLER_BUTTON_X, manager, 75, 75, pos, vel);
				break;
			case 7:
				note = new Note(SDL_CONTROLLER_BUTTON_Y, manager, 75, 75, pos, vel);
				break;
			}
			levelButtons_.push_front(note);
		}
	}
}

void MinigameHipHop::deleteList()
{
	for (auto o = screenButtons_.begin(); o != screenButtons_.end();)
	{
		auto next = o;
		++next;
		delete (*o);
		screenButtons_.remove(*o);
		o = next;
	}
}

void MinigameHipHop::resetMinigame()
{
	mira->setVelocity(Vector2D(0, 0));
}
