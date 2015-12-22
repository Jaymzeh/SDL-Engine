#ifndef STATE_LEVEL_TWO
#define STATE_LEVEL_TWO

#include "gamestate.h"
#include "map.h"
#include "player.h"

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
	Map* map = NULL;
	Player* player;
	vector<BoundingBox> mapBoxes;
};

#endif
