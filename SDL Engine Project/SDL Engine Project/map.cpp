#include "map.h"

/*
Loads in the spritesheet for the map 

@param filePath - file path to the bitmap file (folder\bitmap.bmp)
*/
void Map::setBitmap(char* filePath){
	bitmap = new Bitmap(filePath, false);
	cout << bitmap << endl;
}

void Map::loadMapFile(char* filePath){
	string line;
	ifstream file(filePath);
	if (file.is_open()){

		getline(file, line);
		columns = line.length();

		do{
			for (int x = 0; x < columns; x++){
				grid.push_back(line.at(x));
			}
		} while (getline(file, line));


		rows = grid.size() / columns;

		for (int x = 0; x < grid.size(); x++)
			cout << grid[x];

		file.close();
	}
	else {
		cout << "File '" << filePath << "' could not be loaded" << endl;
	}
	
}

void Map::loadMapTiles(){
	char ID;
	float xPos = position.x;
	float yPos = position.y - tileSize;
	cout << "Map coords [" << position.x << ", " << position.y << "]" << endl;
	
	xPos = position.x;
	int rowLength = 1;
	int tileIndex = 0;
	for (int i = 0; i < grid.size(); i++){
		ID = grid[i];

		if (rowLength>columns){
			yPos -= tileSize;
			xPos = position.x;
			rowLength = 1;
		}

		switch (ID){

		default:
			rowLength++;
			xPos += tileSize;
			break;

		case 'a':
			cout << "Wall tile added - (" << xPos << ", " << yPos << ")" << endl;
			tile.push_back(new WallTile(new Tile(xPos, yPos, tileSize, tileSize, 0)));
			//tile.push_back(new NewWall(xPos, yPos, tileSize, tileSize, 0));
			rowLength++;
			xPos += tileSize;
			break;
		case 'b':
			cout << "Corridor tile added - (" << xPos << ", " << yPos << ")" << endl;
			tile.push_back(new GroundTile(new Tile(xPos, yPos, tileSize, tileSize, 5)));
			rowLength++;
			xPos += tileSize;
			break;

		case 'c':
			cout << "Corridor tile added - (" << xPos << ", " << yPos << ")" << endl;
			tile.push_back(new DoorTile(new Tile(xPos, yPos, tileSize, tileSize, 5)));
			rowLength++;
			xPos += tileSize;
			break;

		case 'd':
			cout << "IronDoor tile added - (" << xPos << ", " << yPos << ")" << endl;
			xPos += tileSize;
			rowLength++;
			break;
		}
	}
}

void Map::render(){
	for (int i = 0; i < tile.size(); i++){
		tile[i]->render(bitmap);
		if (tile[i]->getID() == 0)
			tile[i]->getBox().render();
	}
}