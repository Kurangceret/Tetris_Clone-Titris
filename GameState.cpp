#include "GameState.h"


GameState::GameState(StateStack& stack, Context context)
:State(stack, context),
mTetris(*context.window, *context.textureHolder, *context.font)
{

}


GameState::~GameState()
{
}

void GameState::draw()
{
	mTetris.draw();
}

bool GameState::update(sf::Time dt)
{
	mTetris.update(dt);
	return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
	mTetris.handleEvent(event);

	// Escape pressed, trigger the pause screen
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
		//requestStackPop();
		requestStackPush(States::Pause);
	}

	return true;
}