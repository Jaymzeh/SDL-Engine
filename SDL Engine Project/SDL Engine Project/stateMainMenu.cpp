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

	player->draw();

	SDL_GL_SwapWindow(window);

}//draw
void StateMainMenu::init(Game& context) {
	map = new Map("map.txt", 0, 768);
}//init
void StateMainMenu::enter() {
	
	map->setBitmap("BlockSpriteBitmap2.bmp");
	map->setTileSize(32);
	map->loadMapTiles();
	mapBoxes = map->getBoxes();

	player = new Player(64, 702);

}//enter
void StateMainMenu::exit() {

}//exit

void StateMainMenu::handleSDLEvent(SDL_Event const& sdlEvent, Game& context) {

	if (sdlEvent.type == SDL_KEYDOWN){
		switch (sdlEvent.key.keysym.sym){

		case SDLK_a:
			//glTranslatef(10, 0, 0);
			player->move(-2, 0);
			break;

		case SDLK_d:
			//glTranslatef(-10, 0, 0);
			player->move(2, 0);
			break;

		case SDLK_w:
			//glTranslatef(0, -10, 0);
			player->move(0, 2);
			break;

		case SDLK_s:
			//glTranslatef(0, 10, 0);
			player->move(0, -2);
			break;
		default:
			break;
		}

		for (int i = 0; i < mapBoxes.size(); i++) {
			if (player->getBox().intersects(mapBoxes[i])) {
					player->setPosition(player->getOldPosition());
			}
		}
	}

}//handleSDLEvent