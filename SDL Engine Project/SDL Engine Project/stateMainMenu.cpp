#include "stateMainMenu.h"


StateMainMenu::StateMainMenu() {

}//constructor
StateMainMenu::~StateMainMenu() {

}//destructor

void StateMainMenu::draw(SDL_Window* window) {
	
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	//glViewport(0, 0, 800, 800);
	map->render();

	glColor3f(1, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(0, 0);
	glVertex2f(1024, 0);
	glVertex2f(1024, 768);
	glVertex2f(0, 768);
	glEnd();



	glPointSize(10);
	glBegin(GL_POINTS);
	glVertex2f(0, 0);
	glEnd();

	glBegin(GL_POINTS);
	glVertex2f(1024, 768);
	glEnd();

	SDL_GL_SwapWindow(window);

}//draw
void StateMainMenu::init(Game& context) {

}//init
void StateMainMenu::enter() {
	map = new Map("map.txt", 0, 768);
	map->setBitmap("BlockSpriteBitmap2.bmp");
	map->setTileSize(32);
	map->loadMapTiles();
}//enter
void StateMainMenu::exit() {

}//exit

void StateMainMenu::handleSDLEvent(SDL_Event const& sdlEvent, Game& context) {

	if (sdlEvent.type == SDL_KEYDOWN)
	{
		switch (sdlEvent.key.keysym.sym)
		{

		case SDLK_a:
			glTranslated(10, 0, 0);
			break;

		case SDLK_d:
			glTranslated(-10, 0, 0);
			break;

		case SDLK_w:
			glTranslated(0, -10, 0);
			break;

		case SDLK_s:
			glTranslated(0, 10, 0);
			break;


		default:
			break;
		}
	}

}//handleSDLEvent