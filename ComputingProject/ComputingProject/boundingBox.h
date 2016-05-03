#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "freeglut\freeglut.h"
#include <iostream>
#include "vector2.h"

class BoundingBox {
public:

	void setBox(int dx, int dy, int dw, int dh) {
		position.setPoint(dx, dy);
		w = dw;
		h = dh;

		left = position.x;
		top = position.y;
		right = position.x + w;
		bottom = position.y + h;

	}

	bool intersects(BoundingBox &b) {
		return !(left >= b.right ||
			right <= b.left ||
			top >= b.bottom ||
			bottom <= b.top);

		return true;
	}

	void render() {
		glColor3f(0, 1, 0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(left, top);
		glVertex2f(right, top);
		glVertex2f(right, bottom);
		glVertex2f(left, bottom);
		glEnd();
	}

	Vector2 getPosition() { return position; }
private:
	Vector2 position;
	int w, h;
	int left, top, right, bottom;
protected:
};

#endif