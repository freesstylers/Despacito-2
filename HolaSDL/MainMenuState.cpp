#include "MainMenuState.h"
#include "Credits.h"
#include <stdio.h>


MainMenuState::MainMenuState(GameManager* g) :GameState(g)
{
	gameManager = g;

	P1Controller = manager->getP1Controller();
	P2Controller = manager->getP2Controller();

	buttons.reserve(10);
	selectButton.reserve(5);
	controller = SDL_GameControllerOpen(0);

	EmptyObject* bg = new EmptyObject(g, Vector2D(0, 0), gameManager->getDefaultWindowWidth(), gameManager->getDefaultWindowHeight(), Resources::MainMenu);
	EmptyObject* loadGame1 = new EmptyObject(g, Vector2D(gameManager->getDefaultWindowWidth() / 2 + 70, gameManager->getDefaultWindowHeight() / 2 - 400), 600, 190, Resources::ChargeGameNoSelected);
	EmptyObject* loadGame2 = new EmptyObject(g, Vector2D(gameManager->getDefaultWindowWidth() / 2 + 70, gameManager->getDefaultWindowHeight() / 2 - 400), 600, 190, Resources::ChargeGameSelected);
	EmptyObject* newGame1 = new EmptyObject(g, Vector2D(gameManager->getDefaultWindowWidth() / 2 + 60, gameManager->getDefaultWindowHeight() / 2 - 260), 600, 190, Resources::NewGameNoSelected);
	EmptyObject* newGame2 = new EmptyObject(g, Vector2D(gameManager->getDefaultWindowWidth() / 2 + 60, gameManager->getDefaultWindowHeight() / 2 - 260), 600, 190, Resources::NewGameSelected);
	EmptyObject* options1 = new EmptyObject(g, Vector2D(gameManager->getDefaultWindowWidth() / 2 + 100, gameManager->getDefaultWindowHeight() / 2 - 120), 600, 190, Resources::OptionsNoSelected);
	EmptyObject* options2 = new EmptyObject(g, Vector2D(gameManager->getDefaultWindowWidth() / 2 + 100, gameManager->getDefaultWindowHeight() / 2 - 120), 600, 190, Resources::OptionsSelected);
	EmptyObject* credits1 = new EmptyObject(g, Vector2D(gameManager->getDefaultWindowWidth() / 2 + 60, gameManager->getDefaultWindowHeight() / 2 + 25), 600, 190, Resources::CreditsNoSelected);
	EmptyObject* credits2 = new EmptyObject(g, Vector2D(gameManager->getDefaultWindowWidth() / 2 + 60, gameManager->getDefaultWindowHeight() / 2 + 25), 600, 190, Resources::CreditsSelected);
	EmptyObject* exit1 = new EmptyObject(g, Vector2D(gameManager->getDefaultWindowWidth() / 2 + 200, gameManager->getDefaultWindowHeight() / 2 + 165), 600, 190, Resources::ExitNoSelected);
	EmptyObject* exit2 = new EmptyObject(g, Vector2D(gameManager->getDefaultWindowWidth() / 2 + 200, gameManager->getDefaultWindowHeight() / 2 + 165), 600, 190, Resources::ExitSelected);

	buttons.push_back(loadGame1);
	buttons.push_back(loadGame2);
	buttons.push_back(newGame1);
	buttons.push_back(newGame2);
	buttons.push_back(options1);
	buttons.push_back(options2);
	buttons.push_back(credits1);
	buttons.push_back(credits2);
	buttons.push_back(exit1);
	buttons.push_back(exit2);

	for (int i = 0; i < buttons.size() / 2; i++) {
		buttons[2 * i]->scale(0.9);
		buttons[2 * i + 1]->scale(1.1);
	}

	bool b1 = true;
	bool b2 = false;
	bool b3 = false;
	bool b4 = false;
	bool b5 = false;

	selectButton.push_back(b1);
	selectButton.push_back(b2);
	selectButton.push_back(b3);
	selectButton.push_back(b4);
	selectButton.push_back(b5);

	stage.push_back(bg);

	double menuX = gameManager->getDefaultWindowWidth() / 3;
	double menuY = gameManager->getDefaultWindowHeight() / 6;
	double menuW = gameManager->getDefaultWindowWidth() / 3;
	double menuH = gameManager->getDefaultWindowHeight() * 2 / 3;

	double buttonConst = menuH / 9 - 50;

	op_bg = new EmptyObject(gameManager, Vector2D(menuX, menuY), menuW, menuH, Resources::MenuBG);

	music = new EmptyObject(gameManager, Vector2D(menuX + menuX / 4, menuY + menuH * 0.08 + buttonConst), menuW / 2, 45, Resources::ButtonMusic);
	music->scale(0.8);
	musicSelect = new EmptyObject(gameManager, Vector2D(menuX + menuX / 4, menuY + menuH * 0.08 + buttonConst + 45), menuW / 2, 45, Resources::ButtonVol);

	sounds = new EmptyObject(gameManager, Vector2D(menuX + menuX / 4, menuY + menuH * 0.275 + buttonConst), menuW / 2, 45, Resources::ButtonSound);
	sounds->scale(0.8);
	soundsSelect = new EmptyObject(gameManager, Vector2D(menuX + menuX / 4, menuY + menuH * 0.275 + buttonConst + 45), menuW / 2, 45, Resources::ButtonVol);

	controls = new EmptyObject(gameManager, Vector2D(menuX + menuX / 4, menuY + menuH * 0.475 + buttonConst), menuW / 2, 45, Resources::ButtonControls);
	controls->scale(0.8);
	controlsSelect = new EmptyObject(gameManager, Vector2D(menuX + menuX / 4 - 75, menuY + menuH * 0.475 + buttonConst + 41), menuW / 2, 45, Resources::ButtonVol);
	controlsSelect->setWidth(controlsSelect->getWidth() + 150);
	controlsSelect->scale(0.8);

	controls2 = new EmptyObject(gameManager, Vector2D(menuX + menuX / 4, menuY + menuH * 0.650 + buttonConst), menuW / 2, 45, Resources::ButtonControls2);
	controls2->scale(0.8);
	controlsSelect2 = new EmptyObject(gameManager, Vector2D(menuX + menuX / 4 - 75, menuY + menuH * 0.650 + buttonConst + 41), menuW / 2, 45, Resources::ButtonVol);
	controlsSelect2->setWidth(controlsSelect2->getWidth() + 150);
	controlsSelect2->scale(0.8);

	op_exit = new EmptyObject(gameManager, Vector2D(menuX + menuX / 4, menuY + menuH * 0.8 + buttonConst + 25), menuW / 2, 45, Resources::ButtonExit);

	musicTxt = new TextObject(gameManager, gameManager->getServiceLocator()->getFonts()->getFont(Resources::RETRO30), Vector2D(0, 0));
	soundTxt = new TextObject(gameManager, gameManager->getServiceLocator()->getFonts()->getFont(Resources::RETRO30), Vector2D(0, 0));
	controlTxt = new TextObject(gameManager, gameManager->getServiceLocator()->getFonts()->getFont(Resources::RETRO30), Vector2D(0, 0));
	control2Txt = new TextObject(gameManager, gameManager->getServiceLocator()->getFonts()->getFont(Resources::RETRO30), Vector2D(0, 0));

	updateTxt();

	optionsButtons.push_back(musicSelect);
	optionsButtons.push_back(soundsSelect);
	optionsButtons.push_back(controlsSelect);
	optionsButtons.push_back(controlsSelect2);
	optionsButtons.push_back(op_exit);
	optionsButtons.push_back(music);
	optionsButtons.push_back(sounds);
	optionsButtons.push_back(controls);
	optionsButtons.push_back(controls2);
	selection = new EmptyObject(gameManager, Vector2D(menuX + menuX / 4, menuY + menuH * 2 / 3), menuW / 2, 45, Resources::ButtonSelection);
	confirmation = new EmptyObject(gameManager, Vector2D(gameManager->getDefaultWindowWidth() / 2 - 1020 / 2, gameManager->getDefaultWindowHeight() / 2 - 420 / 2), 1020, 420, Resources::newGameConfirm);

	g->getServiceLocator()->getAudios()->setChannelVolume(gameManager->getSoundVolume(), 1);
	g->getServiceLocator()->getAudios()->setChannelVolume(gameManager->getMusicVolume(), 0);

	manager->getServiceLocator()->getAudios()->playChannel(Resources::MainTheme, -1, 0);


	selection->setHeight(musicSelect->getHeight());
	selection->setWidth(musicSelect->getWidth());


	haptics = SDL_HapticOpen(0);	//id del controller, asumo 0 para MANDO 1 y 1 para MANDO 2
	SDL_HapticRumbleInit(haptics);

	aux = SDL_HapticRumblePlay(haptics, 1, 5000);
}


