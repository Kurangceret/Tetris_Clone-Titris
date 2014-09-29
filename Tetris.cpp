#include "Tetris.h"
#include "Constant.h"
#include <iostream>
#include <algorithm>
#include <string>

//631.f = Y, the bottom

Tetris::Tetris(sf::RenderWindow& window, TextureHolder& textures, sf::Font& font)
:
mWindow(window),
mElapsedTime(sf::Time::Zero),
mTextures(),
mVisualBorder(sf::Vector2f(boundingX,boundingY)),
mTrackerRect(sf::Vector2f(140.f, 100.f)),
mNextText(),
mPlayerBlock(nullptr),
mTrackerBlock(nullptr),
mNextBlock(nullptr),
mUpdateTracker(true),
mArea(),
mNextArea(),
mRealScore(0),
mHighScoreTxt()
{
	loadTextures();

	mVisualBorder.setFillColor(sf::Color::Black);
	mVisualBorder.setOutlineColor(sf::Color::Red);
	mVisualBorder.setOutlineThickness(thickness);
	centerOrigin(mVisualBorder);
	mVisualBorder.setPosition(sf::Vector2f(mWindow.getSize().x / 2 - 70, mWindow.getSize().y / 2 + 4));
	mArea = mVisualBorder.getGlobalBounds();
	//std::cout << rect.width << " " << rect.height << std::endl;
	
	mTrackerRect.setFillColor(sf::Color::Black);
	mTrackerRect.setOutlineColor(sf::Color::Blue);
	mTrackerRect.setOutlineThickness(thickness);
	centerOrigin(mTrackerRect);
	mTrackerRect.setPosition(mArea.left + mArea.width + 73.f, mArea.top + 70.f);
	mNextArea = mTrackerRect.getGlobalBounds();

	mNextText.setString(std::string("Next Block:"));
	mNextText.setFont(font);
	mNextText.setCharacterSize(16);
	centerOrigin(mNextText);
	mNextText.setPosition(mNextArea.left + mNextArea.width / 2, mNextArea.top - 15.f);

	mHighScoreTxt.setString(std::string("High Score : " + std::to_string(mRealScore)));
	mHighScoreTxt.setFont(font);
	mHighScoreTxt.setCharacterSize(12);
	centerOrigin(mHighScoreTxt);
	mHighScoreTxt.setPosition(mNextText.getPosition() + sf::Vector2f(-30.f, 150.f));
	

	PlayerBlock::Ptr playerBlocks(new PlayerBlock(intToType(randomInt(7)), mTextures, mArea, false));
	mPlayerBlock = playerBlocks.get();

	mPlayers.push_back(std::move(playerBlocks));

	createTracker();

	mNextBlock = PlayerBlock::Ptr(new PlayerBlock(intToType(randomInt(7)), mTextures, mArea, true));
	mNextBlock->setCorePos(sf::Vector2f(mNextArea.left + mNextArea.width - 60.f, mNextArea.top + 35.f));
	mNextBlock->setForm(mNextBlock->getCurrentForm());

	//prepareNewBlock();

}


Tetris::~Tetris()
{
}

void Tetris::loadTextures()
{
	mTextures.load(Textures::Red_Square, "Media/Texture/element_red_square.png");
	mTextures.load(Textures::Blue_Square, "Media/Texture/element_blue_square.png");
	mTextures.load(Textures::Yellow_Square, "Media/Texture/element_yellow_square.png");
	mTextures.load(Textures::Green_Square, "Media/Texture/element_green_square.png");
	mTextures.load(Textures::Purple_Square, "Media/Texture/element_purple_square.png");
	mTextures.load(Textures::Selector, "Media/Texture/selectorC.png");
}

