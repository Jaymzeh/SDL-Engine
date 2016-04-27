#ifndef STATE_LEVEL_TWO_H
#define STATE_LEVEL_TWO_H

#include "gamestate.h"
#include "map.h"
#include "character.h"
#include "player.h"
#include "door.h"
#include "key.h"
#include "bass.h"

class StateLevelTwo : public GameState {
public:

	StateLevelTwo();
	~StateLevelTwo();
	void init(Game& context);
	void update(Game& context);
	void draw(SDL_Window* window);
	void handleSDLEvent(SDL_Event const &sdlEvent, Game& context);
	void enter();
	void exit();

private:

	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	Map* map = NULL;
	Player* player;
	vector<BaseCharacter*> character;
	vector<BoundingBox> mapBoxes;
	Key key;
	Door door;
	HSAMPLE sample;
};

#endif
