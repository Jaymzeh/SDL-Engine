#include "stateLevelTwo.h"
#include "game.h"

StateLevelTwo::StateLevelTwo() {

}//constructor
StateLevelTwo::~StateLevelTwo() {
	delete player;
	delete map;
	delete keystate;
	door.deleteDoor();
	key.deleteKey();
	for (int i = 0; i < character.size(); i++) {
		delete character[i];
		character[i] = nullptr;
	}
}//destructor

void StateLevelTwo::draw(SDL_Window* window) {

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

	for (int i = 0; i < character.size(); i++) 
		character[i]->render();

	door.render();

	player->render();
	player->showHealth(left, top - 16);
	player->showMoney(left, top - 32);

	if (!door.unlocked)
		key.render();

	SDL_GL_SwapWindow(window);
}//draw
void StateLevelTwo::init(Game& context) {
	//label = context.textToTexture("I am text", label);
}//init
void StateLevelTwo::update(Game& context) {

	if (player->health <= 0)
		context.setState(context.getGameOver());

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

			if (character[i]->getPosition().distance(player->getPosition()) < 32 && character[i]->getAttackCooldown()>120) {
				player->health--;
				character[i]->resetAttackCooldown();
			}

			character[i]->update();
			for (int j = 0; j < mapBoxes.size(); j++) {
				if (character[i]->getBox().intersects(mapBoxes[j])) {
					character[i]->moveBack();
				}
			}

			if (character[i]->getHealth() <= 0) {
				character.erase(character.begin() + i);
				player->addMoney(2);
			}
		}
		if (player->getBox().intersects(key.getBox()))
			door.unlocked = true;
		if (door.unlocked && player->getBox().intersects(door.getBox())) {
			player->prevLevel = 2;
			player->savePlayerData("playerData.txt");
			context.setState(context.getLevelShop());
		}
	}
}//update
void StateLevelTwo::enter() {
	cout << "Loading Level Two State \n";
	map = new Map("\mapTwo.txt", 0, 0);
	map->setBitmap("BlockSpriteBitmap3.bmp");
	map->setTileSize(32);
	map->loadMapTiles();
	mapBoxes = map->getBoxes();

	player = new Player(1376, -704, 32, 16);
	player->loadPlayerData("playerData.txt");
	

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

	player->setHeartSprite(new Bitmap("heart.bmp", true));
	player->setCoinSprites(new Bitmap("silverCoin.bmp", true), new Bitmap("goldCoin.bmp", true));

	key.createKey(2016, -64, new Bitmap("Key.bmp", true));
	door.createDoor(1312, -352, new Bitmap("Door.bmp", true));

	character.push_back(new Rat(new Character(96, -448, 32)));
	character[character.size() - 1]->setHealth(15);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatSideWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	character.push_back(new Slime(new Character(160, -448, 32)));
	character[character.size() - 1]->setHealth(15);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeOrangeRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeOrangeSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeOrangeSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	character.push_back(new Rat(new Character(224, -448, 32)));
	character[character.size() - 1]->setHealth(15);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatSideWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());


	character.push_back(new Slime(new Character(416, -734, 32)));
	character[character.size() - 1]->setHealth(15);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeOrangeRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeOrangeSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeOrangeSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	character.push_back(new Slime(new Character(704, -734, 32)));
	character[character.size() - 1]->setHealth(15);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeOrangeRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeOrangeSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeOrangeSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	character.push_back(new Rat(new Character(1312, -576, 32)));
	character[character.size() - 1]->setHealth(15);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatSideWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	character.push_back(new Slime(new Character(1376, -576, 32)));
	character[character.size() - 1]->setHealth(15);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeOrangeRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeOrangeSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeOrangeSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());


	character.push_back(new Rat(new Character(1312, -576, 32)));
	character[character.size() - 1]->setHealth(15);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatSideWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	character.push_back(new Rat(new Character(23 * 32, 9 * -32, 32)));
	character[character.size() - 1]->setHealth(15);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatSideWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	character.push_back(new Rat(new Character(59 * 32, 22 * -32, 32)));
	character[character.size() - 1]->setHealth(15);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatSideWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	character.push_back(new Slime(new Character(61 * 32, 22 * -32, 32)));
	character[character.size() - 1]->setHealth(15);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeOrangeRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeOrangeSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeOrangeSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	character.push_back(new Slime(new Character(63 * 32, 22 * -32, 32)));
	character[character.size() - 1]->setHealth(15);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeOrangeRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeOrangeSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeOrangeSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());



	cout << "Level Two Loaded \n";
}//enter
void StateLevelTwo::exit() {
	cout << "Exiting Level Two State" << endl;

	for (int i = 0; i < character.size(); i++) {
		delete character[i];
	}
	character.clear();
}//exit

void StateLevelTwo::handleSDLEvent(SDL_Event const& sdlEvent, Game& context) {
	if (sdlEvent.type == SDL_KEYDOWN) {
		switch (sdlEvent.key.keysym.sym) {

		case SDLK_e:
			player->attack(character);
			BASS_ChannelPlay(context.getSfxChannel(), true);
			break;

		default:
			break;
		}


	}



}//handleSDLEvent