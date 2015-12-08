#include "player.h"

Player::Player(float dx, float dy) {
	position.setPoint(dx, dy);
}

void Player::move(float dx, float dy) {

	if (dx > 0)
		direction = 1;
	else
		if (dx < 0)
			direction = 3;

	if (dy > 0)
		direction = 0;
	else
		if (dy < 0)
			direction = 2;

	sprite[0]->move(dx, dy);
	sprite[1]->move(dx, dy);
	sprite[2]->move(dx, dy);
	position.x += dx;
	position.y += dy;
}

void Player::draw() {
	
	switch (direction) {
	case 0:
		currentSprite = sprite[0];
		break;
	case 1:
		currentSprite = sprite[1];
		currentSprite->setDrawmode(DrawMode::NOFLIP);
		break;
	case 2:
		currentSprite = sprite[2];
		break;
	case 3:
		currentSprite = sprite[1];
		currentSprite->setDrawmode(DrawMode::FLIPCELL);
		break;
	}

	if (frames++ >= FRAME_STEP) {
		currentSprite->nextCell();
		frames = 0;
	}

	currentSprite->draw();

}