MainMenuState::~MainMenuState()
{
	for (int i = 0; i < 10; i++)
	{
		delete buttons[i];
		buttons[i] = nullptr;
	}

	delete op_bg;
	delete music;
	delete musicSelect;
	delete sounds;
	delete soundsSelect;
	delete controls;
	delete controls2;
	delete controlsSelect;
	delete controlsSelect2;
	delete confirmation;
	delete op_exit;

	delete selection;

	delete musicTxt;
	delete soundTxt;
	delete controlTxt;

	optionsButtons.clear();

	SDL_HapticClose(haptics);
}

void MainMenuState::render(Uint32 time, bool beatHandler)
{
	GameState::render(time);
	for (int i = 0; i < 5; i++)
	{
		if (selectButton[i] == true)
		{
			buttons[2 * i + 1]->render(time);
		}
		else {
			buttons[2 * i]->render(time);
		}
	}
	if (optionsOpen)
	{
		op_bg->render(time);
		for (EmptyObject* g : optionsButtons) {
			g->render(time);
		}

		selection->render(time);
		musicTxt->render(time);
		soundTxt->render(time);
		controlTxt->render(time);
		control2Txt->render(time);
	}
	if (confirmationActive) {
		confirmation->render(time);
	}
}

void MainMenuState::options()
{
	optionsOpen = !op_bg->isActive();

	op_bg->setActive(optionsOpen);

	for (EmptyObject* g : optionsButtons)
		g->setActive(optionsOpen);

	musicTxt->setActive(optionsOpen);
	soundTxt->setActive(optionsOpen);
	controlTxt->setActive(optionsOpen);
	control2Txt->setActive(optionsOpen);

	if (optionsOpen) {
		selectedButton = 0;
		selection->setPosition(optionsButtons[selectedButton]->getPosition());
		selection->setHeight(musicSelect->getHeight());
		selection->setWidth(musicSelect->getWidth());
		selection->forceAnimationChange(Resources::VolSelection);
	}
	gameManager->mainmenu = true;
}

