#include "player.h"
#include "character.h"

	Player::Player(float dx, float dy, float charSize) {
		position.setPoint(dx, dy);
		width = height = charSize;
		bBox.setBox(position.x, position.y, width, height);
	}

	void Player::setSprite(int i, AniSprite* newSprite) {
		sprite[i] = newSprite;
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

		for (int i = 0; i < ARRAYSIZE(sprite); i++)
			sprite[i]->move(dx, dy);

		oldPosition = position;
		position.x += dx;
		position.y += dy;
		bBox.setBox(position.x, position.y, width, height);
	}
	void Player::moveBack() {
		setPosition(oldPosition);
	}

	void Player::handleInputX(const Uint8* keystate) {
		if (keystate[SDL_SCANCODE_A])
			move(-moveSpeed, 0);
		else
			if (keystate[SDL_SCANCODE_D])
				move(moveSpeed, 0);
	}

	void Player::handleInputY(const Uint8* keystate) {
		if (keystate[SDL_SCANCODE_W])
			move(0, moveSpeed);
		else
			if (keystate[SDL_SCANCODE_S])
				move(0, -moveSpeed);
	}

	void Player::setPosition(Vector2 newPos) {
		position = newPos;
		for (int i = 0; i < ARRAYSIZE(sprite); i++)
			sprite[i]->moveTo(position.x, position.y);
		bBox.setBox(position.x, position.y, width, height);
	}
	void Player::setPosition(float dx, float dy) {
		position.setPoint(dx, dy);
		for (int i = 0; i < ARRAYSIZE(sprite); i++)
			sprite[i]->moveTo(position.x, position.y);
		bBox.setBox(position.x, position.y, 32, 32);
	}

	void Player::attack() {

	}

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

		//bBox.render();
	}

	Player::~Player() {
		for (int i = 0; i < ARRAYSIZE(sprite); i++)
			delete sprite[i];
		delete currentSprite;
	}
