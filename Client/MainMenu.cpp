#include "MainMenu.h"


MainMenu::MainMenu(StateMachine* sm, std::string name)
{
	stateMachine = sm;
	playerName = name;
}


MainMenu::~MainMenu()
{
	delete stateMachine;
	delete client;
}

void MainMenu::onInitialize()
{
	client = new Client(playerName);
}

void MainMenu::handleInput()
{
	if (stateMachine->event.type == sf::Event::KeyPressed)
	{
		client->sendInput(stateMachine->event.key.code);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			std::cout << "You voted for Standard." << std::endl;
			std::cout << "Wait until everyone has voted. You can still change your vote." << std::endl;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			std::cout << "You voted for Factory." << std::endl;
			std::cout << "Wait until everyone has voted. You can still change your vote." << std::endl;
		}
	}
}

void MainMenu::update(const float dt)
{
	if (client->receiveState())
	{
		stateMachine->pushState(new GameMode(stateMachine, client, client->gameMode));
	}
}

void MainMenu::draw(const float dt)
{

}
