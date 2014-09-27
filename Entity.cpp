#include "Entity.h"


Entity::Entity()
:mVelocity(0.f,0.f)
{
}


Entity::~Entity()
{
}


void Entity::draw(sf::RenderTarget& target
	, sf::RenderStates states) const
{

}

void Entity::update(sf::Time dt)
{
	move(mVelocity * dt.asSeconds());
}

bool Entity::collidedLand(sf::FloatRect rect)
{
	return false;
}

int Entity::collidedSide(sf::FloatRect rect)
{
	return false;
}