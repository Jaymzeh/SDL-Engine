#ifndef VECTOR_2_H
#define VECTOR_2_H

#include <cmath>

class Vector2{
public:
	float x;
	float y;

	Vector2(){
		x = 0; y = 0;
	}

	Vector2(float X, float Y){
		x = X;
		y = Y;
	}

	float distance(Vector2 end){
		return sqrt((x - end.x) * (x - end.x) + (y - end.y) * (y - end.y));
	}
	float distance(float dx, float dy) {
		return sqrt((x - dx) * (x - dx) + (y - dy) * (y - dy));
	}

	void setPoint(float dx, float dy){
		x = dx;
		y = dy;
	}

};

#endif