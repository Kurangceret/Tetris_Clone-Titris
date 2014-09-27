#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "StateStack.h"

class PauseState :public State{
public:
	PauseState(StateStack& stack, Context context);
	~PauseState();

	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event&);
private:
	sf::Sprite backgroundSprite;
	sf::Text pausedText;
	sf::Text instructionText;
};

#endif