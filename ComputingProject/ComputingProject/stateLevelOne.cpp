#include "stateLevelOne.h"
#include "game.h"

StateLevelOne::StateLevelOne() {

}//constructor
StateLevelOne::~StateLevelOne() {
	delete player;
	delete map;
	delete keystate;
	for (int i = 0; i < character.size(); i++) {
		delete character[i];
		character[i] = nullptr;
	}
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
	player->showHealth(left, top-32);

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
void StateLevelOne::init(Game& context) {

}//init
void StateLevelOne::update(Game& context) {

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
		if (door.unlocked && player->getBox().intersects(door.getBox())) {
			player->savePlayerData("playerData.txt");
			context.setState(context.getLevelTwo());
		}
	}
}//update
void StateLevelOne::enter() {
	cout << "Loading Level One State \n";
	map = new Map("\mapOne.txt", 0, 0);
	map->setBitmap("BlockSpriteBitmap2.bmp");
	map->setTileSize(32);
	map->loadMapTiles();
	mapBoxes = map->getBoxes();

	player = new Player(512, -64, 32, 16);
	//player = new Player(1952, -320, 32, 16);

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

	key.createKey(1952, -320, new Bitmap("Key.bmp", true));

	door.createDoor(1408, -32, new Bitmap("Door.bmp", true));

	character.push_back(new Slime(new Character(704, -96, 32)));
	character[character.size() - 1]->setHealth(5);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeGreenRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeGreenSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeGreenSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	character.push_back(new Slime(new Character(256, -64, 32)));
	character[character.size() - 1]->setHealth(5);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeGreenRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeGreenSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeGreenSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	character.push_back(new Rat(new Character(256, -224, 32)));
	character[character.size() - 1]->setHealth(5);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatSideWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	character.push_back(new Slime(new Character(64, -320, 32)));
	character[character.size() - 1]->setHealth(5);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeGreenRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeGreenSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeGreenSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	character.push_back(new Rat(new Character(128, -448, 32)));
	character[character.size() - 1]->setHealth(5);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatSideWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	character.push_back(new Slime(new Character(512, -256, 32)));
	character[character.size() - 1]->setHealth(5);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeGreenRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeGreenSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeGreenSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	character.push_back(new Rat(new Character(576, -256, 32)));
	character[character.size() - 1]->setHealth(5);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatSideWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	character.push_back(new Slime(new Character(512, -352, 32)));
	character[character.size() - 1]->setHealth(5);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeGreenRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeGreenSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeGreenSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	character.push_back(new Rat(new Character(576, -352, 32)));
	character[character.size() - 1]->setHealth(5);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatSideWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	character.push_back(new Slime(new Character(256, -512, 32)));
	character[character.size() - 1]->setHealth(5);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeGreenRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeGreenSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeGreenSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	character.push_back(new Rat(new Character(320, -512, 32)));
	character[character.size() - 1]->setHealth(5);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatSideWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	character.push_back(new Rat(new Character(1056, -544, 32)));
	character[character.size() - 1]->setHealth(5);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatSideWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	character.push_back(new Rat(new Character(1024, -288, 32)));
	character[character.size() - 1]->setHealth(5);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatSideWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());


	character.push_back(new Rat(new Character(1952, -352, 32)));
	character[character.size() - 1]->setHealth(5);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatSideWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());


	character.push_back(new Slime(new Character(1952, -288, 32)));
	character[character.size() - 1]->setHealth(5);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeGreenRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeGreenSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeGreenSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	character.push_back(new Slime(new Character(1344, -64, 32)));
	character[character.size() - 1]->setHealth(5);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeGreenRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeGreenSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "BabySlimeGreenSideFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());


	character.push_back(new Rat(new Character(1472, -64, 32)));
	character[character.size() - 1]->setHealth(5);
	character[character.size() - 1]->setSprite(0, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatRearWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(1, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatSideWalk.bmp", 2, 1));
	character[character.size() - 1]->setSprite(2, new AniSprite(character[character.size() - 1]->getPosition().x,
		character[character.size() - 1]->getPosition().y, "RatFrontWalk.bmp", 2, 1));
	character[character.size() - 1]->setTarget(player->getPosition());

	cout << "Level One Loaded \n";
}//enter
void StateLevelOne::exit() {
	cout << "Exiting Level One State \n" << endl;

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
			context.setState(context.getLevelOne());
			break;

		default:
			break;
		}


	}
}//handleSDLEvent