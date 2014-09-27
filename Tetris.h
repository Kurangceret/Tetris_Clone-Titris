#pragma once
#include <SFML/Graphics.hpp>
#include "CommandQueue.h"
#include "ResourceHolder.h"
#include "Utility.h"
#include "PlayerBlock.h"

class Tetris : public sf::NonCopyable{
public:
	Tetris(sf::RenderWindow& window, 
		TextureHolder& textures, sf::Font& font = sf::Font());
	~Tetris();
	
	void draw();
	void update(sf::Time dt);
	void handleEvent(const sf::Event&);

	//void handleEvent(const sf::Event&);
	//CommandQueue& getCommandQueue(){ return mCommandQueue; }
private:
	void loadTextures();

	void pushPlayerBlock(PlayerBlock* blocks,sf::Time dt);
	void pushTrackerBlock();

	void adaptPlayerBlocks();
	void prepareNewBlock();
	void resetPlayerBlock();

	void blocksCollision();
	void trackerCollision();

	void checkForFilledSpaces();
	void freeSpaces(std::vector<float>& checkers);

	void createTracker();
	void trackPlayerBlock(sf::Time dt);

	PlayerBlock::Type intToType(int id) const;
private:
	//CommandQueue mCommandQueue;
	TextureHolder mTextures;
	PlayerBlock *mPlayerBlock;
	PlayerBlock *mTrackerBlock;
	PlayerBlock::Ptr mNextBlock;

	//time for pushPlayerBlock func
	sf::Time mElapsedTime;
	sf::Text mNextText;
	sf::RenderWindow& mWindow;
	sf::RectangleShape mVisualBorder;
	sf::RectangleShape mTrackerRect;

	sf::FloatRect mArea;
	sf::FloatRect mNextArea;
	

	//will hold references to the new PlayerBlock object..
	//sounds stupid, but so far got no choices to fix the error without this vector
	//this vector will always have a size of 1
	std::vector< PlayerBlock::Ptr > mPlayers;
	//this will keep all the blocks
	std::vector< Entity::Ptr > mAllBlocks;

	bool mUpdateTracker;
	
};

