#include "stateLevelOne.h"
#include "game.h"

StateLevelOne::StateLevelOne() {
	
}//constructor
StateLevelOne::~StateLevelOne() {
	delete player;
	delete map;
	delete keystate;
}//destructor

void StateLevelOne::draw(SDL_Window* window) {

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	int left = (player->getPosition().x + 16) - (VIEWWIDTH / 2);
	int right = left + VIEWWIDTH;
	int top = (player->getPosition().y + 16) + (VIEWHEIGHT / 2);
	int bottom = top - VIEWHEIGHT;
	gluOrtho2D(left, right, bottom, top);


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

	player->render();

	for (int i = 0; i < character.size(); i++) {
		character[i]->render();
	}

	SDL_GL_SwapWindow(window);
}//draw
void StateLevelOne::init(Game& context) {
	
}//init
void StateLevelOne::update(Game& context) {
	int playerSpeed = 1;

	if (keystate[SDL_SCANCODE_A])
		player->move(-playerSpeed, 0);
	else
		if (keystate[SDL_SCANCODE_D])
			player->move(playerSpeed, 0);
		
	
	

	for (int i = 0; i < mapBoxes.size(); i++) {
		if (player->getBox().intersects(mapBoxes[i])) {
			player->moveBack();
		}
	}

	if (keystate[SDL_SCANCODE_W])
		player->move(0, playerSpeed);
	else
		if (keystate[SDL_SCANCODE_S])
			player->move(0, -playerSpeed);

	for (int i = 0; i < mapBoxes.size(); i++) {
		if (player->getBox().intersects(mapBoxes[i])) {
			player->moveBack();
		}
	}

}//update
void StateLevelOne::enter() {
	map = new Map("\map.txt", 0, 768);
	map->setBitmap("BlockSpriteBitmap2.bmp");
	map->setTileSize(32);
	map->loadMapTiles();
	mapBoxes = map->getBoxes();

	player = new Character(64, 702, 32);

	player->setSprite(0, new AniSprite(player->getPosition().x,
		player->getPosition().y, "BlackMage_up.bmp", 3, 1));
	player->setSprite(1, new AniSprite(player->getPosition().x,
		player->getPosition().y, "BlackMage_right.bmp", 3, 1));
	player->setSprite(2, new AniSprite(player->getPosition().x,
		player->getPosition().y, "BlackMage_down.bmp", 3, 1));

}//enter
void StateLevelOne::exit() {
	cout << "Exiting Level One State" << endl;
	
}//exit

void StateLevelOne::handleSDLEvent(SDL_Event const& sdlEvent, Game& context) {
	
	

	if (sdlEvent.type == SDL_KEYDOWN) {
		switch (sdlEvent.key.keysym.sym) {

		case SDLK_RETURN: case SDLK_RETURN2:
			context.setState(context.getLevelTwo());
			break;

		default:
			break;
		}

		
	}
	
	

}//handleSDLEvent