#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "vector2.h"
#include "boundingBox.h"
#include "aniSprite.h"

class Projectile {
public:
	Projectile(float px, float py, float dx, float dy, AniSprite* newSprite) {
		position.setPoint(px, py);
		spawnPosition = position;
		velocity.setPoint(dx, dy);
		sprite = newSprite;
		bBox.setBox(position.x, position.y, sprite->getWidth(), sprite->getHeight());
	}

	void move() {
		position.add(velocity);
		sprite->moveTo(position.x, position.y);
		bBox.setBox(position.x, position.y, sprite->getWidth(), sprite->getHeight());
	}

	void render() {
		sprite->draw();
	}

private:
	Vector2 position, spawnPosition;
	Vector2 velocity;
	BoundingBox bBox;
	AniSprite* sprite;
};

#endif
