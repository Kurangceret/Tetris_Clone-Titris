#include "PlayerBlock.h"
#include "DataTables.h"
#include "Utility.h"
#include <iostream>

namespace{
	std::vector<ShapeData> Table = initializeShapeData();
}

PlayerBlock::PlayerBlock(Type type, const TextureHolder& textures
	, sf::FloatRect area, bool isTracker)
:
mType(type), 
mBlocks(), 
mCurrentForm(0),
mPrevForm(0),
mArea(area),
mCorePos(),
mIsTracker(isTracker)
{
	if (!mIsTracker){
		Block::Type colorType = intToColor(randomInt(5));
		for (int i = 0; i < 4; i++){
			Block::Ptr block(new Block(colorType, textures));
			mBlocks.push_back(std::move(block));
		}
	}
	else{
		for (int i = 0; i < 4; i++){
			Block::Ptr block(new Block(Block::Type::Selector, textures));
			mBlocks.push_back(std::move(block));
		}
	}
	initializeBlocks();
	
}


PlayerBlock::~PlayerBlock()
{
}


void PlayerBlock::movePosition(sf::Vector2f pos)
{
	for (Entity::Ptr& ptr : mBlocks)
		ptr->setPosition(ptr->getPosition() + pos);
}

void PlayerBlock::draw(sf::RenderTarget& target) 
{
	for (Entity::Ptr& ptr : mBlocks)
		target.draw(*ptr);
}

void PlayerBlock::update(sf::Time dt)
{
	std::size_t i = 0;
	for (Entity::Ptr& ptr : mBlocks){
		ptr->update(dt);
		if (i == 0){
			mCorePos = ptr->getPosition();
			i++;
		}
	}
		
}

void PlayerBlock::handleEvent(const sf::Event& event,
	std::vector<Entity::Ptr>& toBeChecked)
{
	if (event.type != sf::Event::KeyPressed)
		return;

	if (event.key.code == sf::Keyboard::Up){
		mPrevForm = mCurrentForm;
		mCurrentForm++;
		mCurrentForm = mCurrentForm % Table[mType].numShape;
		changeForm(toBeChecked);
	}
	if (event.key.code == sf::Keyboard::Left){
		pushBlocks(sf::Vector2f(-1.f, 0.f));
		if (blockCollide(toBeChecked))
			pushBlocks(sf::Vector2f(1.f, 0.f));
	}
	
	if (event.key.code == sf::Keyboard::Right){
		pushBlocks(sf::Vector2f(1.f, 0.f));
		if (blockCollide(toBeChecked))
			pushBlocks(sf::Vector2f(-1.f, 0.f));
	}
	
}

void PlayerBlock::handleRealTimeInput(std::vector<Entity::Ptr>& toBeChecked)
{
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		pushBlocks(sf::Vector2f(-1.f, 0.f));
		if (blockCollide(toBeChecked))
			pushBlocks(sf::Vector2f(1.f, 0.f));
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		pushBlocks(sf::Vector2f(1.f, 0.f));
		if (blockCollide(toBeChecked))
			pushBlocks(sf::Vector2f(-1.f, 0.f));
	}*/

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		pushBlocks(sf::Vector2f(0.f, 1.f));
		if (blockCollide(toBeChecked))
			pushBlocks(sf::Vector2f(0.f, -1.f));
	}
		
}

void PlayerBlock::initializeBlocks()
{
	
	std::size_t i = 0;
	sf::Vector2f addiPos;


	for (Entity::Ptr& ptr : mBlocks){
		if (i == 0){
			ptr->setPosition(mArea.left + mArea.width / 2 - 16, mArea.top + oneMove / 2);
			mCorePos = ptr->getPosition();
		}
		else{
			addiPos = Table[mType].shape[mCurrentForm].pos[i];
			ptr->setPosition(mCorePos + sf::Vector2f(addiPos.x
				* oneMove, addiPos.y * oneMove));
		}

		i++;
	}
}

Block::Type PlayerBlock::intToColor(int id) const
{
	switch (id){
	case 0:
		return Block::Type::Red;
	case 1:
		return Block::Type::Blue;
	case 2:
		return Block::Type::Yellow;
	case 3:
		return Block::Type::Green;
	case 4:
		return Block::Type::Purple;
	default:
		return Block::Type::Red;
	}
}

void PlayerBlock::setCorePos(sf::Vector2f newV)
{
	mBlocks[0]->setPosition(newV);
	//changeForm();
}

void PlayerBlock::changeForm(std::vector<Entity::Ptr>& toBeChecked = std::vector<Entity::Ptr>())
{
	std::size_t i = 0;
	sf::Vector2f addiPos;

	for (Entity::Ptr& ptr : mBlocks){
		if (i != 0){
			addiPos = Table[mType].shape[mCurrentForm].pos[i];
			ptr->setPosition(mCorePos + sf::Vector2f(addiPos.x
				* oneMove, addiPos.y * oneMove));
		}
		else{
			mCorePos = ptr->getPosition();
		}
		i++;
	}
	if (toBeChecked.empty())
		return;

	if (blockCollide(toBeChecked) /*|| hitSides() != 0*/ || hitLand()){
		mCurrentForm = mPrevForm;
		changeForm();
		revertChanges();
	}
	
}

void PlayerBlock::revertChanges()
{

}

void PlayerBlock::setForm(int newForm)
{
	if (newForm >= Table[mType].numShape)
		return;

	mCurrentForm = newForm;
	changeForm();
}

void PlayerBlock::pushBlocks(sf::Vector2f v)
{
	for (Entity::Ptr& ptr : mBlocks){
		ptr->setPosition(ptr->getPosition() + sf::Vector2f(v.x * oneMove, v.y * oneMove));
		//std::cout << ptr->getPosition().y << std::endl;
		//std::cout << " " << std::endl;
	}
}

bool PlayerBlock::hitLand()
{
	for (Entity::Ptr& ptr : mBlocks){
		if (ptr->collidedLand(mArea))
			return true;
	}
	return false;
}

int PlayerBlock::hitSides()
{
	for (Entity::Ptr& ptr : mBlocks){
		if (ptr->collidedSide(mArea) != 0)
			return ptr->collidedSide(mArea);
	}
	return 0;
}

bool PlayerBlock::blockCollide(std::vector<Entity::Ptr>& toBeChecked)
{
	for (Entity::Ptr& ptr : mBlocks){
		for (Entity::Ptr& chk : toBeChecked){
			if (ptr->getBoundingRect().intersects(chk->getBoundingRect()))
				return true;
		}
	}
	return false;
}