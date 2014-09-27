#pragma once
#include "Block.h"

const float oneMove = 32.f;

class PlayerBlock{
public:
	typedef std::unique_ptr<PlayerBlock> Ptr;
public:
	enum Type{
		L_shape,
		T_shape,
		S_shape,
		O_shape,
		I_shape,
		Z_shape,
		J_shape,
		TypeCount
	};
public:
	//PlayerBlock(Type type, std::vector< Block::Ptr >&);
	PlayerBlock(Type type, const TextureHolder& textures, sf::FloatRect Area, bool isTracker);
	~PlayerBlock();

	void setCorePos(sf::Vector2f newV);
	
	
	void movePosition(sf::Vector2f);

	void draw(sf::RenderTarget& target);
	void handleEvent(const sf::Event&, std::vector<Entity::Ptr>& toBeChecked);
	void update(sf::Time dt);

	void pushBlocks(sf::Vector2f);
	//set new form and change it
	void setForm(int newForm);

	sf::Vector2f getCorePosition() const { return mCorePos; }

	PlayerBlock::Type getShapeType() const { return mType; }

	int getCurrentForm() const { return mCurrentForm; }

	bool hitLand();
	int hitSides();

	void transferBlocks(std::vector<Entity::Ptr>& tobeFilled)
	{
		for (Entity::Ptr& ptr : mBlocks)
			tobeFilled.push_back(std::move(ptr));
	}

	bool blockCollide(std::vector<Entity::Ptr>& toBeChecked);

	void handleRealTimeInput(std::vector<Entity::Ptr>& toBeChecked);

private:	
	void initializeBlocks();
	void changeForm(std::vector<Entity::Ptr>& toBeChecked);
	void revertChanges();
	
	Block::Type intToColor(int id) const;
private:
	std::vector<Entity::Ptr> mBlocks;
	Type mType;
	int mCurrentForm;
	int mPrevForm;
	bool mIsTracker;

	sf::FloatRect mArea;
	sf::Vector2f mCorePos;
};

