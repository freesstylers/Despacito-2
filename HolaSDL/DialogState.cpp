#include "DialogState.h"
#include <fstream>
#include "Background.h"
#include "GameManager.h"
#include "Character.h"
#include "Squares.h"
#include "TextBox.h"
#include <iostream>
using namespace std;


DialogState::DialogState(GameManager* g, int txt, int numctrl, bool oneP, bool hardMode, int prevMaxScoreE, int prevMaxScoreH): GameState(g), oneP_(oneP), hardMode_(hardMode), nlevel(txt)
{
	archivo = levels[txt];
	controller = SDL_GameControllerOpen(numctrl);
	prevMaxScoreE_ = prevMaxScoreE;
	prevMaxScoreH_ = prevMaxScoreH;
	init();
}
//EL m�ximo de caracteres por cuadro es 35*2 = 70, contando espacios y el primer espacio
void DialogState::init() 
{
	//Primero, cargamos todos los di�logos, y las im�genes que necesitaremos, leyendolo del txt correspondiente
	Dialog d;
	int aux;
	int sp;
	string textAux;
	
	ifstream file("resources/dialog/" + archivo + ".txt");
	
	if (file.is_open()) {
		file >> aux;
		//Fondo
		for (int i = 0; i < aux; i++) {
			file >> sp;
			stage.push_back(new Background(manager, manager->getDefaultWindowWidth(), manager->getDefaultWindowHeight(), Vector2D(0, 0), sp));
		}
		file >> aux;
		//Sprites
		for (int i = 0; i < aux; i++) {
			file >> sp;
			stage.push_back(new Character(manager, 240, 480, Vector2D(100 * (i * 3) + 600, 100), sp));
		}
		file >> aux;
		for (int i = 0; i < aux; i++) {
			file >> sp;
			//Di�logo
			file >> textAux;
			textBox = new TextBox(manager, manager->getDefaultWindowWidth() - 20, 400, Vector2D(10, manager->getDefaultWindowHeight() - 400), sp);
			box.insert(pair<string, GameObject*>(textAux, textBox));
		}

		file >> textAux;
		while (textAux != "0") {
			if (textAux == "-") {
				file >> d.box;
				file >> textAux;
				while (textAux != "-" && textAux != "0") {
					d.text = d.text + " " + textAux;
					file >> textAux;

				}
				dialogo.push_back(d);
				d.text = "";
			}
			//file >> textAux;
		}
		actualBox = box[dialogo.front().box];
		text = new TextObject(manager, manager->getServiceLocator()->getFonts()->getFont(Resources::RETRO30), Vector2D(manager->getDefaultWindowWidth() / 22 + 10, manager->getDefaultWindowHeight() - 140));
		text->setText("AAAAA", { COLOR(0x00000000) });
		text2 = new TextObject(manager, manager->getServiceLocator()->getFonts()->getFont(Resources::RETRO30), Vector2D(manager->getDefaultWindowWidth() / 22 + 20, manager->getDefaultWindowHeight() - 140 + text->getHeight()));
		timer = new TimerNoSingleton();
		manager->getServiceLocator()->getAudios()->playChannel(Resources::Snare, 0, 1);
		manager->getServiceLocator()->getAudios()->setChannelVolume(10, 4);
		manager->getServiceLocator()->getAudios()->playChannel(Resources::Ambient, -1, 4);
		timer->Reset();
		updateText();
	}

	file.close();
}
//Solo usado para el timer	
void DialogState::update(Uint32 time) 
{
	timer->Update();
	
	if (timer->DeltaTime() > .25)
	{
		beatSignal = true;
		timer->Reset();
	}
}

DialogState::~DialogState()
{
	bool check = false;
	delete timer;

	for (pair<string, GameObject*> i : box) {
		check = check || i.second == actualBox;
		delete i.second;
		i.second = nullptr;
	}

	box.clear();

	delete text;
	delete text2;
	if(!check)
		delete actualBox;
}

