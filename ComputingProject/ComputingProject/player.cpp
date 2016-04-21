#include "player.h"
#include "character.h"

Player::Player(float dx, float dy, float _width, float _height) {
	position.setPoint(dx, dy);
	width = _width;
	height = _height;
	bBox.setBox(position.x, position.y, width, height);
}

void Player::setSprite(int i, AniSprite* newSprite) {
	sprite[i] = newSprite;
}

void Player::move(float dx, float dy) {
	if (dx > 0)
		currentDirection = RIGHT;
	else
		if (dx < 0)
			currentDirection = LEFT;

	if (dy > 0)
		currentDirection = UP;
	else
		if (dy < 0)
			currentDirection = DOWN;
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

void Player::attack(std::vector<BaseCharacter*>& enemies) {
	if (attacking)
		return;

	attacking = true;

	for (int i = 0; i < enemies.size(); i++) {
		if (enemies[i]->getPosition().distance(position) <= width*1.5f) {
			enemies[i]->setHealth(enemies[i]->getHealth() - 5);
			break;
		}
	}

}

void Player::render() {
	switch (currentDirection) {
	case UP:	//up
		currentSprite = sprite[0];
		break;
	case RIGHT:	//right
		if (attacking)
			currentSprite = sprite[4];
		else
			currentSprite = sprite[1];
		currentSprite->setDrawmode(DrawMode::NOFLIP);
		break;
	case DOWN:	//down
		if (attacking)
			currentSprite = sprite[3];
		else
			currentSprite = sprite[2];
		break;
	case LEFT:	//left
		if (attacking)
			currentSprite = sprite[4];
		else
			currentSprite = sprite[1];
		currentSprite->setDrawmode(DrawMode::FLIPCELL);
		break;
	}

	if (attacking && attackFrames++ >= ATTACK_FRAMES) {

		attackFrames = 0;
		attacking = false;
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
