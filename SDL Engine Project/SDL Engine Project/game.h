#ifndef GAME

#define WINDOWWIDTH 1024
#define WINDOWHEIGHT 768
#define VIEWWIDTH 256
#define VIEWHEIGHT 256

#include "gamestate.h"
#include "bass.h"
#include "SDL2-2.0.3-15\include\SDL.h"
#include "SDL2-2.0.3-15\include\SDL_opengl.h"

class Game{
public:
	Game();
	~Game();

	void init();
	void run();

	void setState(GameState* newState);
	GameState* getMainMenuState();
	GameState* getLevelOne();
	GameState* getLevelTwo();

	//bool keysHeld[323] = { false };
private:
	SDL_Window* window;
	SDL_GLContext glContext;

	static int instances;

	HSAMPLE musicSample;
	HSAMPLE sample;
	HCHANNEL musicChannel, sfxChannel;

	void setupRC();
	
	GameState* currentState;
	GameState* mainMenuState;
	GameState* levelOneState;
	GameState* levelTwoState;
};
#endif