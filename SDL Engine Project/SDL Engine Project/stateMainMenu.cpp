#include "stateMainMenu.h"

#include "game.h"

StateMainMenu::StateMainMenu() {
	
}//constructor
StateMainMenu::~StateMainMenu() {

}//destructor

void StateMainMenu::draw(SDL_Window* window) {
	
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	SDL_GL_SwapWindow(window);
}//draw
void StateMainMenu::init(Game& context) {

}//init
void StateMainMenu::update(Game& context) {

}//update
void StateMainMenu::enter() {

}//enter
void StateMainMenu::exit() {

}//exit

void StateMainMenu::handleSDLEvent(SDL_Event const& sdlEvent, Game& context) {

	if (sdlEvent.type == SDL_KEYDOWN){
		switch (sdlEvent.key.keysym.sym){

		default:
			break;
		}
	}

}//handleSDLEvent