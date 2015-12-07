//#include <iostream>
#include "game.h"

#if _DEBUG
#pragma comment(linker, "/subsystem:\"console\" /entry:\"WinMainCRTStartup\"")
#endif

int main(int argc, char* argv[]){
	Game* newGame = new Game();

	newGame->init();
	newGame->run();

	delete newGame;
	return 0;
}