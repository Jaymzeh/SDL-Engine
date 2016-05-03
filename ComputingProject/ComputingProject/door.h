#ifndef DOOR_H
#define DOOR_H

#include "vector2.h"
#include "boundingBox.h"
#include "bitmap.h"

class Door {
public:
	void createDoor(int dx, int dy, Bitmap* newSprite) {
		position.setPoint(dx, dy);
		sprite = newSprite;
		spriteWidth = sprite->getWidth();
		spriteHeight = sprite->getHeight();
		bBox.setBox(position.x, position.y, spriteWidth, spriteHeight);
	}

	BoundingBox getBox() { return bBox; }

	void render() {
		sprite->drawAt(position.x, position.y);
		bBox.render();
	}

	bool unlocked = false;

private:
	Vector2 position;
	BoundingBox bBox;
	Bitmap* sprite;
	int spriteWidth, spriteHeight;

};

#endif

