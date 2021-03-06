#include "PlayerPack.h"
#include "PlayState.h"

PlayerPack::PlayerPack()
{
}

PlayerPack::PlayerPack(SDLGame* manager, PlayState* ps, int leftNotesPos, int rightNotesPos, int pointSize, int squareWidth, int player, bool OneP): GameObject(manager), playstate_(ps)
{
	int player_ = player;

	for (int i = 0; i < 4; i++)
	{
		califications[i] = 0;
	}

	if (player == 0)
	{
		controllerMode = manager->getP1Controller();
	}
	else if (player == 1)
	{
		controllerMode = manager->getP2Controller();
		if (manager->getP1Controller() == 3)
			player_--;
	}

	lip = new LevelInputManager(playstate_, this, player_, controllerMode);
	player_ = player;

	leftNotesVector = Vector2D(leftNotesPos - 50 / 2, 70);
	rightNotesVector = Vector2D(rightNotesPos - 50 / 2, 70);

	leftPoint = new Point(manager, pointSize, pointSize, Vector2D(leftNotesPos - pointSize / 2, 565), lip->getController(), true, player_);
	rightPoint = new Point(manager, pointSize, pointSize, Vector2D(rightNotesPos - pointSize / 2, 565), lip->getController(), false, player_);
	leftNoteBar = new Squares(manager, squareWidth, 565 + 0.6 * pointSize, Vector2D(leftNotesPos + 1 - squareWidth / 2, leftNotesVector.getY()));
	rightNoteBar = new Squares(manager, squareWidth, 565 + 0.6 * pointSize, Vector2D(rightNotesPos + 1 - squareWidth / 2, rightNotesVector.getY()));
	if (!OneP && player_ == 0)
	{
		leftNoteBar->forceAnimationChange(Resources::Recuadro1P);
		rightNoteBar->forceAnimationChange(Resources::Recuadro1P);
	}
	else if (!OneP && player_ == 1)
	{
		leftNoteBar->forceAnimationChange(Resources::Recuadro2P);
		rightNoteBar->forceAnimationChange(Resources::Recuadro2P);
	}
	feedbackLeft = new FeedbackPool(manager, pointSize * 0.8, pointSize * 0.8, Vector2D(leftNotesPos - (pointSize * 2 *0.8), 565 + pointSize / 2));
	feedbackRight = new FeedbackPool(manager, pointSize * 0.8, pointSize * 0.8, Vector2D(rightNotesPos + (pointSize * 0.8), 565 + pointSize / 2));
	hitLeft = new HitNotePool(manager, pointSize - 10, pointSize - 10);
	hitRight = new HitNotePool(manager, pointSize - 10, pointSize - 10);
	noteYLimit = leftPoint->getPosition().getY() + leftPoint->getHeight()/1.5;
	if (player_ == 0)
	{
		scoreBar = new ScoreBar(manager, 80, 0, Vector2D(6, 500 + pointSize), playstate_->getMaxScore(), manager->getDefaultWindowHeight() - (500 + pointSize));
	}
	else
	{
		scoreBar = new ScoreBar(manager, 80, 0, Vector2D(manager->getDefaultWindowWidth() - 86, 500 + pointSize), playstate_->getMaxScore(), manager->getDefaultWindowHeight() - (500 + pointSize));
	}

	comboTextX = rightNoteBar->getPosition().getX() - ((rightNoteBar->getPosition().getX() - (leftNoteBar->getPosition().getX() + squareWidth)) / 2);

	comboPosition = Vector2D(comboTextX, 465);	//the position of the Combo Text is anchored to the middle of the object's x coordinate

	comboTxt = new ComboText(manager, manager->getServiceLocator()->getFonts()->getFont(Resources::FIPPS20), comboPosition);

	combo = 0;
}
void PlayerPack::render(Uint32 time, bool beatSync)
{
	leftNoteBar->render(time,beatSync);
	rightNoteBar->render(time,beatSync);
	leftPoint->render(time);
	rightPoint->render(time);
	comboTxt->render(time);
	scoreBar->render(time);
	feedbackLeft->render(time, false);
	feedbackRight->render(time, false);
	hitLeft->render(time, false);
	hitRight->render(time, false);

	for (Note* o : screenArrows_)
	{
		o->render(time, beatSync);
	}
	for (Note* o : screenButtons_)
	{
		o->render(time, beatSync);
	}
}

