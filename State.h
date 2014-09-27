#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "StateIdentifier.h"
#include "ResourceHolder.h"

class StateStack;

class State{
public:
	struct Context{
		Context(sf::RenderWindow& window, sf::Font& font, TextureHolder& textureHolder)
		:window(&window),font(&font), textureHolder(&textureHolder){}

		sf::RenderWindow *window;
		sf::Font *font;
		TextureHolder *textureHolder;
	};

	typedef std::unique_ptr<State> Ptr;
public:
	State(StateStack& stack, Context context);
	virtual ~State();

	virtual void draw() = 0;
	virtual bool update(sf::Time dt) = 0;
	virtual bool handleEvent(const sf::Event&) = 0;

protected:
	void requestStackClear();
	void requestStackPop();
	void requestStackPush(States::ID);

	Context getContext()  const { return mContext; }
private:
	StateStack *mStack;
	Context mContext;
};

