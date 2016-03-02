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
	virtual void setPosition(Vector2 newPos) = 0;
	virtual void setPosition(float dx, float dy) = 0;
	virtual void render() = 0;
	virtual BoundingBox getBox() = 0;
	virtual Vector2 getPosition() = 0;
	virtual Vector2 getOldPosition() = 0;
	virtual int getHealth() = 0;
	virtual void setHealth(int _health) = 0;
	virtual ~BaseCharacter() {};
};

class Character : public BaseCharacter {
private:
	Vector2 position, oldPosition;
	AniSprite* sprite[3];
	AniSprite* currentSprite;
	int direction;
	int frames = 0;
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
	void moveBack() {
		setPosition(oldPosition);
	}

	void setPosition(Vector2 newPos) {
		position = newPos;
		for (int i = 0; i < ARRAYSIZE(sprite); i++)
			sprite[i]->moveTo(position.x, position.y);
		bBox.setBox(position.x, position.y, width, height);
	}
	void setPosition(float dx, float dy){
		position.setPoint(dx,dy);
		for (int i = 0; i < ARRAYSIZE(sprite); i++)
			sprite[i]->moveTo(position.x, position.y);
		bBox.setBox(position.x, position.y, 32, 32);
	}

	void render() {
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

		bBox.render();
	}

	BoundingBox getBox() { return bBox; }
	Vector2 getPosition() { return position; }
	Vector2 getOldPosition() { return oldPosition; }
	int getHealth() { return health; }
	void setHealth(int _health) { health = _health; }

	~Character() {
		for (int i = 0; i < ARRAYSIZE(sprite); i++)
			delete sprite[i];
		//delete currentSprite;
	}

protected:
	int health;
	float width, height;
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
	void setPosition(Vector2 newPos) { character->setPosition(newPos); }
	void setPosition(float dx, float dy) { character->setPosition(dx, dy); }
	void render() { character->render(); }
	BoundingBox getBox() { return character->getBox(); }
	Vector2 getPosition() { return character->getPosition(); }
	Vector2 getOldPosition() { return character->getOldPosition(); }
	int getHealth() { return character->getHealth(); }
	void setHealth(int _health) { character->setHealth(_health); }
	~CharacterDecorator() { delete character; }
};



class Slime : public CharacterDecorator {
public:
	Slime(BaseCharacter* c) : CharacterDecorator(c) { }
	void setSprite(int i, AniSprite* newSprite) { CharacterDecorator::setSprite(i, newSprite); }
	void move(float dx, float dy) { CharacterDecorator::move(dx, dy); }
	void moveBack() { CharacterDecorator::moveBack(); }
	void setPosition(Vector2 newPos) { CharacterDecorator::setPosition(newPos); }
	void setPosition(float dx, float dy) { CharacterDecorator::setPosition(dx,dy); }
	void render() { CharacterDecorator::render(); }
	BoundingBox getBox() { return CharacterDecorator::getBox(); }
	Vector2 getPosition() { return CharacterDecorator::getPosition(); }
	Vector2 getOldPosition() { return CharacterDecorator::getOldPosition(); }
	~Slime() {};
};

class Orc : public CharacterDecorator {
public:
	Orc(BaseCharacter* c) : CharacterDecorator(c) { }
	void setSprite(int i, AniSprite* newSprite) { CharacterDecorator::setSprite(i, newSprite); }
	void move(float dx, float dy) { CharacterDecorator::move(dx, dy); }
	void moveBack() { CharacterDecorator::moveBack(); }
	void setPosition(Vector2 newPos) { CharacterDecorator::setPosition(newPos); }
	void setPosition(float dx, float dy) { CharacterDecorator::setPosition(dx, dy); }
	void render() { CharacterDecorator::render(); }
	BoundingBox getBox() { return CharacterDecorator::getBox(); }
	Vector2 getPosition() { return CharacterDecorator::getPosition(); }
	Vector2 getOldPosition() { return CharacterDecorator::getOldPosition(); }
	~Orc() {};
private:

};



#endif

