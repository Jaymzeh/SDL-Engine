#ifndef STATE_LEVEL_ONE
#define STATE_LEVEL_ONE

#include "gamestate.h"
#include "map.h"
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
	Map* map = NULL;
	Player* player;
	vector<BoundingBox> mapBoxes;
};

#endif
