#ifndef KEY_H
#define KEY_H

#include "vector2.h"
#include "boundingBox.h"
#include "bitmap.h"
#include "door.h"

class Key {
public:
	void createKey(float dx, float dy, Bitmap* newSprite) {
		position.setPoint(dx, dy);
		sprite = newSprite;
		spriteWidth = sprite->getWidth();
		spriteHeight = sprite->getHeight();
		bBox.setBox(position.x, position.y, spriteWidth, spriteHeight);
	}

	void deleteKey() {
		delete sprite;
	}

	BoundingBox getBox() { return bBox; }

	void render() {
		sprite->drawAt(position.x, position.y);
		//bBox.render();
	}
private:
	Vector2 position;
	BoundingBox bBox;
	Bitmap* sprite;
	float spriteWidth, spriteHeight;
};

#endif
