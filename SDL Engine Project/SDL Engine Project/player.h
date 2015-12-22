#ifndef PLAYER_H
#define PLAYER_H

#define FRAME_STEP 10

#include "SDL2-2.0.3-15\include\SDL.h"
#include "aniSprite.h"
#include "vector2.h"
#include "boundingBox.h"

class Player {
public:
	Player(float dx, float dy);

	void LoadSprites(Bitmap *bitmap[], int c[], int r[]);
	Vector2 getPosition() { return position; }
	void setPosition(Vector2 newPos);
	Vector2 getOldPosition() { return oldPosition; }
	BoundingBox getBox() { return box; }

	void setSprite(int i, AniSprite* newSprite) { sprite[i] = newSprite; }

	//void updateInput(sdlk)

	void move(float dx, float dy);
	void moveBack();
	void draw();

private:
	AniSprite* sprite[3];
	AniSprite* currentSprite;
	int direction = 0;
	int frames = 0;

	BoundingBox box;

	Vector2 position, oldPosition;
	int health;
	bool moving = false;
};

#endif