void MainMenuState::updateMusic(bool raise)
{
	if (raise && gameManager->getMusicVolume() < 100) {
		gameManager->setMusicVolume(gameManager->getMusicVolume() + 5);
	}
	else if (!raise && gameManager->getMusicVolume() > 0) {
		gameManager->setMusicVolume(gameManager->getMusicVolume() - 5);
	}

	gameManager->getServiceLocator()->getAudios()->setChannelVolume(gameManager->getMusicVolume(), 0);
	gameManager->getServiceLocator()->getAudios()->setChannelVolume(gameManager->getMusicVolume(), 2);
	gameManager->getServiceLocator()->getAudios()->playChannel(Resources::Snare, 0, 2);

	updateTxt();
}

void MainMenuState::updateSound(bool raise)
{
	if (raise && gameManager->getSoundVolume() < 100) {
		gameManager->setSoundVolume(gameManager->getSoundVolume() + 5);
	}
	else if (!raise && gameManager->getSoundVolume() > 0) {
		gameManager->setSoundVolume(gameManager->getSoundVolume() - 5);
	}

	gameManager->getServiceLocator()->getAudios()->setChannelVolume(gameManager->getSoundVolume(), 1);
	gameManager->getServiceLocator()->getAudios()->playChannel(Resources::Snare, 0, 1);

	updateTxt();
}

void MainMenuState::updateControlsP1(bool raise)
{
	int P1Controller = manager->getP1Controller(); //

	if (raise)
	{
		if (P1Controller <= 1 || (P1Controller == 2 && manager->getP2Controller() != 3))
		{
			manager->setP1Controller((P1Controller + 1));
		}
		else
		{
			manager->setP1Controller(0);
		}
		P1Controller = manager->getP1Controller();

	}
	else
	{
		if (P1Controller > 0 && P1Controller <= 3)
		{
			manager->setP1Controller((P1Controller - 1));
		}
		else if (P1Controller == 0)
		{
			if (manager->getP2Controller() != 3)
				manager->setP1Controller(3);
			else
				manager->setP1Controller(2);
		}
		P1Controller = manager->getP1Controller();
	}

	updateTxt();
}

void MainMenuState::updateControlsP2(bool raise)
{
	int P2Controller = manager->getP2Controller(); //

	if (raise)
	{
		if (P2Controller <= 1 || (P2Controller == 2 && manager->getP1Controller() != 3))
		{
			manager->setP2Controller((P2Controller + 1));
		}
		else
		{
			manager->setP2Controller(0);
		}
		P2Controller = manager->getP2Controller();

	}
	else
	{
		if (P2Controller > 0 && P2Controller <= 3)
		{
			manager->setP2Controller((P2Controller - 1));
		}
		else if (P2Controller == 0)
		{
			if (manager->getP1Controller() != 3)
				manager->setP2Controller(3);
			else
				manager->setP2Controller(2);
		}
		P2Controller = manager->getP2Controller();
	}

	updateTxt();
}

