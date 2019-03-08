#include "PlayState.h"
#include "GameManager.h"

PlayState::PlayState(GameManager* g) :GameState(g) //Asigna game y llama a inicializaci�n
{
	newGame();
}

void PlayState::newGame()
{
	/*
	Inicializar:

	Barra de puntuacion
	Barra de la cancion
	Perico
	Enemigo
	Fondo
	Cancion
	Flechas
	Pulsador/Logica de botones
	*/

	int leftNotesPos = manager->getWindowWidth() / 2 - pointOffset;
	int rightNotesPos = manager->getWindowWidth() / 2 + pointOffset;
	
	
	

	timer = Timer::Instance();
	timer->Reset();
	leftPoint = new Point(manager, pointSize, pointSize, Vector2D(leftNotesPos - pointSize / 2, 465));
	rightPoint = new Point(manager, pointSize, pointSize, Vector2D(rightNotesPos - pointSize / 2, 465));
	lip = new LevelInputManager(this);
	lip->setMinigameActive(true);
	perico = new Perico(manager, 33, 33, Vector2D(100, 50));
	minigame = new MiniGame(manager, this);

	cin >> level;

	ifstream file("resources/levels/" + level + ".txt");

	file >> bpm;
	file >> tiempo;
	file >> probqte;

	barraPuntos = new BarraPuntos(manager, 20, 20, Vector2D(20, 100));
	spriteBarra = new FondoBarra(manager, 20, 20, Vector2D(20, 25), tiempo / (manager->getWindowWidth() - 40+50), Resources::Bar);
	indicador = new BarrasHUD(manager, 50, 50, Vector2D(20, 10), Vector2D(tiempo/(manager->getWindowWidth()-40+50), 0),spriteBarra); //0.3 va a depender de la duracion de la cancion

	bh = new BeatHandeler(bpm);
	qteman = new QTEManager(manager, probqte);

	velFlechas = asignaVel(bh->getBeatTime());

	Vector2D leftNotesVector = Vector2D(leftNotesPos - noteSize / 2, initialNoteHeight);
	Vector2D rightNotesVector = Vector2D(rightNotesPos - noteSize / 2, initialNoteHeight);
	int aux;
	Flechas* flecha;
	for (int i = 0; i < 50; i++) {
		file >> aux;
		switch (aux) {
		case 0:
			flecha = nullptr;
			break;
		case 1:
			flecha = new Flechas(SDL_CONTROLLER_BUTTON_DPAD_LEFT, manager, noteSize, noteSize, leftNotesVector, velFlechas);
			break;
		case 2:
			flecha = new Flechas(SDL_CONTROLLER_BUTTON_DPAD_RIGHT, manager, noteSize, noteSize, leftNotesVector, velFlechas);
			break;
		case 3:
			flecha = new Flechas(SDL_CONTROLLER_BUTTON_DPAD_UP, manager, noteSize, noteSize, leftNotesVector, velFlechas);
			break;
		case 4:
			flecha = new Flechas(SDL_CONTROLLER_BUTTON_DPAD_DOWN, manager, noteSize, noteSize, leftNotesVector, velFlechas);
			break;
		}
		flechasNivel_.push_back(flecha);
	}
	for (int i = 0; i < 50; i++) {
		file >> aux;
		switch (aux) {
		case 0:
			flecha = nullptr;
			break;
		case 1:
			flecha = new Flechas(SDL_CONTROLLER_BUTTON_A, manager, noteSize, noteSize, rightNotesVector, velFlechas);
			break;
		case 2:
			flecha = new Flechas(SDL_CONTROLLER_BUTTON_B, manager, noteSize, noteSize, rightNotesVector, velFlechas);
			break;
		case 3:
			flecha = new Flechas(SDL_CONTROLLER_BUTTON_X, manager, noteSize, noteSize, rightNotesVector, velFlechas);
			break;
		case 4:
			flecha = new Flechas(SDL_CONTROLLER_BUTTON_Y, manager, noteSize, noteSize, rightNotesVector, velFlechas);
			break;
		}
		botonesNivel_.push_back(flecha);
	}
	file.close();


	stage.push_back(leftPoint);
	stage.push_back(rightPoint);
	stage.push_back(perico);
	stage.push_back(barraPuntos);
	stage.push_back(spriteBarra);
	stage.push_back(indicador);



	/////////////////////////

	//exit_ = false;
	manager->getServiceLocator()->getAudios()->playChannel(Resources::Pruebas, -1);
	manager->getServiceLocator()->getAudios()->setChannelVolume(70);

	
}