void Tetris::draw()
{
	mWindow.draw(mVisualBorder);
	mWindow.draw(mTrackerRect);
	mWindow.draw(mNextText);
	mWindow.draw(mHighScoreTxt);

	if (mNextBlock)
		mNextBlock->draw(mWindow);

	if (mPlayerBlock)
		mPlayerBlock->draw(mWindow);

	if (mTrackerBlock && !mUpdateTracker)
		mTrackerBlock->draw(mWindow);

	for (Entity::Ptr& block : mAllBlocks)
		mWindow.draw(*block);

}

void Tetris::update(sf::Time dt)
{
	if (mPlayerBlock){
		mPlayerBlock->update(dt);
		mPlayerBlock->handleRealTimeInput(mAllBlocks);
		pushPlayerBlock(mPlayerBlock, dt);
	}
	if (mTrackerBlock)
		mTrackerBlock->update(dt);

	mHighScoreTxt.setString(std::string("High Score : " + std::to_string(mRealScore)));

	adaptPlayerBlocks();
	trackPlayerBlock(dt);
}


void Tetris::handleEvent(const sf::Event& event)
{
	if (mPlayerBlock)
		mPlayerBlock->handleEvent(event, mAllBlocks);

	if (event.type != sf::Event::KeyPressed)
		return;
	if (event.key.code == sf::Keyboard::Space && !mUpdateTracker){
		mPlayerBlock->setCorePos(mTrackerBlock->getCorePosition());
		mPlayerBlock->setForm(mPlayerBlock->getCurrentForm());

		resetPlayerBlock();

		prepareNewBlock();

		checkForFilledSpaces();
	}
}

void Tetris::pushPlayerBlock(PlayerBlock* blocks, sf::Time dt)
{
	sf::Time interval = sf::seconds(1.5f);
	mElapsedTime += dt;
	
	while (mElapsedTime >= interval){
		mElapsedTime -= interval;
		blocks->pushBlocks(sf::Vector2f(0.f, 1.f));
		blocksCollision();
	}
}

void Tetris::pushTrackerBlock()
{
	mTrackerBlock->pushBlocks(sf::Vector2f(0.f, 1.f));
	trackerCollision();
}

void Tetris::blocksCollision()
{
	if (mPlayerBlock->blockCollide(mAllBlocks)){
		mPlayerBlock->pushBlocks(sf::Vector2f(0.f, -1.f));
		resetPlayerBlock();
		
		prepareNewBlock();

		checkForFilledSpaces();
	}
	
}

void Tetris::trackerCollision()
{
	if (mTrackerBlock->blockCollide(mAllBlocks)){
		mTrackerBlock->pushBlocks(sf::Vector2f(0.f, -1.f));
		mUpdateTracker = false;
	}
}

void Tetris::adaptPlayerBlocks()
{
	if (!mPlayerBlock)
		return;

	if (mPlayerBlock->hitLand()){
		mPlayerBlock->pushBlocks(sf::Vector2f(0.f, -1.f));
		resetPlayerBlock();
			
		prepareNewBlock();

		checkForFilledSpaces();
			
	}
	//check whether it collides with the X axis
	int direction = mPlayerBlock->hitSides();
	//if direction is 1, we collided to the left and adjust it
	//if direction is -1, we collided to the right and adjust it
	if (direction != 0)
		mPlayerBlock->pushBlocks(sf::Vector2f(direction, 0.f));

	if (!mTrackerBlock || !mUpdateTracker)
		return;

	if (mTrackerBlock->hitLand()){
		mTrackerBlock->pushBlocks(sf::Vector2f(0.f, -1.f));
		mUpdateTracker = false;
	}
		
	
}

void Tetris::resetPlayerBlock()
{
	mPlayerBlock->transferBlocks(mAllBlocks);
	mTrackerBlock = mPlayerBlock = nullptr;
	mPlayers.clear();
	
	mElapsedTime = sf::Time::Zero;
}

