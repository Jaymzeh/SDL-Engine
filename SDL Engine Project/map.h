#ifndef MAP
#define MAP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "bitmap.h"
#include "tile.h"
using namespace std;

#define ROWS = 5
#define COLUMNS = 5;

class Map {
protected:
	int rows = 5;
	int columns = 5;
	float tileSize = 32;
	vector<char> grid;
	vector<BaseTile*> tile;
	Vector2 position;
	Bitmap *bitmap;

	
public:
	Map(){};
	Map(char* filePath, float dx, float dy) { 
		position.x = dx; position.y = dy; loadMapFile(filePath); };
	void setBitmap(char* filePath);

	void setTileSize(float size){ tileSize = size; }
	float getTileSize(){ return tileSize; }

	void loadMapFile(char* filePath);
	void loadMapTiles();
	void render();

	~Map() {
		cout << "Deleting map" << endl;
		delete bitmap;
	}
};

#endif