PlayState::~PlayState()
{
}

void PlayState::update(Uint32 time)
{
	GameState::update(time);
	if (miniActive == false) {
	for (Flechas* o : flechasPantalla_)
	{
		o->update(time);
	}
	for (Flechas* o : botonesPantalla_)
	{
		o->update(time);
	}
	//qteman->update(time);
	
		if (!flechasPantalla_.empty() && flechasPantalla_.front()->getPosition().getY() > 550)
		{

			flechasPantalla_.pop_front();
			cout << "fuera" << endl;

		}
		if (!botonesPantalla_.empty() && botonesPantalla_.front()->getPosition().getY() > 550)
		{

			botonesPantalla_.pop_front();
			cout << "fuera" << endl;

		}
		timer->Update();
		
		if ( timer->DeltaTime() > (bh->getBeatTime() / 1000) - 0.005 && timer->DeltaTime() < (bh->getBeatTime() / 1000) + 0.005)
		{
			generateFlechas();
			generateBotones();
			timer->Reset();

			beatSignal = true;
		}
		else if (timer->DeltaTime() < (bh->getBeatTime() / animationFramesPerBeat / 1000) + 0.010 && timer->DeltaTime() > (bh->getBeatTime() / animationFramesPerBeat / 1000) - 0.010)
		{
			//aqu� se divide el beatTime lo necesario para animar las frames especificadas entre cada beat

			beatSignal = true;
		}
	}
	else {
		minigame->update(time);
		lip->update();
		if (minigame->getFallado()) {
			lip->setMinigameActive(false);
			miniActive = false;
			timer->Reset();
			
			
		}
	}
	
}

bool PlayState::handleEvent(Uint32 time, SDL_Event e)
{
	if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) {
		manager->stop();
	}
	// Pressing f to toggle fullscreen.
	else if (e.key.keysym.sym == SDLK_f)
	{
		int flags = SDL_GetWindowFlags(manager->getWindow());
		if (flags & SDL_WINDOW_FULLSCREEN) {
			SDL_SetWindowFullscreen(manager->getWindow(), 0);
		}
		else {
			SDL_SetWindowFullscreen(manager->getWindow(), SDL_WINDOW_FULLSCREEN);
		}
	}
	else
	{
		if (miniActive) {
			lip->setMinigameActive(true);
		}
		
		
			lip->handleInput(time, e);
			//qteman->handleInput(time, e);
			GameState::handleEvent(time, e);
		
		return false;
	}
}

void PlayState::render(Uint32 time, bool beatSync)
{

	GameState::render(time, beatSignal);

	qteman->render(time, beatSignal);

	for (Flechas* o : flechasPantalla_)
	{
		o->render(time, beatSignal);
	}
	for (Flechas* o : botonesPantalla_)
	{
		o->render(time, beatSignal);
	}
	if (miniActive) {
		minigame->render(time);
	}

	beatSignal = false;
}

void PlayState::DeleteAll()
{
	for (GameObject* o : stage)
	{
		delete o;
	}

	for (Flechas* o : flechasPantalla_)
	{
		delete o;
	}

	for (Flechas* o : flechasNivel_) //Por si se cierra el nivel antes de que acabe
	{
		delete o;
	}
}

int PlayState::getPoints()
{
	return currentPoints;
}

void PlayState::changePoints(int data)
{
	currentPoints = currentPoints + data;
}

void PlayState::generateFlechas()
{
	if (!flechasNivel_.empty()) {
		if (flechasNivel_.back() != nullptr) {
			flechasPantalla_.push_back(flechasNivel_.back());
		}
		flechasNivel_.pop_back();
	}
}

void PlayState::generateBotones()
{
	if (!botonesNivel_.empty()) {
		if (botonesNivel_.back() != nullptr) {
			botonesPantalla_.push_back(botonesNivel_.back());
		}
		botonesNivel_.pop_back();
	}
}

Vector2D PlayState::asignaVel(double time)
{
	double distance = initialNoteHeight - (leftPoint->getPosition().getY()+ leftPoint->getHeight()/2);
	double velocity = distance / bh->getBeatTime();
	return Vector2D(0, -velocity * 4);
}