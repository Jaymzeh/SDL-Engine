/* AniSprite (Animated Sprite) class.
*
* Copyright (c) 2010, Alistair McMonnies
* alistair.mcmonnies@uws.ac.uk

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

alistair.mcmonnies@uws.ac.uk

last tested 14/10/2010
*
*/

#include "Bitmap.h"
#include "freeglut\freeglut.h"
#include"AniSprite.h"

// A general purpose initialization routine to support all constructors...
void AniSprite::init(int ix, int iy, int icols, int irows, int idx, int idy) {
	x = ix;
	y = iy;
	dx = idx;
	dy = idy;
	width = pic->getWidth();
	height = pic->getHeight();
	ncols = icols;
	nrows = irows;
	currentCell = 0;
	setSpriteSheetDimensions(width, height);
	ref_x = ref_y = 0;
	updatemode = UPDATEONASK;
	drawmode = NOFLIP;
}

BMPError AniSprite::getError() {
	if (pic != NULL) {
		return pic->getError();
	}
	else {
		return NO_ERROR;
	}
}

AniSprite::AniSprite(int initial_x, int initial_y, const char *file, int incols, int inrows) {
	pic = new Bitmap(file, true);
	this->init(initial_x, initial_y, incols, inrows, 0, 0);
}

AniSprite::AniSprite(int initial_x, int initial_y, Bitmap *ipic, int incols, int inrows) {
	pic = ipic;
	this->init(initial_x, initial_y, incols, inrows, 0, 0);
}

AniSprite::AniSprite(int initial_x, int initial_y, int initial_dx, int initial_dy, const char *file, int incols, int inrows) {
	pic = new Bitmap(file, true);
	this->init(initial_x, initial_y, incols, inrows, initial_dx, initial_dy);
}

AniSprite::AniSprite(int initial_x, int initial_y, int initial_dx, int initial_dy, Bitmap *ipic, int incols, int inrows) {
	pic = ipic;
	this->init(initial_x, initial_y, incols, inrows, initial_dx, initial_dy);
}

void AniSprite::draw() {
	int currentCol = currentCell % ncols;
	int currentRow = currentCell / ncols;
	int cx = cellWidth * currentCol;
	int cy = cellHeight * currentRow;
	if ((dx >= 0 && drawmode == AUTOFLIP) || drawmode == NOFLIP)
		pic->setOrientation(NORMAL);
	else
		pic->setOrientation(MIRROR_X);
	pic->drawAt(x - ref_x, y - ref_y, cx, cy, cellWidth, cellHeight);
}

void AniSprite::setUpdatemode(UpdateMode um) {
	updatemode = um;
}

void AniSprite::setDrawmode(DrawMode dm) {
	drawmode = dm;
}

void AniSprite::nextCell() {
	currentCell++;
	if (currentCell == ncols*nrows)
		currentCell = 0;
}

void AniSprite::prevCell() {
	currentCell--;
	if (currentCell<0)
		currentCell = ncols*nrows - 1;
}

void AniSprite::move() {
	x += dx;
	y += dy;
	if (updatemode == UPDATEONMOVE && dx != 0 || dy != 0) {
		nextCell();
	}
}

void AniSprite::move(float by_x, float by_y) {
	x += by_x;
	y += by_y;
	if (updatemode == UPDATEONMOVE) {
		nextCell();
	}
}

bool AniSprite::intersects(int xx, int yy, int ww, int hh) {
	if (x + cellWidth<xx || x>xx + ww)	// No overlap in x-axis
		return false;
	if (y + cellHeight<yy || y>yy + hh)	// No overlap in y-axis
		return false;
	// Overlaps in both axes, so...
	return true;
}

void AniSprite::calculate_cells() {
	// Figure out the cell width and height as a proportion of the picture...
	cellWidth = sheet_width / ncols;
	cellHeight = sheet_height / nrows;
}

void AniSprite::setSpriteSheetDimensions(int w, int h) {
	sheet_width = w;
	sheet_height = h;
	calculate_cells();
}

AniSprite::~AniSprite() {
	if (pic)
		delete pic;
}
