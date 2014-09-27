#pragma once
#include <SFML/Graphics.hpp>
#include "Texture.h"
#include <memory>

class Entity : public sf::Drawable, public sf::Transformable, public sf::NonCopyable{
public:
	typedef std::unique_ptr<Entity> Ptr;
public:
	Entity();
	virtual ~Entity();

	void accelerate(sf::Vector2f addV){ mVelocity += addV; }
	void setVelocity(sf::Vector2f newV){ mVelocity = newV; }
	sf::Vector2f getVelocity() const { return mVelocity; }

	virtual void update(sf::Time dt);
	virtual bool collidedLand(sf::FloatRect rect);
	virtual int collidedSide(sf::FloatRect rect);
	virtual sf::FloatRect getBoundingRect(){ return sf::FloatRect(); }

protected:
	virtual void draw(sf::RenderTarget& target
		, sf::RenderStates states) const;
	
private:
	sf::Vector2f mVelocity;

};

