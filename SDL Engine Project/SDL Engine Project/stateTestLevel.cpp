#include "stateTestLevel.h"

#include "game.h"

StateTestLevel::StateTestLevel() {

}//constructor
StateTestLevel::~StateTestLevel() {

}//destructor

void StateTestLevel::draw(SDL_Window* window) {

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	//glViewport(0, 0, 800, 800);
	map->render();

	//glColor3f(1, 0, 0);
	//glBegin(GL_LINE_LOOP);
	//glVertex2f(0, 0);
	//glVertex2f(1024, 0);
	//glVertex2f(1024, 768);
	//glVertex2f(0, 768);
	//glEnd();
	//glPointSize(10);
	//glBegin(GL_POINTS);
	//glVertex2f(0, 0);
	//glEnd();
	//glBegin(GL_POINTS);
	//glVertex2f(1024, 768);
	//glEnd();

	player->draw();


	SDL_GL_SwapWindow(window);
}//draw
void StateTestLevel::init(Game& context) {
	map = new Map("map.txt", 0, 768);


}//init
void StateTestLevel::update(Game& context) {

}//update
void StateTestLevel::enter() {

	map->setBitmap("BlockSpriteBitmap2.bmp");
	map->setTileSize(32);
	map->loadMapTiles();
	mapBoxes = map->getBoxes();

	player = new Player(64, 702);

	player->setSprite(0, new AniSprite(player->getPosition().x,
		player->getPosition().y, "BlackMage_up.bmp", 3, 1));
	player->setSprite(1, new AniSprite(player->getPosition().x,
		player->getPosition().y, "BlackMage_right.bmp", 3, 1));
	player->setSprite(2, new AniSprite(player->getPosition().x,
		player->getPosition().y, "BlackMage_down.bmp", 3, 1));

}//enter
void StateTestLevel::exit() {

}//exit

void StateTestLevel::handleSDLEvent(SDL_Event const& sdlEvent, Game& context) {

	if (sdlEvent.type == SDL_KEYDOWN) {
		switch (sdlEvent.key.keysym.sym) {

		case SDLK_a:
			player->move(-2, 0);
			glTranslatef(2, 0, 0);
			break;

		case SDLK_d:
			player->move(2, 0);
			glTranslatef(-2, 0, 0);
			break;

		case SDLK_w:
			player->move(0, 2);
			glTranslatef(0, -2, 0);
			break;

		case SDLK_s:
			player->move(0, -2);
			glTranslatef(0, 2, 0);
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