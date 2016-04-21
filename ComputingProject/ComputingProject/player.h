#ifndef PLAYER_H
#define PLAYER_H

#define FRAME_STEP 10
#define ATTACK_FRAMES 15

#include "aniSprite.h"
#include "vector2.h"
#include <vector>
#include "boundingBox.h"
#include "character.h"
//#include <SDL.h>
#include "SDL2-2.0.3-15\include\SDL.h"

class Player {
public:
	Player(float dx, float dy, float _width, float _height);

	void setSprite(int i, AniSprite* newSprite);
	void move(float dx, float dy);
	void moveBack();
	void handleInputX(const Uint8* keystate);
	void handleInputY(const Uint8* keystate);
	void setPosition(Vector2 newPos);
	void setPosition(float dx, float dy);

	void attack(std::vector<BaseCharacter*>& enemies);

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
	AniSprite* sprite[5];
	AniSprite* currentSprite;
	enum Direction { UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3 };
	Direction currentDirection = UP;
	int frames = 0;
	int attackFrames = 0;
	bool attacking = false;
};
#endif
