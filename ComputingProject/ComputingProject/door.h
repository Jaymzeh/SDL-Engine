#ifndef DOOR_H
#define DOOR_H

#include "vector2.h"
#include "boundingBox.h"
#include "bitmap.h"

class Door {
public:
	void createDoor(float dx, float dy, Bitmap* newSprite) {
		position.setPoint(dx, dy);
		sprite = newSprite;
		spriteWidth = sprite->getWidth();
		spriteHeight = sprite->getHeight();
		bBox.setBox(position.x, position.y, spriteWidth, spriteHeight);

		unlocked = false;
	}

	BoundingBox getBox() { return bBox; }

	void render() {
		sprite->drawAt(position.x, position.y);
		//bBox.render();
	}

	void deleteDoor() {
		delete sprite;
	}

	bool unlocked = false;

private:
	Vector2 position;
	BoundingBox bBox;
	Bitmap* sprite;
	float spriteWidth, spriteHeight;

};

#endif

