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

	Vector2 getPosition() { return position; }	

	//void updateInput(sdlk)

	void move(float dx, float dy);
	void draw();

private:
	AniSprite* sprite[3];
	AniSprite* currentSprite;
	int direction = 0;
	int frames = 0;

	Vector2 position;
	int health;
};

#endif
