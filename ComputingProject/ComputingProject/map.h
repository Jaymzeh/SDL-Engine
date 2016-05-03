#ifndef MAP_H
#define MAP_H

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
	int tileSize = 32;
	vector<char> grid;
	vector<BaseTile*> tile;
	Vector2 position;
	Bitmap *bitmap;


public:
	Map() {};
	Map(char* filePath, int dx, int dy) {
		position.x = dx; position.y = dy; loadMapFile(filePath);
	};
	void setBitmap(char* filePath);

	void setTileSize(int size) { tileSize = size; }
	int getTileSize() { return tileSize; }

	vector<BoundingBox> getBoxes() {
		vector<BoundingBox> boxes;
		for (int i = 0; i < tile.size(); i++) {
			if (tile[i]->getID() == 0 || tile[i]->getID() == 2)
				boxes.push_back(tile[i]->getBox());
		}
		return boxes;
	}

	void loadMapFile(char* filePath);
	void loadMapTiles();
	void render();
	void renderDebug();

	~Map() {
		cout << "Deleting map" << endl;
		delete bitmap;
	}
};

#endif