void MainMenuState::updateTxt()	//this updates the text found in the options menu
{
	int P1Controller = manager->getP1Controller();
	int P2Controller = manager->getP2Controller();


	musicTxt->setText(to_string(gameManager->getMusicVolume()), SDL_Color{ 0, 0, 0, 255 });
	musicTxt->setPosition(musicSelect->getPosition() + Vector2D(musicSelect->getWidth() / 2, musicSelect->getHeight() / 2) - Vector2D(musicTxt->getWidth() / 2, musicTxt->getHeight() / 2));

	soundTxt->setText(to_string(gameManager->getSoundVolume()), SDL_Color{ 0, 0, 0, 255 });
	soundTxt->setPosition(soundsSelect->getPosition() + Vector2D(soundsSelect->getWidth() / 2, soundsSelect->getHeight() / 2) - Vector2D(soundTxt->getWidth() / 2, soundTxt->getHeight() / 2));

	switch (P1Controller)
	{
	case 0:
		controlTxt->setText("Xbox", SDL_Color{ 0, 0, 0, 255 });
		break;
	case 1:
		controlTxt->setText("PS4", SDL_Color{ 0, 0, 0, 255 });
		break;
	case 2:
		controlTxt->setText("Flechas", SDL_Color{ 0, 0, 0, 255 });
		break;
	case 3:
		controlTxt->setText("Teclado", SDL_Color{ 0, 0, 0, 255 });
		break;
	default:
		manager->setP1Controller(0);
		P1Controller = manager->getP1Controller();
		controlTxt->setText("Xbox", SDL_Color{ 0, 0, 0, 255 });
		break;
	}

	controlTxt->setPosition(controlsSelect->getPosition() + Vector2D(controlsSelect->getWidth() / 2, controlsSelect->getHeight() / 2) - Vector2D(controlTxt->getWidth() / 2, controlTxt->getHeight() / 2));

	switch (P2Controller)
	{
	case 0:
		control2Txt->setText("Xbox", SDL_Color{ 0, 0, 0, 255 });
		break;
	case 1:
		control2Txt->setText("PS4", SDL_Color{ 0, 0, 0, 255 });
		break;
	case 2:
		control2Txt->setText("Flechas", SDL_Color{ 0, 0, 0, 255 });
		break;
	case 3:
		control2Txt->setText("Teclado", SDL_Color{ 0, 0, 0, 255 });
		break;
	default:
		manager->setP2Controller(0);
		P2Controller = manager->getP2Controller();
		control2Txt->setText("Xbox", SDL_Color{ 0, 0, 0, 255 });
		break;
	}

	control2Txt->setPosition(controlsSelect2->getPosition() + Vector2D(controlsSelect2->getWidth() / 2, controlsSelect2->getHeight() / 2) - Vector2D(control2Txt->getWidth() / 2, control2Txt->getHeight() / 2));


	manager->updateOptionsFile();
}

void MainMenuState::nextButton()
{
	if (optionsOpen == true)
	{
		if (selectedButton == 4) //deberia ser 4
			selectedButton = 0;
		else {
			selectedButton++;
		}

		selection->setPosition(optionsButtons[selectedButton]->getPosition());

		if (selectedButton == 0 || selectedButton == 1)
		{
			selection->setHeight(musicSelect->getHeight());
			selection->setWidth(musicSelect->getWidth());
		}

		else if (selectedButton == 2 || selectedButton == 3)
		{
			//selection->setPosition(selection->getPosition() + 75);
			selection->setHeight(controlsSelect->getHeight());
			selection->setWidth(controlsSelect->getWidth());
		}

		if (selectedButton == 4)
		{
			selection->setHeight(op_exit->getHeight());
			selection->setWidth(op_exit->getWidth());
			selection->forceAnimationChange(Resources::ButtonSelection);
		}
		else
		{
			selection->forceAnimationChange(Resources::VolSelection);
		}
	}
	else {
		selectButton[index] = false;
		if (index < max)
		{
			index++;
		}
		else {
			index = min;
		}
		selectButton[index] = true;
	}
}
void MainMenuState::backButton()
{
	if (optionsOpen)
	{
		if (selectedButton == 0)
			selectedButton = 4; //4
		else {
			selectedButton--;
		}

		selection->setPosition(optionsButtons[selectedButton]->getPosition());

		if (selectedButton == 0 || selectedButton == 1)
		{
			selection->setHeight(musicSelect->getHeight());
			selection->setWidth(musicSelect->getWidth());
		}
		else if (selectedButton == 2 || selectedButton == 3)
		{
			//selection->setPosition(selection->getPosition() + 75);
			selection->setHeight(controlsSelect->getHeight());
			selection->setWidth(controlsSelect->getWidth());
		}


		if (selectedButton == 4) //4
		{
			selection->setHeight(op_exit->getHeight());
			selection->setWidth(op_exit->getWidth());
			selection->forceAnimationChange(Resources::ButtonSelection);
		}
		else
		{
			selection->forceAnimationChange(Resources::VolSelection);
		}
	}
	else {
		selectButton[index] = false;
		if (index > min)
		{
			index--;
		}
		else {
			index = max;
		}
		selectButton[index] = true;
	}
}

