#ifndef KEY_H
#define KEY_H

#include "vector2.h"
#include "boundingBox.h"
#include "bitmap.h"
#include "door.h"

class Key {
public:
	void createKey(int dx, int dy, Bitmap* newSprite) {
		position.setPoint(dx, dy);
		sprite = newSprite;
		spriteWidth = sprite->getWidth();
		spriteHeight = sprite->getHeight();
		bBox.setBox(position.x, position.y, spriteWidth, spriteHeight);
	}

	void unlockDoor(Door door) {
		door.unlocked = true;
	}

	BoundingBox getBox() { return bBox; }

	void render() {
		sprite->drawAt(position.x, position.y);
		bBox.render();
	}
private:
	Vector2 position;
	BoundingBox bBox;
	Bitmap* sprite;
	int spriteWidth, spriteHeight;
};

#endif
