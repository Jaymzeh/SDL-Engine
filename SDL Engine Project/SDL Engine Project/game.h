#ifndef GAME

#define WINDOWWIDTH 1024
#define WINDOWHEIGHT 768

#include <iostream>
#include "gamestate.h"

#include "SDL2-2.0.3-15\include\SDL.h"
#include "SDL2-2.0.3-15\include\SDL_opengl.h"

class Game{
public:
	Game();
	~Game();

	void init();
	void run();
private:
	SDL_Window* window;
	SDL_GLContext glContext;

	static int instances;

	void setupRC();
	void setState(GameState* newState);
	GameState* currentState;
	GameState* mainMenuState;
	GameState* testLevelState;
};
#endif