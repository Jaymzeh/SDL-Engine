#ifndef STATE_MAIN_MENU_H
#define STATE_MAIN_MENU_H


#include "gamestate.h"
#include "bass.h"
#include "aniSprite.h"
#include <iostream>

using std::cout;
using std::endl;

class StateMainMenu : public GameState {
public:

	StateMainMenu();
	~StateMainMenu();
	void init(Game& context);
	void update(Game& context);
	void draw(SDL_Window* window);
	void handleSDLEvent(SDL_Event const &sdlEvent, Game& context);
	void enter();
	void exit();

private:

	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	Bitmap* background;

	HSAMPLE sample;
};

#endif