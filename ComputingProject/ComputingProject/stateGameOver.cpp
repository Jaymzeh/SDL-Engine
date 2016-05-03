#include "stateGameOver.h"
#include "game.h"

StateGameOver::StateGameOver() {

}//constructor
StateGameOver::~StateGameOver() {

}//destructor

void StateGameOver::draw(SDL_Window* window) {

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
void StateGameOver::init(Game& context) {

}//init
void StateGameOver::update(Game& context) {


}//update
void StateGameOver::enter() {
	cout << "Game Over State \n";

	background = new Bitmap("mainMenuBackground.bmp", true);

	cout << "Game Over  Loaded \n";
}//enter
void StateGameOver::exit() {
	cout << "Exiting Game Over State \n" << endl;

}//exit

void StateGameOver::handleSDLEvent(SDL_Event const& sdlEvent, Game& context) {
	if (sdlEvent.type == SDL_KEYDOWN) {
		switch (sdlEvent.key.keysym.sym) {

		case SDLK_RETURN: case SDLK_RETURN2: case SDLK_n:
			context.setState(context.getMainMenuState());
			break;

		default:
			break;
		}
	}
}//handleSDLEvent