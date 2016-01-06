#ifndef PLAYER_H
#define PLAYER_H

#define FRAME_STEP 10

#include "aniSprite.h"
#include "vector2.h"
#include "boundingBox.h"
#include "SDL2-2.0.3-15\include\SDL.h"

class Player {
public:
	Player(float dx, float dy, float charSize);

	void setSprite(int i, AniSprite* newSprite);
	void move(float dx, float dy);
	void moveBack();
	void handleInputX(const Uint8* keystate);
	void handleInputY(const Uint8* keystate);
	void setPosition(Vector2 newPos);
	void setPosition(float dx, float dy);

	void attack();

	void render();

	BoundingBox getBox() { return bBox; }
	Vector2 getPosition() { return position; }
	Vector2 getOldPosition() { return oldPosition; }

	~Player();
private:
	int health;
	float width, height;
	float moveSpeed = 1;
	BoundingBox bBox;
	Vector2 position, oldPosition;
	AniSprite* sprite[3];
	AniSprite* currentSprite;
	int direction;
	int frames = 0;
};
#endif
