#include "game.h"
#include "stateMainMenu.h"

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
		800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (!window)
		exitFatalError("Unable to create window");
	
	

	glContext = SDL_GL_CreateContext(window);

	gluOrtho2D(0, 400, 0, 300);

	//SDL_GL_SetSwapInterval(1);
}

void Game::init(){

	mainMenuState = new StateMainMenu();
	mainMenuState->init(*this);


	currentState = mainMenuState;
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
		//currentState->update(); // this is the place to put a call to the game update function
		currentState->draw(window);
	}
}

void Game::setState(GameState* newState){
	currentState->exit();
	currentState = newState;
	currentState->enter();
}