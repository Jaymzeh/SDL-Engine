#ifndef STATE_TEST_LEVEL
#define STATE_TEST_LEVEL

#include "gamestate.h"
#include "map.h"
#include "player.h"

class StateTestLevel : public GameState {
public:

	StateTestLevel();
	~StateTestLevel();
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
