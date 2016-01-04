#ifndef STATE_LEVEL_ONE_H
#define STATE_LEVEL_ONE_H

#include "gamestate.h"
#include "map.h"
#include "character.h"
#include "player.h"

class StateLevelOne : public GameState {
public:

	StateLevelOne();
	~StateLevelOne();
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
};

#endif
