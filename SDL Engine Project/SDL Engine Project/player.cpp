#include "player.h"
#include <iostream>
#include "SDL2-2.0.3-15\include\SDL.h"

/*
Initializes Player class

@param dx - initial X position
@param dy - initial Y position
*/
Player::Player(float dx, float dy) {
	position.setPoint(dx, dy);
}

/*
Move the player

@param dx - Amount to move the player on the X axis
@param dy - Amount to move the player on the Y axis
*/
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

	for (int i = 0; i < ARRAYSIZE(sprite); i++)
		sprite[i]->move(dx, dy);

	oldPosition = position;
	position.x += dx;
	position.y += dy;
	box.setBox(position.x, position.y, 32, 32);

}

/*
Move the player back to the last known position
*/
void Player::moveBack() {
	setPosition(oldPosition);
}

/*
Set the player's position at a specific location

@param newPos - The new position to place the player
*/
void Player::setPosition(Vector2 newPos) {
	position = newPos;
	for (int i = 0; i < ARRAYSIZE(sprite); i++)
		sprite[i]->moveTo(position.x, position.y);
	box.setBox(position.x, position.y, 32, 32);
}

/*
Draw the player at the player's position
*/
void Player::render() {
	
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

	box.render();
}