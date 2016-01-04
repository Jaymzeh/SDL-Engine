#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "SDL2-2.0.3-15\include\SDL.h"

class Game;

class GameState {
public:
	virtual ~GameState() { return; } // need a virtual destructor
	virtual void draw(SDL_Window* window) = 0;
	virtual void init(Game& context) = 0;
	virtual void update(Game& context) = 0;
	virtual void enter() = 0;
	virtual void exit() = 0;
	virtual void handleSDLEvent(SDL_Event const& sdlEvent, Game& context) = 0;
};

#endif