void MainMenuState::newGame(GameManager* gameManager)	//erases all the savefiles (besides the options) and pushes a Tutorial State
{
	remove("resources/data/0.ddb");
	remove("resources/data/1.ddb");
	remove("resources/data/2.ddb");
	remove("resources/data/3.ddb");
	remove("resources/data/4.ddb");
	remove("resources/data/5.ddb");
	gameManager->getMachine()->changeState(new DialogState(gameManager, 0, 0, true, false, 0, 0));
}

void MainMenuState::exit(GameManager* gameManager)
{
	gameManager->exit_ = true;
}

bool MainMenuState::handleEvent(Uint32 time, SDL_Event e)
{
	if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_F9) {
		manager->stop();
		return true;
	}

	bool input = false;
	
	if ((SDL_CONTROLLERBUTTONDOWN || SDL_KEYDOWN) && keyup)
	{
		if (!confirmationActive && (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN) || e.key.keysym.sym == SDLK_DOWN))
		{
			nextButton();

			input = true;
		}
		else if (!confirmationActive && (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_UP) || e.key.keysym.sym == SDLK_UP))
		{
			backButton();
			input = true;
		}
		else if (!confirmationActive && (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT) || e.key.keysym.sym == SDLK_RIGHT))
		{
			if (optionsOpen) {
				switch (selectedButton) {
				case 0:
					updateMusic(true);
					break;
				case 1:
					updateSound(true);
					break;
				case 2:
					updateControlsP1(true);
					break;
				case 3:
					updateControlsP2(true);
					break;
				default:
					break;
				}
			}

			input = true;

		}
		else if (!confirmationActive && (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_B) || e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_BACKSPACE))
		{
			if (optionsOpen) {
				options();
			}

			input = true;

		}
		else if (!confirmationActive && (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT) || e.key.keysym.sym == SDLK_LEFT))
		{
			if (optionsOpen) {
				switch (selectedButton) {
				case 0:
					updateMusic(false);
					break;
				case 1:
					updateSound(false);
					break;
				case 2:
					updateControlsP1(false);
					break;
				case 3:
					updateControlsP2(true);
					break;
				default:
					break;
				}
			}

			input = true;

		}
		else if (selectButton[0] == true && (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A) || e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_SPACE))
		{
			manager->getServiceLocator()->getAudios()->haltChannel(0);
			gameManager->mainmenu = false;
			input = true;
			gameManager->getMachine()->changeState(new MapState(gameManager));
		}
		else if (selectButton[1] == true && (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_B) || e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_BACKSPACE))
		{
			if (confirmationActive) {
				confirmationActive = false;
			}

			input = true;

		}
		else if (selectButton[1] == true && (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A) || e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_SPACE))
		{
			if (confirmationActive) {
				manager->getServiceLocator()->getAudios()->haltChannel(0);
				gameManager->mainmenu = false;
				confirmationActive = false;
				input = true;
				newGame(gameManager);
			}
			else {
				confirmationActive = true;
			}

			input = true;

		}
		else if (selectButton[2] == true && (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A) || e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_SPACE))
		{
			gameManager->mainmenu = false;
			options();
			input = true;
		}
		else if (selectButton[3] == true && (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A) || e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_SPACE))
		{
			gameManager->mainmenu = false;
			manager->getMachine()->changeState(new Credits(gameManager));
			input = true;
		}
		else if (selectButton[4] == true && (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A) || e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_SPACE))
		{
			gameManager->mainmenu = false;
			exit(gameManager);
			input = true;
		}

		if(input) //if any button got pressed
			keyup = false;
	}
	else if (e.type == SDL_CONTROLLERBUTTONUP || e.type == SDL_KEYUP) { keyup = true; input = false; }

	return false;
}