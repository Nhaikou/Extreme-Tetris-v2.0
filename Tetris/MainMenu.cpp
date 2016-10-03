#include "MainMenu.h"
#include "Standard.h"
#include "Factory.h"

MainMenu::MainMenu(StateMachine* sm)
{
	stateMachine = sm;
}

MainMenu::~MainMenu()
{

}

void MainMenu::onInitialize()
{
	if (!font.loadFromFile("../Assets/8bitOperatorPlus8-Bold.ttf"))
	{
		std::cout << "Error loading font" << std::endl;
	}
	
	text.setFont(font);
}

void MainMenu::handleInput()
{
	sf::Keyboard key;

	if (key.isKeyPressed(key.Space))
	{
		stateMachine->pushState(new Standard(stateMachine));
	}
	if (key.isKeyPressed(key.Return))
	{
		stateMachine->pushState(new Factory(stateMachine));
	}

	text.setString("Main Menu soon...");
	text.setCharacterSize(48);
	text.setColor(sf::Color::White);
}

void MainMenu::update(const float dt)
{

}

void MainMenu::draw(const float dt)
{
	stateMachine->window.draw(text);
}