void Tetris::prepareNewBlock()
{
	/*int type = randomInt(7);

	PlayerBlock::Ptr playerBlocks(new PlayerBlock(intToType(type), mTextures, mArea, false));
	mPlayerBlock = playerBlocks.get();

	mPlayers.push_back(std::move(playerBlocks));

	createTracker();*/

	PlayerBlock::Ptr playerBlocks(new PlayerBlock(mNextBlock->getShapeType(), mTextures, mArea, false));
	mPlayerBlock = playerBlocks.get();
	
	mPlayers.push_back(std::move(playerBlocks));

	createTracker();

	mNextBlock.reset();

	mNextBlock = PlayerBlock::Ptr(new PlayerBlock(intToType(randomInt(7)), mTextures, mArea, true));
	mNextBlock->setCorePos(sf::Vector2f(mNextArea.left + mNextArea.width - 60.f, mNextArea.top + 35.f));
	mNextBlock->setForm(mNextBlock->getCurrentForm());
}

PlayerBlock::Type Tetris::intToType(int id) const
{
	switch (id){
	case 0:
		return PlayerBlock::Type::L_shape;
	case 1:
		return PlayerBlock::Type::T_shape;
	case 2:
		return PlayerBlock::Type::S_shape;
	case 3:
		return PlayerBlock::Type::O_shape;
	case 4:
		return PlayerBlock::Type::I_shape;
	case 5:
		return PlayerBlock::Type::Z_shape;
	case 6:
		return PlayerBlock::Type::J_shape;
	default:
		return PlayerBlock::Type::L_shape;
	}
}

void Tetris::createTracker()
{
	if (!mPlayerBlock)
		return;

	PlayerBlock::Type type = mPlayerBlock->getShapeType();
	PlayerBlock::Ptr tracker(new PlayerBlock(type, mTextures, mArea, true));
	mTrackerBlock = tracker.get();

	mUpdateTracker = true;
	mPlayers.push_back(std::move(tracker));
}

void Tetris::trackPlayerBlock(sf::Time dt)
{
	if (!mTrackerBlock)
		return;

	int currentForm = mPlayerBlock->getCurrentForm();
	sf::Vector2f curPos = mPlayerBlock->getCorePosition();

	if (curPos.x != mTrackerBlock->getCorePosition().x
		|| mTrackerBlock->getCurrentForm() != currentForm){
		mTrackerBlock->setCorePos(curPos);
		mTrackerBlock->setForm(currentForm);
		mUpdateTracker = true;
	}

	if (!mUpdateTracker)
		return;
			

		
	pushTrackerBlock();
	
}

void Tetris::checkForFilledSpaces()
{
	if (mAllBlocks.empty())
		return;

	std::vector<float> checkers;
	std::size_t i = 0, j;
	float lowestY = 631.f;
	float oneMove = 32.f;

	for (; i < 20; i++){
		j = 0;
		for (Entity::Ptr& ptr : mAllBlocks){
			if (ptr->getPosition().y == lowestY)
				j++;
		}
		if (j == 10)
			checkers.push_back(lowestY);

		lowestY -= oneMove;
	}
	freeSpaces(checkers);
}

void Tetris::freeSpaces(std::vector<float>& checkers)
{
	if (checkers.empty())
		return;

	typedef std::vector<Entity::Ptr>::iterator iter;
	
	int countScore = 0;
	for (float y : checkers){
		countScore++;
		for (iter start = mAllBlocks.begin(); start != mAllBlocks.end();){
			if (start->get()->getPosition().y == y)
				start = mAllBlocks.erase(start);
			else
				start++;
		}
	}

	mRealScore += countScore * perLine;

	sf::Vector2f movement = sf::Vector2f(0.f, 32.f);
	std::size_t c;
	for (Entity::Ptr& ptr : mAllBlocks){
		c = 0;
		
		for (float boundY : checkers){
			if (ptr->getPosition().y < boundY)
				c++;
		}
		ptr->setPosition(ptr->getPosition() + sf::Vector2f(0.f, 32.f * c));
	}
}

