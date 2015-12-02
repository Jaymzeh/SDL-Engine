#ifndef TILE_H
#define TILE_H

#include <iostream>
#include "freeglut\glut.h"
#include "vector2.h"
#include "aniSprite.h"

using std::cout;
using std::endl;

class BaseTile{
public:
	virtual Vector2 getPosition() = 0;
	virtual float getWidth() = 0;
	virtual float getHeight() = 0;
	virtual void render(Bitmap* bitmap) = 0;
	virtual ~BaseTile(){};
};

class Tile :public BaseTile{
private:
	Vector2 position;
public:

	Tile(){
		width = 1;
		height = 1;
	}
	Tile(float dx, float dy){
		position.x = dx;
		position.y = dy;
		width = 1;
		height = 1;
	}
	Tile(float dx, float dy, float dw, float dh){
		position.x = dx;
		position.y = dy;
		width = dw;
		height = dh;
	}

	Tile(float dx, float dy, 
		float dw, float dh, int tileID){
		position.x = dx;
		position.y = dy;
		width = dw;
		height = dh;
		ID = tileID;
	}

	Vector2 getPosition(){ return position; }
	float getWidth(){ return width; }
	float getHeight(){ return height; }
	void render(Bitmap* sprite){

		if (sprite){
			int spriteWidth = sprite->getWidth();
			int spriteHeight = sprite->getHeight();
			
			int ncols = spriteWidth / width;

			int currentCol = ID % ncols;
			int currentRow = ID / ncols;
			
			int cellX = width*currentCol;
			int cellY = height * currentRow;
			sprite->drawAt(position.x, position.y, cellX, cellY, width, height);
		}
		else{
			glBegin(GL_POLYGON);
			glVertex2f(position.x, position.y); //Top left
			glVertex2f(position.x + width, position.y); //Top right
			glVertex2f(position.x + width, position.y + height); //Bottom right
			glVertex2f(position.x, position.y + height); //Bottom left
			glEnd();
		}

	}
	~Tile(){ cout << "Deleting tile" << endl; }
protected:
	float width;
	float height;
	int ID;
};

class TileDecorator :public BaseTile{
private:
	BaseTile *tile;

public:
	TileDecorator(BaseTile *t){ tile = t; }
	Vector2 getPosition(){ return tile->getPosition(); }
	float getWidth(){ return tile->getWidth(); }
	float getHeight(){ return tile->getHeight(); }
	void render(Bitmap *bitmap){ tile->render(bitmap); }
	~TileDecorator(){ delete tile; }

};

class GroundTile :public TileDecorator{
public:
	GroundTile(BaseTile *t) : TileDecorator(t){};
	Vector2 getPosition(){ return TileDecorator::getPosition(); }
	float getWidth(){ return TileDecorator::getWidth(); }
	float getHeight(){ return TileDecorator::getHeight(); }
	void render(Bitmap *bitmap){ TileDecorator::render(bitmap); }
	~GroundTile(){ cout << "Deleting GroundTile" << endl; }
};

class WallTile :public TileDecorator{
public:
	WallTile(BaseTile *t) : TileDecorator(t){};
	Vector2 getPosition(){ return TileDecorator::getPosition(); }
	float getWidth(){ return TileDecorator::getWidth(); }
	float getHeight(){ return TileDecorator::getHeight(); }
	void render(Bitmap *bitmap){ TileDecorator::render(bitmap); }
	~WallTile(){ cout << "Deleting WallTile" << endl; }
};

class DoorTile :public TileDecorator{
public:
	DoorTile(BaseTile *t) : TileDecorator(t){};
	Vector2 getPosition(){ return TileDecorator::getPosition(); }
	float getWidth(){ return TileDecorator::getWidth(); }
	float getHeight(){ return TileDecorator::getHeight(); }
	void render(Bitmap *bitmap){ TileDecorator::render(bitmap); }
	~DoorTile(){ cout << "Deleting DoorTile" << endl; }
};


class NewTile{
private:
	Vector2 position;
public:

	NewTile(){
		width = 1;
		height = 1;
	}
	NewTile(float dx, float dy){
		position.x = dx;
		position.y = dy;
		width = 1;
		height = 1;
	}
	NewTile(float dx, float dy, float dw, float dh){
		position.x = dx;
		position.y = dy;
		width = dw;
		height = dh;
	}

	NewTile(float dx, float dy,
		float dw, float dh, int tileID){
		position.x = dx;
		position.y = dy;
		width = dw;
		height = dh;
		ID = tileID;
	}

	Vector2 getPosition(){ return position; }
	float getWidth(){ return width; }
	float getHeight(){ return height; }
	void render(Bitmap* sprite){

		if (sprite){
			int spriteWidth = sprite->getWidth();
			int spriteHeight = sprite->getHeight();

			int ncols = spriteWidth / width;

			int currentCol = ID % ncols;
			int currentRow = ID / ncols;

			int cellX = width*currentCol;
			int cellY = height * currentRow;
			sprite->drawAt(position.x, position.y, cellX, cellY, width, height);
		}
		else{
			glBegin(GL_POLYGON);
			glVertex2f(position.x, position.y); //Top left
			glVertex2f(position.x + width, position.y); //Top right
			glVertex2f(position.x + width, position.y + height); //Bottom right
			glVertex2f(position.x, position.y + height); //Bottom left
			glEnd();
		}

	}
	~NewTile(){ cout << "Deleting tile" << endl; }
protected:
	float width;
	float height;
	int ID;
};

class NewWall :public NewTile{
public:
	NewWall(float dx, float dy, float dw, float dh, int tileID) :NewTile(dx, dy, dw, dh, tileID){

	}
};
#endif