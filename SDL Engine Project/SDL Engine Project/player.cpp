#include "player.h"
#include <iostream>

Player::Player(float dx, float dy) {
	position.setPoint(dx, dy);
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

	sprite[0]->move(dx, dy);
	sprite[1]->move(dx, dy);
	sprite[2]->move(dx, dy);

	oldPosition = position;

	position.x += dx;
	position.y += dy;
	box.setBox(position.x, position.y, 32, 32);
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

	if (frames++ >= FRAME_STEP) {
		currentSprite->nextCell();
		frames = 0;
	}

	
	/*glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2f(position.x, position.y);
	glVertex2f(position.x + 32, position.y);
	glVertex2f(position.x + 32, position.y + 32);
	glVertex2f(position.x, position.y + 32);
	glEnd();*/

	currentSprite->draw();

	//box.render();
}