#include "Block.h"
#include "Utility.h"
#include "ResourceHolder.h"
#include <iostream>

Block::Block(Block::Type type, const TextureHolder& textures)
:mType(type), mSprite(textures.get(typeToTexture(type)))
{
	centerOrigin(mSprite);
	//mSprite.setColor(sf::Color::Color(0,55,25,255));
	//std::cout << mSprite.getGlobalBounds().width << mSprite.getGlobalBounds().height << std::endl;
}


Block::~Block()
{
}


Textures::ID Block::typeToTexture(Type type) const
{
	switch (type){
		case Type::Red:
				return Textures::Red_Square;
		case Type::Blue:
				return Textures::Blue_Square;
		case Type::Yellow:
				return Textures::Yellow_Square;
		case  Type::Green:
				return Textures::Green_Square;
		case Type::Purple:
				return Textures::Purple_Square;
		case Type::Selector:
				return Textures::Selector;
		default:
			return Textures::Red_Square;
	}
}

void Block::draw(sf::RenderTarget& target
	, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);
}

bool Block::collidedLand(sf::FloatRect rect)
{
	sf::Vector2f curPos = getPosition();
	float totalYBound = rect.height + rect.top;
	//std::cout << curPos.y << " " << totalYBound << std::endl;
	if (curPos.y >= totalYBound - 16.f)//working = 21.f
		return true;
	else
		return false;
}

int Block::collidedSide(sf::FloatRect rect)
{
	float curX = getPosition().x;
	
	float leftX = rect.left;
	float rightX = rect.left + rect.width + 2.f;
	//std::cout << " right side " << rightX << std::endl;
	if (curX - 16.f <= leftX)
		return 1;
	else if (curX + 16.f >= rightX)
		return -1;
	else
		return 0;
}