#ifndef GAME_H
#define GAME_H

#define WINDOWWIDTH 1024
#define WINDOWHEIGHT 768
#define VIEWWIDTH 256
#define VIEWHEIGHT 256

#include "gamestate.h"
#include "bass.h"
#include "SDL2-2.0.3-15\include\SDL.h"
#include "SDL2-2.0.3-15\include\SDL_opengl.h"

class Game {
public:
	Game();
	~Game();

	void init();
	void run();

	void setShowDebug(bool show) { showDebug = true; }

	HCHANNEL getMusicChannel() { return musicChannel; }
	HCHANNEL getSfxChannel() { return sfxChannel; }

	void setState(GameState* newState);
	GameState* getMainMenuState();
	GameState* getGameOver();
	GameState* getGameEnd();
	GameState* getLevelShop();
	GameState* getLevelOne();
	GameState* getLevelTwo();
	GameState* getLevelThree();

private:
	SDL_Window* window;
	SDL_GLContext glContext;

	static int instances;
	static bool showDebug;

	HSAMPLE musicSample;
	HSAMPLE sample;
	HCHANNEL musicChannel, sfxChannel;

	void setupRC();

	GameState* currentState;
	GameState* mainMenuState;
	GameState* gameOverState;
	GameState* gameEndState;
	GameState* shopLevel;
	GameState* levelOneState;
	GameState* levelTwoState;
	GameState* levelThreeState;
};
#endif