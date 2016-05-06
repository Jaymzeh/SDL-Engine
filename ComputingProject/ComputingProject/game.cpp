#include "game.h"
#include "stateMainMenu.h"
#include "stateGameOver.h"
#include "stateGameEnd.h"
#include "stateShop.h"
#include "stateLevelOne.h"
#include "stateLevelTwo.h"
#include "stateLevelThree.h"

void exitFatalError(char *message) {
	std::cout << message << " " << SDL_GetError();
	SDL_Quit();
	exit(1);
}

int Game::instances = 0;

Game::Game() {
	instances++;
	if (instances > 1)
		exitFatalError("Attempt to create multiple game instances");
	setupRC();
}
Game::~Game() {

}

void Game::setupRC() {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) // Initialize video
		exitFatalError("Unable to initialize SDL");

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	window = SDL_CreateWindow("Group 3: Dungeon Peril",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WINDOWWIDTH, WINDOWHEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (!window)
		exitFatalError("Unable to create window");

	glContext = SDL_GL_CreateContext(window);

	SDL_GL_SetSwapInterval(1);

	//Audio
	BASS_Init(-1, 44100, 0, 0, NULL);
	musicSample = BASS_SampleLoad(false, "Exploring a cave.mp3", 0, 0, 1, BASS_SAMPLE_MONO | BASS_SAMPLE_LOOP);
	sample = BASS_SampleLoad(false, "sword_sheath_1.wav", 0, 0, 1, BASS_SAMPLE_MONO);

	musicChannel = BASS_SampleGetChannel(musicSample, TRUE);
	sfxChannel = BASS_SampleGetChannel(sample, FALSE);
}
/*
Initialise all the game states
*/
void Game::init() {
	BASS_ChannelPlay(musicChannel, TRUE);

	mainMenuState = new StateMainMenu();
	mainMenuState->init(*this);

	gameOverState= new StateGameOver();
	gameOverState->init(*this);

	gameEndState = new StateGameEnd();
	gameEndState->init(*this);

	shopLevel = new StateShop();
	shopLevel->init(*this);

	levelOneState = new StateLevelOne();
	levelOneState->init(*this);

	levelTwoState = new StateLevelTwo();
	levelTwoState->init(*this);

	levelThreeState = new StateLevelThree();
	levelThreeState->init(*this);

	//Set the first game state to the main menu
	currentState = mainMenuState;
	currentState->enter();

	glClearColor(0, 0, 0, 0);
}

void Game::run() {
	bool running = true;
	SDL_Event sdlEvent;

	while (running)	// the event loop
	{
		while (SDL_PollEvent(&sdlEvent)) {
			if (sdlEvent.type == SDL_QUIT)
				running = false;
			else
				currentState->handleSDLEvent(sdlEvent, *this);

		}
		currentState->update(*this);
		currentState->draw(window);
	}
}
/*
Exit the current game state and enter the new game state
*/
void Game::setState(GameState* newState) {
	currentState->exit();
	currentState = newState;
	currentState->enter();
	glPushMatrix();
}

/*
Return specific game states in the game.
Can be called within a gamestate to set the current game state of the game
*/
GameState* Game::getMainMenuState() {
	return mainMenuState;
}
GameState* Game::getGameOver() {
	return gameOverState;
}
GameState* Game::getGameEnd() {
	return gameEndState;
}
GameState* Game::getLevelShop() {
	return shopLevel;
}
GameState* Game::getLevelOne() {
	return levelOneState;
}
GameState* Game::getLevelTwo() {
	return levelTwoState;
}
GameState* Game::getLevelThree() {
	return levelThreeState;
}
