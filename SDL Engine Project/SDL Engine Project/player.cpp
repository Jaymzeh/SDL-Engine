#include "player.h"
#include <iostream>
#include "SDL2-2.0.3-15\include\SDL.h"

Player::Player(float dx, float dy) {
	position.setPoint(dx, dy);
	
	//glPopMatrix();
	
	int width = 256;
	int height = 256;
	int left = (position.x + 16) - (width / 2);
	int top =(position.y+16) + (height / 2);
	//glOrtho(left, left + width, top - height, top, 0, 1);
}

void Player::LoadSprites(Bitmap *bitmap[], int c[], int r[]) {
	for (int i = 0; i < 3; i++) {
		sprite[i] = new AniSprite(position.x, position.y, bitmap[i], c[i], r[i]);
		std::cout << sprite[i] << std::endl;
	}
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

	if (dx != 0 && dy != 0)
		moving = true;
	else
		moving = false;

	sprite[0]->move(dx, dy);
	sprite[1]->move(dx, dy);
	sprite[2]->move(dx, dy);

	oldPosition = position;
	position.x += dx;
	position.y += dy;
	box.setBox(position.x, position.y, 32, 32);

}

void Player::moveBack() {
	setPosition(oldPosition);
}

void Player::setPosition(Vector2 newPos) {
	position = newPos;
	for (int i = 0; i < 3; i++)
		sprite[i]->moveTo(position.x, position.y);
	box.setBox(position.x, position.y, 32, 32);
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
	if (moving) {
		if (frames++ >= FRAME_STEP) {
			currentSprite->nextCell();
			frames = 0;
		}
	}
	else
		frames = 0;

	currentSprite->draw();

	box.render();
}