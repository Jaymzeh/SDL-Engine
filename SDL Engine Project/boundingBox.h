#ifndef BOUNDING_BOX
#define BOUNDING_BOX

#include "freeglut\glut.h"
#include <iostream>
#include "vector2.h"

class BoundingBox{
public:

	void setBox(float dx, float dy, float dw, float dh){
		std::cout << "Creating BoundingBox at (" << dx << ", " << dy << ")" << std::endl;
		position.setPoint(dx, dy);
		w = dw;
		h = dh;

		left = position.x;
		top = position.y;
		right = position.x + w;
		bottom = position.y + h;

	}

	bool intersects(BoundingBox &b){
		return !(left > b.right ||
			right < b.left ||
			top>b.bottom ||
			bottom < b.top);

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

	Vector2 getPosition(){ return position; }
private:
	Vector2 position;
	float w, h;
	float left, top, right, bottom;
protected:
};

#endif