//Renderizar
void DialogState::render(Uint32 time, bool beatSync) {
	GameState::render(time, beatSignal);
	/*
	for (auto it : stage) {
		it->render(time, beatSync);
	}*/
 	actualBox->render(time, beatSync);
	text->render(time);
	text2->render(time);
	beatSignal = false;
}

bool DialogState::handleEvent(Uint32 time, SDL_Event e) {

	GameState::handleEvent(time, e);
	//Pasar de di�logo
	if ((e.type == SDL_CONTROLLERBUTTONDOWN && SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A) && keyup) || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE))
	{
		manager->getServiceLocator()->getAudios()->playChannel(Resources::Snare, 0, 1);
		if (!dialogo.empty()) {
			dialogo.pop_front();
			if (!dialogo.empty()) {
				actualBox = box[dialogo.front().box];
			}
			//En caso de que sea el �ltimo di�logo
			else if (archivo == "Corpselillo1" || archivo == "Onilecram1") { 
				actualBox = new TextBox(manager, manager->getDefaultWindowWidth() - 20, 400, Vector2D(10, manager->getDefaultWindowHeight() - 400), Resources::GreyDialog);
			}
			else 
 				actualBox = new TextBox(manager, manager->getDefaultWindowWidth() - 20, 400, Vector2D(10, manager->getDefaultWindowHeight() - 400), 131);

			updateText();

			keyup = false;
		}
		else if (end) {
			manager->getServiceLocator()->getAudios()->haltChannel(4);
			if(nlevel <= 5)
				manager->getMachine()->changeState(new PlayState(manager, nlevel, oneP_, hardMode_, prevMaxScoreE_, prevMaxScoreH_));
			else
				manager->getMachine()->changeState(new MapState(manager));
		}

	}
	else if (e.type == SDL_CONTROLLERBUTTONUP) keyup = true;

	else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_TAB || (e.type == SDL_CONTROLLERBUTTONDOWN && SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_BACK))) {

		manager->getServiceLocator()->getAudios()->haltChannel(4);
		if (nlevel <= 5)
			manager->getMachine()->changeState(new PlayState(manager, nlevel, oneP_, hardMode_, prevMaxScoreE_, prevMaxScoreH_));
		else
			manager->getMachine()->changeState(new MapState(manager));
	}

	return true;
}
//Cambiar de texto
void DialogState::updateText() {
	if (!dialogo.empty()) {

		if (dialogo.front().text.size() <= 51) {
			text->setText(dialogo.front().text, { COLOR(0x00000000) });
			text2->setText(" ", { COLOR(0x00000000) });
		}
		else {
			string aux1 = "";
			string aux2 = "";
			int intaux = 0;

			while (intaux <= 51 || (intaux > 51 && intaux < dialogo.front().text.size() && dialogo.front().text[intaux] != ' ')) {
				aux1 += dialogo.front().text[intaux];
				intaux++;
			}

			intaux++;

			while (intaux < dialogo.front().text.size()) {
				aux2 += dialogo.front().text[intaux];
				intaux++;
			}
			aux2 += " ";

			text->setText(aux1, { COLOR(0x00000000) });
			text2->setText(aux2, { COLOR(0x00000000) });
		}
	}
	else {
		if (nlevel <= 5) {
			text->setText("COMIENZA LA BATALLA", { COLOR(0x00000000) });
			text2->setText(" ", { COLOR(0x00000000) });
		}
		else if(nlevel % 2 == 0){
			text->setText("HAS COMPLETADO EL NIVEL", { COLOR(0x00000000) });
			text2->setText(" ", { COLOR(0x00000000) });
		}
		else {
			text->setText("NO HAS COMPLETADO EL NIVEL", { COLOR(0x00000000) });
			text2->setText(" ", { COLOR(0x00000000) });
		}

		end = true;
	}
}



