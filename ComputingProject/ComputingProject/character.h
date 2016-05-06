#ifndef CHARACTER_H
#define CHARACTER_H

#define FRAME_STEP 10

#include "vector2.h"
#include "boundingBox.h"
#include "aniSprite.h"
/*
Base abstract class for characters
*/
class BaseCharacter {
public:

	virtual void setSprite(int i, AniSprite* newSprite) = 0;
	virtual void move(float dx, float dy) = 0;
	virtual void moveBack() = 0;
	virtual void knockBack(int _direction) = 0;
	virtual void setPosition(Vector2 newPos) = 0;
	virtual void setPosition(float dx, float dy) = 0;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void setTarget(Vector2 _target) = 0;
	virtual Vector2 getTarget() = 0;
	virtual BoundingBox getBox() = 0;
	virtual Vector2 getPosition() = 0;
	virtual Vector2 getOldPosition() = 0;
	virtual int getHealth() = 0;
	virtual void resetAttackCooldown() = 0;
	virtual void setHealth(int _health) = 0;
	virtual void updateAttackCooldown() = 0;
	virtual int getAttackCooldown() = 0;
	virtual ~BaseCharacter() {};

};

class Character : public BaseCharacter {
private:
	Vector2 position, oldPosition;
	AniSprite* sprite[3];
	AniSprite* currentSprite;
	enum Direction { UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3 };
	Direction currentDirection = UP;
	int frames = 0;
	int knockBackCooldown = 0;
public:
	Character(float dx, float dy, float charSize) {
		position.setPoint(dx, dy);
		width = height = charSize;
		bBox.setBox(position.x, position.y, width, height);
	}

