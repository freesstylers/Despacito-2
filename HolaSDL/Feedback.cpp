#include "Feedback.h"


Feedback::Feedback(SDLGame* game, double width, double height, Vector2D pos) :
	GameObject(game)
{
	setWidth(width);
	setHeight(height);
	setPosition(pos);
	setVelocity(Vector2D(0, 0));


	animation = *getGame()->getServiceLocator()->getTextures()->getAnimation(Resources::Blank);

	framesPerSecond = 4;
	isAnimationSyncedToMusic = true;

	timer = Timer::Instance();
}

void Feedback::render(Uint32 time, bool beatSync)
{

	animation.texture_->render(getRect(), getFrameRect());


	if ((!isAnimationSyncedToMusic && (time - lastRender) >= (1000 / framesPerSecond)) || (isAnimationSyncedToMusic && beatSync)) {	//animations update only when a certain time has passed OR when the "beatSync" signal is true
		animation.currentFrame = animation.currentFrame + 1;

		if (animation.currentFrame == animation.totalFrames) {
			animation.currentFrame = 0;
		}

		lastRender = time;

		if (queuedAnimations.size() > 0) {
			changeAnimation(queuedAnimations.front());
		}
	}
}

void Feedback::update(Uint32 time)
{
}
Feedback::~Feedback()
{
}

void Feedback::changeAnimation(int animationTag)
{
	timer->Reset();

	int currentFrame = animation.currentFrame;

	animation = *getGame()->getServiceLocator()->getTextures()->getAnimation(animationTag);
	if(!queuedAnimations.empty())
		queuedAnimations.pop();

	animation.currentFrame = currentFrame;
}