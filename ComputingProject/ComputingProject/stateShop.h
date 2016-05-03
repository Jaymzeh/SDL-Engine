#ifndef STATE_SHOP_H
#define STATE_SHOP_H

#include "gamestate.h"
#include "shop.h"
#include "map.h"
#include "character.h"
#include "player.h"
#include "door.h"
#include "key.h"
#include "bass.h"

class StateShop : public GameState {
public:

	StateShop();
	~StateShop();
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
	Shop shop;
	vector<BoundingBox> mapBoxes;
	Door door;
	HSAMPLE sample;
};

#endif
