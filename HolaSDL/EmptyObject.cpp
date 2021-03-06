#include "EmptyObject.h"

EmptyObject::EmptyObject(SDLGame* game, Vector2D pos, int width, int height, int texture) : GameObject(game)
{
	setPosition(pos);
	animation = *getGame()->getServiceLocator()->getTextures()->getAnimation(texture);
	setWidth(width);
	setHeight(height);
}

EmptyObject::~EmptyObject()
{
}

void EmptyObject::render(Uint32 time, bool beatSync) {

	if(active_)
		animation.texture_->render(getRect(), &getFrameRect(), alpha_);

}

void EmptyObject::changeFrame() {	//method used to change a sprite's animation's frame
	animation.currentFrame = animation.currentFrame + 1;

	if (animation.currentFrame == animation.totalFrames) {
		animation.currentFrame = 0;
	}
}