void PlayerPack::update(Uint32 time)
{
	leftNoteBar->update(time);
	rightNoteBar->update(time);
	leftPoint->update(time);
	rightNoteBar->update(time);
	scoreBar->update(time);
	feedbackRight->update(time);
	feedbackLeft->update(time);
	for (Note* o : screenArrows_)
	{
		if (o != nullptr) {
			o->update(time);
		}
			
	}
	for (Note* o : screenButtons_)
	{
		if (o != nullptr)
		{
			o->update(time);
		}
	}
	if (!screenArrows_.empty() && screenArrows_.front()->getPosition().getY() > noteYLimit)
	{
		Note* aux = screenArrows_.front();
		SDL_GameControllerButton x = aux->getKey();
		if (x == SDL_CONTROLLER_BUTTON_INVALID) {
			feedbackLeft->addFeedback(Resources::FeedbackPerfect);
			addCalifications(3);
			updateScoreNote(1);
			addCombo(1);
		}
		else
		{
			playstate_->showError();
			resetCombo();
			feedbackLeft->addFeedback(Resources::FeedbackBad);
			addCalifications(0);
		}
		delete aux;
		screenArrows_.pop_front();
		lip->numFailed++;
	}
	if (!screenButtons_.empty() && screenButtons_.front()->getPosition().getY() > noteYLimit)
	{
		Note* aux = screenButtons_.front();
		SDL_GameControllerButton y = aux->getKey();
		if (y == SDL_CONTROLLER_BUTTON_INVALID) {
			feedbackRight->addFeedback(Resources::FeedbackPerfect);
			updateScoreNote(1);
			addCombo(1);
			addCalifications(3);
		}
		else
		{
			playstate_->showError();
			feedbackRight->addFeedback(Resources::FeedbackBad);
			resetCombo();
			addCalifications(0);
		}
		delete aux;
		screenButtons_.pop_front();
		lip->numFailed++;
	}
}

bool PlayerPack::handleInput(Uint32 time, const SDL_Event& event)
{
	leftPoint->handleInput(time, event);
	rightPoint->handleInput(time, event);
	feedbackLeft->handleInput(time, event);
	feedbackRight->handleInput(time, event);

	return lip->handleInput(time, event);;
}

void PlayerPack::addCombo(int i)
{
	combo += i;

	if (combo > maxCombo)
		maxCombo = combo;

	if (combo == 10 || combo == 25 || combo == 50 || combo % 100 == 0) {
		comboTxt->updateCombo(combo);
		updateCombo();
	}

}

void PlayerPack::resetCombo()
{
	if (combo != 0) {
		combo = 0;
		comboTxt->setActive(false);
		updateCombo();
	}

}

int* PlayerPack::getCalifications() //Makes possible showing data at EndState
{
	return califications;
}

void PlayerPack::addCalifications(int letter)
{
	califications[letter]++;
}

void PlayerPack::changeController(int controller)
{
	for (Note* o : screenArrows_) {
		if (o != nullptr)
			o->changeController(controller);
	}
	for (Note* o : screenButtons_) {
		if (o != nullptr)
			o->changeController(controller);
	}

	if (controller < 2) {
		leftPoint->forceAnimationChange(Resources::Point);
		leftPoint->setControllerMode(controller);
		rightPoint->forceAnimationChange(Resources::Point);
		rightPoint->setControllerMode(controller);
	}
	else {
		leftPoint->forceAnimationChange(Resources::KeyPoint);
		leftPoint->setControllerMode(controller);
		rightPoint->forceAnimationChange(Resources::KeyPoint);
		rightPoint->setControllerMode(controller);
	}

	lip->setControllerMode(controller);
}

void PlayerPack::updateCombo()
{

	if (combo < 10) {
		playstate_->getPerico()->setAnimation(Resources::PericoIdle);
	}

	else
	{
		if (combo < 50)
			playstate_->getPerico()->setAnimation(Resources::PericoDab);

		else if (combo < 100)
			playstate_->getPerico()->setAnimation(Resources::PericoDance1);

		else
			playstate_->getPerico()->setAnimation(Resources::PericoMaxPower);
	}
}

PlayerPack::~PlayerPack()
{
	delete leftNoteBar;
	delete rightNoteBar;
	delete leftPoint;
	delete rightPoint;
	delete feedbackRight;
	delete feedbackLeft;
	delete hitRight;
	delete hitLeft;
	delete lip;
	delete comboTxt;
	delete scoreBar;
	delete califications;

	for (Note* o : screenArrows_)
	{
		delete o;
	}
	for (Note* o : screenButtons_)
	{
		delete o;
	}
}

void PlayerPack::updateScoreNote(int accuracy)
{
	if(accuracy == 1)
		currentScore += playstate_->getMaxNoteValue();
	else if(accuracy == 2)
		currentScore += playstate_->getMaxNoteValue() * 0.75;
	else
		currentScore += playstate_->getMaxNoteValue() * 0.5;
	scoreBar->updateBar(currentScore);
}
