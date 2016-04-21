#ifndef TILE_H
#define TILE_H

#include <iostream>
#include "freeglut\freeglut.h"
#include "vector2.h"
#include "boundingBox.h"
#include "aniSprite.h"

using std::cout;
using std::endl;

class BaseTile {
public:
	virtual Vector2 getPosition() = 0;
	virtual float getWidth() = 0;
	virtual float getHeight() = 0;
	virtual void render(Bitmap* bitmap) = 0;
	virtual BoundingBox getBox() = 0;
	virtual int getID() = 0;
	virtual ~BaseTile() {};
};

class Tile :public BaseTile {
private:
	Vector2 position;
public:

	Tile() {
		width = 1;
		height = 1;
		ID = 0;
	}
	Tile(float dx, float dy) {
		position.x = dx;
		position.y = dy;
		width = 1;
		height = 1;
		bBox.setBox(position.x, position.y, width, height);
		ID = 0;
	}
	Tile(float dx, float dy, float dw, float dh) {
		position.x = dx;
		position.y = dy;
		width = dw;
		height = dh;
		bBox.setBox(position.x, position.y, width, height);
		ID = 0;
	}

	Tile(float dx, float dy,
		float dw, float dh, int tileID) {
		position.x = dx;
		position.y = dy;
		width = dw;
		height = dh;
		ID = tileID;
		bBox.setBox(position.x, position.y, width, height);
	}

	Vector2 getPosition() { return position; }
	BoundingBox getBox() { return bBox; }
	float getWidth() { return width; }
	float getHeight() { return height; }
	int getID() { return ID; }
	void render(Bitmap* sprite) {

		if (sprite) {
			int spriteWidth = sprite->getWidth();
			int spriteHeight = sprite->getHeight();

			int ncols = spriteWidth / width;

			int currentCol = ID % ncols;
			int currentRow = ID / ncols;

			int cellX = width * currentCol;
			int cellY = height * currentRow;
			sprite->drawAt(position.x, position.y, cellX, cellY, width, height);
		}
		else {
			glBegin(GL_POLYGON);
			glVertex2f(position.x, position.y); //Top left
			glVertex2f(position.x + width, position.y); //Top right
			glVertex2f(position.x + width, position.y + height); //Bottom right
			glVertex2f(position.x, position.y + height); //Bottom left
			glEnd();
		}

	}

	void move(float dx, float dy) {

		bBox.setBox(position.x = +dx, position.y = +dy, width, height);
		position.x += dx;
		position.y += dy;
	}

	~Tile() { cout << "Deleting tile" << endl; }
protected:
	float width;
	float height;
	BoundingBox bBox;
	int ID;
};

class TileDecorator :public BaseTile {
private:
	BaseTile *tile;

public:
	TileDecorator(BaseTile *t) { tile = t; }
	Vector2 getPosition() { return tile->getPosition(); }
	float getWidth() { return tile->getWidth(); }
	float getHeight() { return tile->getHeight(); }
	int getID() { return tile->getID(); }
	void render(Bitmap *bitmap) { tile->render(bitmap); }
	BoundingBox getBox() { return tile->getBox(); }
	~TileDecorator() { delete tile; }

};

class GroundTile :public TileDecorator {
public:
	GroundTile(BaseTile *t) : TileDecorator(t) {};
	Vector2 getPosition() { return TileDecorator::getPosition(); }
	float getWidth() { return TileDecorator::getWidth(); }
	float getHeight() { return TileDecorator::getHeight(); }
	int getID() { return TileDecorator::getID(); }
	void render(Bitmap *bitmap) { TileDecorator::render(bitmap); }
	BoundingBox getBox() { return TileDecorator::getBox(); }
	~GroundTile() { cout << "Deleting GroundTile" << endl; }
};

class WallTile :public TileDecorator {
public:
	WallTile(BaseTile *t) : TileDecorator(t) {};
	Vector2 getPosition() { return TileDecorator::getPosition(); }
	float getWidth() { return TileDecorator::getWidth(); }
	float getHeight() { return TileDecorator::getHeight(); }
	int getID() { return TileDecorator::getID(); }
	void render(Bitmap *bitmap) { TileDecorator::render(bitmap); }
	BoundingBox getBox() { return TileDecorator::getBox(); }
	~WallTile() { cout << "Deleting WallTile" << endl; }
};

class WallBottomTile :public TileDecorator {
public:
	WallBottomTile(BaseTile *t) : TileDecorator(t) {};
	Vector2 getPosition() { return TileDecorator::getPosition(); }
	float getWidth() { return TileDecorator::getWidth(); }
	float getHeight() { return TileDecorator::getHeight(); }
	int getID() { return TileDecorator::getID(); }
	void render(Bitmap *bitmap) { TileDecorator::render(bitmap); }
	BoundingBox getBox() { return TileDecorator::getBox(); }
	~WallBottomTile() { cout << "Deleting WallTile" << endl; }
};

class DoorTile :public TileDecorator {
public:
	DoorTile(BaseTile *t) : TileDecorator(t) {};
	Vector2 getPosition() { return TileDecorator::getPosition(); }
	float getWidth() { return TileDecorator::getWidth(); }
	float getHeight() { return TileDecorator::getHeight(); }
	int getID() { return TileDecorator::getID(); }
	void render(Bitmap *bitmap) { TileDecorator::render(bitmap); }
	BoundingBox getBox() { return TileDecorator::getBox(); }
	~DoorTile() { cout << "Deleting DoorTile" << endl; }
};
#endif