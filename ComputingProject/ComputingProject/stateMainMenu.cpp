#include "stateMainMenu.h"
#include "game.h"

StateMainMenu::StateMainMenu() {

}//constructor
StateMainMenu::~StateMainMenu() {

}//destructor

void StateMainMenu::draw(SDL_Window* window) {

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	int left = 0;
	int right = left + VIEWWIDTH;
	int top = VIEWHEIGHT;
	int bottom = 0;
	gluOrtho2D(left, right, bottom, top);

	background->draw(0, 0, VIEWWIDTH, VIEWHEIGHT);

	SDL_GL_SwapWindow(window);
}//draw
void StateMainMenu::init(Game& context) {

}//init
void StateMainMenu::update(Game& context) {

	
}//update
void StateMainMenu::enter() {
	cout << "Loading Main Menu State \n";

	background = new Bitmap("mainMenuBackground.bmp", false);

	cout << "Main Menu Loaded \n";
}//enter
void StateMainMenu::exit() {
	cout << "Exiting Main Menu State \n" << endl;

}//exit

void StateMainMenu::handleSDLEvent(SDL_Event const& sdlEvent, Game& context) {
	if (sdlEvent.type == SDL_KEYDOWN) {
		switch (sdlEvent.key.keysym.sym) {

		case SDLK_RETURN: case SDLK_RETURN2: case SDLK_e:
			context.setState(context.getLevelOne());
			break;

		default:
			break;
		}


	}
}//handleSDLEvent