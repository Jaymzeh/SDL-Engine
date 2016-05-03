#ifndef VECTOR_2_H
#define VECTOR_2_H

#include <cmath>

class Vector2 {
public:
	int x;
	int y;

	Vector2() {
		x = 0; y = 0;
	}

	Vector2(int X, int Y) {
		x = X;
		y = Y;
	}

	float distance(Vector2 end) {
		return (float)sqrt((x - end.x) * (x - end.x) + (y - end.y) * (y - end.y));
	}
	float distance(int dx, int dy) {
		return (float)sqrt((x - dx) * (x - dx) + (y - dy) * (y - dy));
	}
	void add(Vector2 point) {
		x += point.x;
		y += point.y;
	}

	void add(int dx, int dy) {
		x += x;
		y += y;
	}

	void setPoint(int dx, int dy) {
		x = dx;
		y = dy;
	}

};

#endif