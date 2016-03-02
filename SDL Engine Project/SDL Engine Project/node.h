#include "vector2.h"
class Node {
public:

	Vector2 position;
	bool walkable;

	int gCost, hCost, fCost;
	int gridX, gridY;

	
	int heapIndex;

	Node(bool _walkable, Vector2 _pos, int _gridX, int _gridY) {
		walkable = _walkable;
		position = _pos;
		gridX = _gridX;
		gridY = _gridY;
	}

	

	int CompareTo(Node node) {
		int compare = 0;
		
			

		return 0;
	}

private:

};