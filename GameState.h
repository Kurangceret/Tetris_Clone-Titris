#pragma once
#include "StateStack.h"
#include "Tetris.h"

class GameState :public State{
public:
	GameState(StateStack& stack, Context context);
	~GameState();

	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event&);

private:
	Tetris mTetris;
};

