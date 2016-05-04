#include "stateShop.h"
#include "game.h"
#define GL_CLAMP_TO_EDGE 0x812F
//#include "player.h"

StateShop::StateShop() {

}//constructor
StateShop::~StateShop() {
	delete player;
	delete map;
	delete keystate;

}//destructor

void StateShop::draw(SDL_Window* window) {

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

	shop.render();
	door.render();

	player->render();
	player->showHealth(left, top - 16);
	player->showMoney(left, top - 32);

	SDL_GL_SwapWindow(window);
}//draw
void StateShop::init(Game& context) {

}//init
void StateShop::update(Game& context) {
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

	if (door.unlocked && player->getBox().intersects(door.getBox())) {
		switch (player->prevLevel) {
		case 1:
			player->savePlayerData("playerData.txt");
			context.setState(context.getLevelTwo());
			break;

		case 2:
			player->savePlayerData("playerData.txt");
			context.setState(context.getLevelThree());
			break;
		}
		
	}
		
		

	//Checking shop collisions
	if (player->getBox().intersects(shop.getMainbBox()))
		shop.inShopSelection = 1;
	if (player->getBox().intersects(shop.getbBoxOption1()))
		shop.inShopSelection = 2;
	if (player->getBox().intersects(shop.getbBoxOption2()))
		shop.inShopSelection = 3;
	if (player->getBox().intersects(shop.getbBoxOption3()))
		shop.inShopSelection = 4;
	if (!player->getBox().intersects(shop.getMainbBox()) && !player->getBox().intersects(shop.getbBoxOption1()) && !player->getBox().intersects(shop.getbBoxOption2())
		&& !player->getBox().intersects(shop.getbBoxOption3()))
		shop.inShopSelection = 5;

	//Checks to see if payer has entered shop, Then respective options
	if (shop.inShopSelection == 1 && !shop.inShop) {
		shop.inShop = true;
		cout << "Welome to $shopName" << endl;
	}
	else if (shop.inShopSelection == 2 && shop.selectionCooldown < 1) {
		//N: Doesn't need a cooldown
		if (keystate[SDL_SCANCODE_E]) {

			if (player->getMoney() >= 5) {
				cout << "+1 Strength" << endl << "-5 coins" << endl;
				player->addMoney(-5);
				player->strength++;
				BASS_ChannelPlay(context.getSfxChannel(), true);
				cout << "Coins: " << player->getMoney() << endl;
				cout << "-----------------------------" << endl;
			}
			else
				cout << "No enough coins" << endl;

			shop.selectionCooldown = 100;
		}
	}
	else if (shop.inShopSelection == 3 && shop.selectionCooldown < 1) {
		//N: Doesn't need a cooldown
		if (keystate[SDL_SCANCODE_E]) {
			if (player->getMoney() >= 15) {
				cout << "+1 Extra Health" << endl << "-15 coins" << endl;
				player->addMoney(-15);
				player->maxHealth++;
				BASS_ChannelPlay(context.getSfxChannel(), true);
				cout << "Coins: " << player->getMoney() << endl;
				cout << "-----------------------------" << endl;
			}
			else
				cout << "No enough coins" << endl;

			shop.selectionCooldown = 100;
		}
	}
	else if (shop.inShopSelection == 4 && shop.selectionCooldown < 1) {
		//N: Doesn't need a cooldown
		if (keystate[SDL_SCANCODE_E]) {

			if (player->getMoney() >= 10) {
				player->health = player->maxHealth;
				player->addMoney(-10);
				BASS_ChannelPlay(context.getSfxChannel(), true);
				cout << "+1 Potion" << endl << "-10 coins" << endl;
				cout << "Coins: " << player->getMoney() << endl;
				cout << "-----------------------------" << endl;
			}
			else
				cout << "No enough coins" << endl;
			shop.selectionCooldown = 100;
		}
	}
	else {
	}

	//Check to see if player exits shop
	if (shop.inShopSelection != 1) {
		shop.inShop = false;
	}

	//Cooldown to stop instant re-selection
	shop.selectionCooldown--;

}//update
void StateShop::enter() {
	cout << "Entering Shop State" << endl;

	map = new Map("\mapShop.txt", 0, 0);
	map->setBitmap("BlockSpriteBitmap2.bmp");
	map->setTileSize(32);
	map->loadMapTiles();
	mapBoxes = map->getBoxes();

	shop.spawnShop(64, -5*32, new Bitmap("shop.bmp", true));

	player = new Player(64, -6*32, 32, 16);
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
	player->setCoinSprite(new Bitmap("coin.bmp", true));

	door.createDoor(8*32, -6*32, new Bitmap("Door.bmp", false));
	door.unlocked = true;


}//enter
void StateShop::exit() {
	cout << "Exiting Shop State" << endl;

}//exit

void StateShop::handleSDLEvent(SDL_Event const& sdlEvent, Game& context) {
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