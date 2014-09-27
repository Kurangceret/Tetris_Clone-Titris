#ifndef DATATABLES_H
#define DATATABLES_H
#include "PlayerBlock.h"

namespace Blocks{
	enum ID{
		Block1,
		Block2,
		Block3,
		Block4
	};
}

//struct Pos{
	//std::vector<sf::Vector2f> pos;
//};

struct Shape{
	sf::Vector2f pos[4];
};

struct ShapeData{
	//how many form it has
	int numShape;
	Shape shape[4];
};




std::vector<ShapeData> initializeShapeData();

#endif