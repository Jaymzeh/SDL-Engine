#ifndef SHOP_H
#define SHOP_H

#include "vector2.h"
#include "boundingBox.h"
#include "bitmap.h"

class Shop {
public:
	void spawnShop(int dx, int dy, Bitmap* shop) {
		position.setPoint(dx, dy);

		sprite = shop;
		spriteWidth = sprite->getWidth();
		spriteHeight = sprite->getHeight();

		//bboxes
		mainbBox.setBox(position.x, position.y, spriteWidth, spriteHeight);
		bBoxOption1.setBox(position.x, position.y, 57, 43);
		bBoxOption2.setBox(position.x + 68, position.y, 57, 43);
		bBoxOption3.setBox(position.x + 135, position.y, 57, 43);
	}

	BoundingBox getMainbBox() { return mainbBox; }
	BoundingBox getbBoxOption1() { return bBoxOption1; }
	BoundingBox getbBoxOption2() { return bBoxOption2; }
	BoundingBox getbBoxOption3() { return bBoxOption3; }

	int inShopSelection = 0;
	int selectionCooldown = 0;
	bool inShop;

	void render() {
		sprite->drawAt(position.x, position.y);

		//bboxes render
		mainbBox.render();
		bBoxOption1.render();
		bBoxOption2.render();
		bBoxOption3.render();
	}

private:

	Vector2 position;
	BoundingBox mainbBox, bBoxOption1, bBoxOption2, bBoxOption3, blockingBox1, blockingBox2, blockingBox3;
	Bitmap* sprite;
	int spriteWidth, spriteHeight;
};

#endif

