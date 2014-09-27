#include "Application.h"
#include "Constant.h"

const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

Application::Application()
:mWindow(sf::VideoMode(winWidth,winHeight), "Titris Alpha Build", sf::Style::Close),
mFont(),
mTextures(),
mStacks(State::Context(mWindow,mFont, mTextures))
{
	mFont.loadFromFile("Media/Sansation.ttf");
	registerStates();
	mWindow.setPosition(sf::Vector2i(300, 40));
	
	mStacks.pushState(States::Menu);
}


Application::~Application()
{
}


void Application::run()
{
	sf::Time limitTime = sf::Time::Zero;
	sf::Clock clock;
	sf::Time sleepTime = sf::Time::Zero;
	while (mWindow.isOpen()){
		limitTime += clock.restart();
		
		//when it is not the next fps, put CPU 
		//to sleep, to save CPU power
		if (limitTime < TimePerFrame){
			sleepTime = sf::seconds((TimePerFrame.asSeconds() - limitTime.asSeconds()));
			sf::sleep(sleepTime);
		}

		if (TimePerFrame <= limitTime){
			limitTime -= TimePerFrame;
			processInputs();
			update(TimePerFrame);
			if (mStacks.isEmpty())
				mWindow.close();
		}
		render();
	}
}

void Application::update(sf::Time dt)
{
	mStacks.update(dt);
}

void Application::processInputs()
{
	sf::Event event;
	while (mWindow.pollEvent(event)){
		mStacks.handleEvent(event);

		if (event.type == sf::Event::Closed)
			mWindow.close();
	}
}

void Application::render()
{
	mWindow.clear();

	mStacks.draw();
	mWindow.setView(mWindow.getDefaultView());

	mWindow.display();
}

void Application::registerStates()
{
	mStacks.registerState<MenuState>(States::Menu);
	mStacks.registerState<GameState>(States::Game);
	mStacks.registerState<PauseState>(States::Pause);
}