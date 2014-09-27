#pragma once
#include "Entity.h"
#include <iostream>


class Block : public Entity{
public:
	typedef std::unique_ptr<Block> Ptr;
public:
	enum Type{
		Red,
		Blue,
		Yellow,
		Green,
		Purple,
		Selector
	};
public:
	Block(Block::Type, const TextureHolder&);
	~Block();
	
	bool collidedLand(sf::FloatRect rect);
	int collidedSide(sf::FloatRect rect);
	sf::FloatRect getBoundingRect(){  return getTransform().transformRect(mSprite.getGlobalBounds()); }
protected:
	virtual void draw(sf::RenderTarget& target
		, sf::RenderStates states) const;
private:
	Textures::ID typeToTexture(Type type) const;
private:
	sf::Sprite mSprite;
	Type mType;

	
};

