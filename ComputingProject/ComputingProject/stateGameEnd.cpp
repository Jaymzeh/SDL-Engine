#include "stateGameEnd.h"
#include "game.h"

StateGameEnd::StateGameEnd() {

}//constructor
StateGameEnd::~StateGameEnd() {

}//destructor

void StateGameEnd::draw(SDL_Window* window) {

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
void StateGameEnd::init(Game& context) {

}//init
void StateGameEnd::update(Game& context) {


}//update
void StateGameEnd::enter() {
	cout << "Game End State \n";

	background = new Bitmap("endScreenBackground.bmp", false);

	cout << "Game End Loaded \n";
}//enter
void StateGameEnd::exit() {
	cout << "Exiting Game Over State \n" << endl;

}//exit

void StateGameEnd::handleSDLEvent(SDL_Event const& sdlEvent, Game& context) {
	if (sdlEvent.type == SDL_KEYDOWN) {
		switch (sdlEvent.key.keysym.sym) {

		case SDLK_RETURN: case SDLK_RETURN2: case SDLK_e:
			context.setState(context.getMainMenuState());
			break;

		default:
			break;
		}
	}
}//handleSDLEvent