	void setSprite(int i, AniSprite* newSprite) {
		sprite[i] = newSprite;
	}
	void move(float dx, float dy) {
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
	void moveBack() {
		setPosition(oldPosition);
	}

	//new
	void knockBack(int _direction) {
		if (knockBackCooldown < 1) {
			//std::cout << "knockback" << std::endl;
			Vector2 tempPos;
			tempPos.x = position.x;
			tempPos.y = position.y;

			if (_direction == 2)
				tempPos.y -= 32;
			if (_direction == 0)
				tempPos.y += 32;
			if (_direction == 1)
				tempPos.x += 32;
			if (_direction == 3)
				tempPos.x -= 32;

			std::cout << "tempPos" << tempPos.x << tempPos.y << " Direction" << _direction << std::endl;
			setPosition(tempPos);

			knockBackCooldown = 40;
		}
	}
	void setPosition(Vector2 newPos) {
		position = newPos;
		for (int i = 0; i < ARRAYSIZE(sprite); i++)
			sprite[i]->moveTo(position.x, position.y);
		bBox.setBox(position.x, position.y, width, height);
	}
	void setPosition(float dx, float dy) {
		position.setPoint(dx, dy);
		for (int i = 0; i < ARRAYSIZE(sprite); i++)
			sprite[i]->moveTo(position.x, position.y);
		bBox.setBox(position.x, position.y, 32, 32);
	}

	void update() {
		float dx = 0;
		float dy = 0;
		knockBackCooldown--;

		Vector2 pos = target;

		if (pos.x != 0 && pos.y != 0) {
			if (pos.x < position.x) {
				dx = -1;
			}
			else
				if (pos.x > position.x)
					dx = 1;

			if (pos.y < position.y)
				dy = -1;
			else
				if (pos.y > position.y)
					dy = 1;
			move(dx, dy);
		}
	};

	void render() {
		switch (currentDirection) {
		case UP:	//up
			currentSprite = sprite[0];
			break;
		case RIGHT:	//right
			currentSprite = sprite[1];
			currentSprite->setDrawmode(DrawMode::NOFLIP);
			break;
		case DOWN:	//down
			currentSprite = sprite[2];
			break;
		case LEFT:	//left
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

	void setTarget(Vector2 _target) { target = _target; };
	Vector2 getTarget() { return target; }

	BoundingBox getBox() { return bBox; }
	Vector2 getPosition() { return position; }
	Vector2 getOldPosition() { return oldPosition; }
	int getHealth() { return health; }
	void setHealth(int _health) { health = _health; }
	void resetAttackCooldown() {
		attackCooldown = 0;
	}
	void updateAttackCooldown() {
		attackCooldown++;
	}
	int getAttackCooldown() {
		return attackCooldown;
	}
	~Character() {
		for (int i = 0; i < ARRAYSIZE(sprite); i++)
			delete sprite[i];
		//delete currentSprite;
	}

protected:
	int health;
	int attackCooldown;
	int baseAttackCooldown = 120;
	float width, height;
	Vector2 target;
	BoundingBox bBox;
};

class CharacterDecorator :public BaseCharacter {
private:
	BaseCharacter* character;

public:
	CharacterDecorator(BaseCharacter* c) { character = c; }
	void setSprite(int i, AniSprite* newSprite) { character->setSprite(i, newSprite); }
	void move(float dx, float dy) { character->move(dx, dy); };
	void moveBack() { character->moveBack(); }
	void knockBack(int _direction) { character->knockBack(_direction); }
	void setPosition(Vector2 newPos) { character->setPosition(newPos); }
	void setPosition(float dx, float dy) { character->setPosition(dx, dy); }
	void update() { character->update(); }
	void render() { character->render(); }
	void setTarget(Vector2 _target) { character->setTarget(_target); };
	Vector2 getTarget() { return character->getTarget(); }
	BoundingBox getBox() { return character->getBox(); }
	Vector2 getPosition() { return character->getPosition(); }
	Vector2 getOldPosition() { return character->getOldPosition(); }
	int getHealth() { return character->getHealth(); }
	void setHealth(int _health) { character->setHealth(_health); }
	void resetAttackCooldown() { character->resetAttackCooldown(); }
	void updateAttackCooldown() { character->updateAttackCooldown(); }
	int getAttackCooldown() { return character->getAttackCooldown(); }
	~CharacterDecorator() { delete character; }
};

class Slime : public CharacterDecorator {
public:
	Slime(BaseCharacter* c) : CharacterDecorator(c) { setHealth(5); }
	void setSprite(int i, AniSprite* newSprite) { CharacterDecorator::setSprite(i, newSprite); }
	void move(float dx, float dy) { CharacterDecorator::move(dx, dy); }
	void moveBack() { CharacterDecorator::moveBack(); }
	void knockBack(int _direction) { CharacterDecorator::knockBack(_direction); }
	void setPosition(Vector2 newPos) { CharacterDecorator::setPosition(newPos); }
	void setPosition(float dx, float dy) { CharacterDecorator::setPosition(dx, dy); }
	void update() { CharacterDecorator::update(); }
	void render() { CharacterDecorator::render(); }
	void setTarget(Vector2 _target) { CharacterDecorator::setTarget(_target); };
	Vector2 getTarget() { return CharacterDecorator::getTarget(); }
	BoundingBox getBox() { return CharacterDecorator::getBox(); }
	Vector2 getPosition() { return CharacterDecorator::getPosition(); }
	Vector2 getOldPosition() { return CharacterDecorator::getOldPosition(); }
	int getHealth() { return CharacterDecorator::getHealth(); }
	void setHealth(int _health) { CharacterDecorator::setHealth(_health); }
	void resetAttackCooldown() { CharacterDecorator::resetAttackCooldown(); }
	void updateAttackCooldown() { CharacterDecorator::updateAttackCooldown(); }
	int getAttackCooldown() { return CharacterDecorator::getAttackCooldown(); }
	~Slime() {};
};

class Rat : public CharacterDecorator {
public:
	Rat(BaseCharacter* c) : CharacterDecorator(c) { setHealth(10); }
	void setSprite(int i, AniSprite* newSprite) { CharacterDecorator::setSprite(i, newSprite); }
	void move(float dx, float dy) { CharacterDecorator::move(dx, dy); }
	void moveBack() { CharacterDecorator::moveBack(); }
	void knockback(int _direction) { CharacterDecorator::knockBack(_direction); }
	void setPosition(Vector2 newPos) { CharacterDecorator::setPosition(newPos); }
	void setPosition(float dx, float dy) { CharacterDecorator::setPosition(dx, dy); }
	void update() { CharacterDecorator::update(); }
	void render() { CharacterDecorator::render(); }
	void setTarget(Vector2 _target) { CharacterDecorator::setTarget(_target); };
	Vector2 getTarget() { return CharacterDecorator::getTarget(); }
	BoundingBox getBox() { return CharacterDecorator::getBox(); }
	Vector2 getPosition() { return CharacterDecorator::getPosition(); }
	Vector2 getOldPosition() { return CharacterDecorator::getOldPosition(); }
	int getHealth() { return CharacterDecorator::getHealth(); }
	void setHealth(int _health) { CharacterDecorator::setHealth(_health); }
	void resetAttackCooldown() { CharacterDecorator::resetAttackCooldown(); }
	void updateAttackCooldown() { CharacterDecorator::updateAttackCooldown(); }
	int getAttackCooldown() { return CharacterDecorator::getAttackCooldown(); }
	~Rat() {};
private:

};

#endif