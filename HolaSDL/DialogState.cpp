#include "DialogState.h"
#include <fstream>
#include "Background.h"
#include "GameManager.h"
#include "Character.h"
#include "Squares.h"
#include "TextBox.h"
#include <iostream>
using namespace std;


DialogState::DialogState(GameManager* g, int txt, int numctrl, bool oneP, bool hardMode): GameState(g), oneP_(oneP), hardMode_(hardMode), nlevel(txt)
{
	archivo = levels[txt];
	controller = SDL_GameControllerOpen(numctrl);
	init();
}
//EL m�ximo de caracteres por cuadro es 35*2 = 70, contando espacios y el primer espacio
void DialogState::init() 
{
	
	Dialog d;
	int aux;
	int sp;
	string textAux;
	
	ifstream file("resources/dialog/" + archivo + ".txt");
	
	if (file.is_open()) {
		file >> aux;
		for (int i = 0; i < aux; i++) {
			file >> sp;
			//sprites.push_back(new Background(manager, manager->getWindowWidth(), manager->getWindowHeight(), Vector2D(0, 0), sp));
			stage.push_back(new Background(manager, manager->getDefaultWindowWidth(), manager->getDefaultWindowHeight(), Vector2D(0, 0), sp));
		}
		file >> aux;
		//Sprites
		for (int i = 0; i < aux; i++) {
			file >> sp;
		//	sprites.push_back(new Character(manager,240 , 480, Vector2D(100 * (i*5), 100), sp));
			//stage.push_back(new Character(manager, 240, 480, Vector2D(100 * (i * 5), 100), sp));
		}
		file >> aux;
		for (int i = 0; i < aux; i++) {
			file >> sp;
			//Hay que crear una nueva clase que sea textBox
			file >> textAux;
			box.insert(pair<string, GameObject*>(textAux, new TextBox(manager, manager->getDefaultWindowWidth() - 20, 400, Vector2D(10, manager->getDefaultWindowHeight()-400),sp)));
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
		file.close();
		actualBox = box[dialogo.front().box];
		text = new TextObject(manager, manager->getServiceLocator()->getFonts()->getFont(Resources::RETRO30), Vector2D(manager->getDefaultWindowWidth() / 22 + 10, manager->getDefaultWindowHeight() - 140));
		text->setText("AAAAA", { COLOR(0x00000000) });
		text2 = new TextObject(manager, manager->getServiceLocator()->getFonts()->getFont(Resources::RETRO30), Vector2D(manager->getDefaultWindowWidth() / 22 + 20, manager->getDefaultWindowHeight() - 140 + text->getHeight()));

		updateText();
	}
}
	
	
	


DialogState::~DialogState()
{
	delete actualBox;
}

void DialogState::render(Uint32 time, bool beatSync) {
	for (auto it : stage) {
		it->render(time, beatSync);
	}
	actualBox->render(time, beatSync);
	text->render(time);
	text2->render(time);
}

bool DialogState::handleEvent(Uint32 time, SDL_Event e) {

	GameState::handleEvent(time, e);

	if ((e.type == SDL_CONTROLLERBUTTONDOWN && SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A) && keyup) || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE))
	{
		if (!dialogo.empty()) {
			dialogo.pop_front();
			if (!dialogo.empty()) {
				actualBox = box[dialogo.front().box];
			}
			else actualBox = new TextBox(manager, manager->getDefaultWindowWidth() - 20, 400, Vector2D(10, manager->getDefaultWindowHeight() - 400), 29);

			updateText();

			keyup = false;
		}
		else if (end) {
			manager->getMachine()->changeState(new PlayState(manager, nlevel, oneP_, hardMode_));
		}

	}
	else if (e.type == SDL_CONTROLLERBUTTONUP) keyup = true;

	else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_TAB)
		manager->getMachine()->changeState(new PlayState(manager, nlevel, oneP_, hardMode_));

	return true;
}

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
		text->setText("COMIENZA LA BATALLA", { COLOR(0x00000000) });
		text2->setText(" ", { COLOR(0x00000000) });

		end = true;
	}
}



