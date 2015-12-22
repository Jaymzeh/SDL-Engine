#include "game.h"
#include "stateMainMenu.h"
#include "stateLevelOne.h"
#include "stateLevelTwo.h"

void exitFatalError(char *message)
{
	std::cout << message << " " << SDL_GetError();
	SDL_Quit();
	exit(1);
}

int Game::instances = 0;

Game::Game(){
	instances++;
	if (instances > 1)
		exitFatalError("Attempt to create multiple game instances");
	setupRC();
}
Game::~Game() {

}

void Game::setupRC(){
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) // Initialize video
		exitFatalError("Unable to initialize SDL");

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	window = SDL_CreateWindow("Group 3 Engine Prototype",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WINDOWWIDTH, WINDOWHEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (!window)
		exitFatalError("Unable to create window");
	
	glContext = SDL_GL_CreateContext(window);

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//int left = 0;
	//int right = left + WINDOWWIDTH;
	//int top = WINDOWHEIGHT;
	//int bottom = top -WINDOWHEIGHT;
	////glPushMatrix();
	////gluOrtho2D(left, right, bottom, top);
	//gluOrtho2D(left, right, bottom, top);

	SDL_GL_SetSwapInterval(1);

	//Audio

	BASS_Init(-1, 44100, 0, 0, NULL);
	musicSample = BASS_SampleLoad(false, "Build_That_Wall.mp3",0,0,1, BASS_SAMPLE_MONO);
	sample = BASS_SampleLoad(false, "edubble.mp3", 0, 0, 1, BASS_SAMPLE_MONO);
	musicChannel = BASS_SampleGetChannel(musicSample, FALSE);
	sfxChannel = BASS_SampleGetChannel(sample, FALSE);
}

void Game::init(){
	//BASS_ChannelPlay(musicChannel, FALSE);
	//BASS_ChannelPlay(sfxChannel, FALSE);

	levelOneState = new StateLevelOne();
	levelOneState->init(*this);

	levelTwoState = new StateLevelTwo();
	levelTwoState->init(*this);

	currentState = levelOneState;
	currentState->enter();

	glClearColor(0, 0, 0, 0);
}

void Game::run(){
	bool running = true;
	SDL_Event sdlEvent;

	while (running)	// the event loop
	{
		while (SDL_PollEvent(&sdlEvent))
		{
			if (sdlEvent.type == SDL_QUIT)
				running = false;
			else
				currentState->handleSDLEvent(sdlEvent, *this);

		}
		//currentState->update();
		currentState->draw(window);
	}
}

void Game::setState(GameState* newState){
	currentState->exit();
	currentState = newState;
	currentState->enter();
	glPushMatrix();
}

GameState* Game::getMainMenuState() {
	return mainMenuState;
}

GameState* Game::getLevelOne() {
	return levelOneState;
}
GameState* Game::getLevelTwo() {
	return levelOneState;
}
