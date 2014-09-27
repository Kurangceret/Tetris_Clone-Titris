#ifndef APPLICATION_H
#define APPLICATION_H
#define WIN32_LEAN_AND_MEAN

#include "MenuState.h"
#include "GameState.h"
#include "PauseState.h"



class Application{
public:
	Application();
	~Application();


	void run();
	void render();
	void processInputs();
	void update(sf::Time dt);
	void registerStates();
private:
	StateStack mStacks;
	sf::RenderWindow mWindow;
	sf::Font mFont;
	TextureHolder mTextures;

	
};


#endif