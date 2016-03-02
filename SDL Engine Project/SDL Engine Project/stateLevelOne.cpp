#include "stateLevelOne.h"
#include "game.h"
//#include "player.h"

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

	player->render();

	for (int i = 0; i < character.size(); i++) {
		character[i]->render();
		if (character[i]->getHealth() <= 0)
			character.erase(character.begin() + i);
	}

	door.render();

	if(!door.unlocked)
		key.render();

	SDL_GL_SwapWindow(window);
}//draw
void StateLevelOne::init(Game& context) {
	
}//init
void StateLevelOne::update(Game& context) {
	player->handleInputX(keystate);

	for (int i = 0; i < mapBoxes.size(); i++) {
		if (player->getBox().intersects(mapBoxes[i])) {
			player->moveBack();
		}
	}
	player->handleInputY(keystate);

	for (int i = 0; i < mapBoxes.size(); i++) {
		if (player->getBox().intersects(mapBoxes[i])) {
			player->moveBack();
		}
	}

	if (player->getBox().intersects(key.getBox()))
		door.unlocked = true;

	if (door.unlocked && player->getBox().intersects(door.getBox()))
		context.setState(context.getLevelTwo());

}//update
void StateLevelOne::enter() {

	map = new Map("\mapOne.txt", 0, 0);
	map->setBitmap("BlockSpriteBitmap2.bmp");
	map->setTileSize(32);
	map->loadMapTiles();
	mapBoxes = map->getBoxes();

	player = new Player(32,-96,32);

	player->setSprite(0, new AniSprite(player->getPosition().x,
		player->getPosition().y, "rearViewWalk.bmp", 3, 1));
	player->setSprite(1, new AniSprite(player->getPosition().x,
		player->getPosition().y, "sideViewWalk.bmp", 4, 1));
	player->setSprite(2, new AniSprite(player->getPosition().x,
		player->getPosition().y, "frontViewWalk.bmp", 3, 1));

	player->setSprite(3, new AniSprite(player->getPosition().x,
		player->getPosition().y, "frontStickStab.bmp", 2, 1));
	player->setSprite(4, new AniSprite(player->getPosition().x,
		player->getPosition().y, "sideStickStab.bmp", 2, 1));

	key.createKey(32, -512, new Bitmap("key.bmp", true));
	door.createDoor(832, -224, new Bitmap("door.bmp", false));	

	
	character.push_back(new Orc(new Character(32, -128, 64)));
	character[0]->setHealth(1);
	character[0]->setSprite(0, new AniSprite(character[0]->getPosition().x,
		character[0]->getPosition().y, "playerUp.bmp", 1, 1));
	character[0]->setSprite(1, new AniSprite(character[0]->getPosition().x,
		character[0]->getPosition().y, "playerSide.bmp", 3, 1));
	character[0]->setSprite(2, new AniSprite(character[0]->getPosition().x,
		character[0]->getPosition().y, "playerDown.bmp", 3, 1));


	character.push_back(new Orc(new Character(192, -192, 64)));
	character[1]->setHealth(1);
	character[1]->setSprite(0, new AniSprite(character[1]->getPosition().x,
		character[1]->getPosition().y, "playerUp.bmp", 1, 1));
	character[1]->setSprite(1, new AniSprite(character[1]->getPosition().x,
		character[1]->getPosition().y, "playerSide.bmp", 3, 1));
	character[1]->setSprite(2, new AniSprite(character[1]->getPosition().x,
		character[1]->getPosition().y, "playerDown.bmp", 3, 1));
		
}//enter
void StateLevelOne::exit() {
	cout << "Exiting Level One State" << endl;

	for (int i = 0; i < character.size(); i++) {
		delete character[i];
	}
	character.clear();
}//exit

void StateLevelOne::handleSDLEvent(SDL_Event const& sdlEvent, Game& context) {
	if (sdlEvent.type == SDL_KEYDOWN) {
		switch (sdlEvent.key.keysym.sym) {

		case SDLK_e:
			player->attack(character);
			break;

		case SDLK_RETURN: case SDLK_RETURN2:
			context.setState(context.getLevelTwo());
			break;

		default:
			break;
		}

		
	}
	
	

}//handleSDLEvent