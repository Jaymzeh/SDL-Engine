#include "player.h"
#include "character.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Player::Player(float dx, float dy, float _width, float _height) {
	position.setPoint(dx, dy);
	width = _width;
	height = _height;
	bBox.setBox(position.x, position.y, width, height);
	heartImage = new Bitmap("heart.bmp", true);
	coinImage = new Bitmap("coin.bmp", true);
	numbers = new AniSprite(0, 0, "numbers.bmp", 10, 1);
}

void Player::loadPlayerData(char* filePath) {
	string line;
	ifstream file(filePath);
	if (file.is_open()) {

		getline(file, line);
		health = stoi(line);
		
		getline(file, line);
		money = stoi(line);

		file.close();
		cout << "File contents: " << line << endl;
	}
	else {
		cout << "File '" << filePath << "' could not be loaded" << endl;
	}
}

void Player::savePlayerData(char* filePath) {
	string line;
	ofstream file(filePath);
	if (file.is_open()) {
		line = (to_string(health) + "\n" + to_string(money));

		file << line;
		file.close();
	}
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

			//Left
			if (position.x < enemies[i]->getPosition().x && currentDirection == 1)
				enemies[i]->setHealth(enemies[i]->getHealth() - 5);

			//Right
			if (position.x > enemies[i]->getPosition().x && currentDirection == 3)
				enemies[i]->setHealth(enemies[i]->getHealth() - 5);
			//Top
			if (position.y > enemies[i]->getPosition().y && currentDirection == 2)
				enemies[i]->setHealth(enemies[i]->getHealth() - 5);
			//Bottom
			if (position.y < enemies[i]->getPosition().y && currentDirection == 0)
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

void Player::showHealth(int dx, int dy) {
	for (int i = 0; i < health;i++) {
		heartImage->drawAt(dx + (i * heartImage->getWidth()), dy);
	}
}

void Player::showMoney(int dx, int dy) {
	coinImage->drawAt(dx, dy);
	if (money < 10) {
		
	}

}


Player::~Player() {
	for (int i = 0; i < ARRAYSIZE(sprite); i++)
		delete sprite[i];
	delete currentSprite;
}
