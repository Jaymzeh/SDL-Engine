#include "stateLevelThree.h"
#include "game.h"
#define GL_CLAMP_TO_EDGE 0x812F
//#include "player.h"

StateLevelThree::StateLevelThree() {

}//constructor
StateLevelThree::~StateLevelThree() {
	delete player;
	delete map;
	delete keystate;
	for (int i = 0; i < character.size(); i++) {
		delete character[i];
		character[i] = nullptr;
	}
}//destructor

void StateLevelThree::draw(SDL_Window* window) {

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
	player->showHealth(left, top - 32);

	for (int i = 0; i < character.size(); i++) {
		character[i]->render();
		if (character[i]->getHealth() <= 0)
			character.erase(character.begin() + i);

	}

	door.render();

	if (!door.unlocked)
		key.render();

	SDL_GL_SwapWindow(window);
}//draw
void StateLevelThree::init(Game& context) {
	//label = context.textToTexture("I am text", label);
}//init
void StateLevelThree::update(Game& context) {
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
	for (int i = 0; i < character.size(); i++) {
		character[i]->updateAttackCooldown();
		if (i != character.size() - 1) {
			if (character[i]->getBox().intersects(character[i + 1]->getBox())) {
				character[i]->moveBack();
			}
		}
		if (character[i]->getPosition().distance(player->getPosition()) < 128) {
			character[i]->setTarget(player->getPosition());
			if (player->getBox().intersects(character[i]->getBox()))
				character[i]->moveBack();

			if (character[i]->getPosition().distance(player->getPosition()) < 64 && character[i]->getAttackCooldown()>120) {
				player->health--;
				character[i]->resetAttackCooldown();
			}

			character[i]->update();
			for (int j = 0; j < mapBoxes.size(); j++) {
				if (character[i]->getBox().intersects(mapBoxes[j])) {
					character[i]->moveBack();
				}
			}
		}
		if (player->getBox().intersects(key.getBox()))
			door.unlocked = true;
		if (door.unlocked && player->getBox().intersects(door.getBox()))
			context.setState(context.getLevelThree());
	}
}//update
void StateLevelThree::enter() {
	cout << "Loading Level Three State \n";
	map = new Map("\mapThree.txt", 0, 0);
	map->setBitmap("BlockSpriteBitmap4.bmp");
	map->setTileSize(32);
	map->loadMapTiles();
	mapBoxes = map->getBoxes();

	player = new Player(23 * 32, 12 * -32, 32, 16);

	player->setSprite(0, new AniSprite(player->getPosition().x,
		player->getPosition().y, "rearViewWalk.bmp", 3, 1));
	player->setSprite(1, new AniSprite(player->getPosition().x,
		player->getPosition().y, "sideViewWalk.bmp", 4, 1));
	player->setSprite(2, new AniSprite(player->getPosition().x,
		player->getPosition().y, "frontViewWalk.bmp", 3, 1));

	player->setSprite(3, new AniSprite(player->getPosition().x,
		player->getPosition().y, "frontStickStab.bmp", 2, 1));
	player->setSprite(4, new AniSprite(player->getPosition().x,
		player->getPosition().y, "sideSwordStab.bmp", 2, 1));

	key.createKey(53 * 32, 24 * -32, new Bitmap("Key.bmp", true));

	door.createDoor(37 * 32, -64, new Bitmap("Door.bmp", true));

	character.push_back(new Slime(new Character(41 * 32, 12 * -32, 32)));
	character[character.size() - 1]->setHealth(20);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeRedRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeRedSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeRedSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	//black Slime
	character.push_back(new Slime(new Character(10 * 32, 15 * -32, 32)));
	character[character.size() - 1]->setHealth(40);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeBlackRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeBlackSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeBlackSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	character.push_back(new Slime(new Character(19 * 32, 23 * -32, 32)));
	character[character.size() - 1]->setHealth(20);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeRedRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeRedSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeRedSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	//black Slime
	character.push_back(new Slime(new Character(10 * 32, 23 * -32, 32)));
	character[character.size() - 1]->setHealth(40);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeBlackRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeBlackSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeBlackSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	character.push_back(new Slime(new Character(48 * 32, 27 * -32, 32)));
	character[character.size() - 1]->setHealth(40);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeBlackRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeBlackSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeBlackSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	character.push_back(new Slime(new Character(50 * 32, 25 * -32, 32)));
	character[character.size() - 1]->setHealth(40);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeBlackRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeBlackSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeBlackSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	character.push_back(new Slime(new Character(52 * 32, 26 * -32, 32)));
	character[character.size() - 1]->setHealth(40);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeBlackRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeBlackSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeBlackSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	character.push_back(new Slime(new Character(15 * 32, 23 * -32, 32)));
	character[character.size() - 1]->setHealth(20);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeRedRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeRedSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeRedSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	character.push_back(new Slime(new Character(23 * 32, 23 * -32, 32)));
	character[character.size() - 1]->setHealth(20);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeRedRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeRedSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeRedSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	character.push_back(new Slime(new Character(34 * 32, 31 * -32, 32)));
	character[character.size() - 1]->setHealth(20);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeRedRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeRedSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeRedSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	character.push_back(new Slime(new Character(29 * 32, 17 * -32, 32)));
	character[character.size() - 1]->setHealth(20);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeRedRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeRedSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeRedSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	character.push_back(new Slime(new Character(26 * 32, 18 * -32, 32)));
	character[character.size() - 1]->setHealth(20);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeRedRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeRedSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeRedSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	character.push_back(new Slime(new Character(23 * 32, 17 * -32, 32)));
	character[character.size() - 1]->setHealth(20);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeRedRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeRedSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeRedSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	character.push_back(new Slime(new Character(20 * 32, 18 * -32, 32)));
	character[character.size() - 1]->setHealth(20);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeRedRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeRedSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeRedSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	//black Slime
	character.push_back(new Slime(new Character(47 * 32, 8 * -32, 32)));
	character[character.size() - 1]->setHealth(40);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeBlackRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeBlackSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeBlackSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	character.push_back(new Slime(new Character(44 * 32, 12 * -32, 32)));
	character[character.size() - 1]->setHealth(20);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeRedRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeRedSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeRedSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	character.push_back(new Slime(new Character(46 * 32, 12 * -32, 32)));
	character[character.size() - 1]->setHealth(20);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeRedRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeRedSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeRedSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	character.push_back(new Slime(new Character(26 * 32, 3 * -32, 32)));
	character[character.size() - 1]->setHealth(20);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeRedRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeRedSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeRedSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	character.push_back(new Slime(new Character(29 * 32, 6 * -32, 32)));
	character[character.size() - 1]->setHealth(20);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeRedRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeRedSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeRedSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	character.push_back(new Slime(new Character(27 * 32, 4 * -32, 32)));
	character[character.size() - 1]->setHealth(20);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeRedRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeRedSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeRedSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	character.push_back(new Rat(new Character(28 * 32, 5 * -32, 32)));
	character[character.size() - 1]->setHealth(20);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatSideWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	cout << "Level Three Loaded \n";
}//enter
void StateLevelThree::exit() {
	cout << "Exiting Level Three State \n" << endl;

	for (int i = 0; i < character.size(); i++) {
		delete character[i];
	}
	character.clear();
}//exit

void StateLevelThree::handleSDLEvent(SDL_Event const& sdlEvent, Game& context) {
	if (sdlEvent.type == SDL_KEYDOWN) {
		switch (sdlEvent.key.keysym.sym) {

		case SDLK_e:
			player->attack(character);
			break;

		case SDLK_RETURN: case SDLK_RETURN2:
			context.setState(context.getLevelOne());
			break;

		default:
			break;
		}
	}



}//handleSDLEvent