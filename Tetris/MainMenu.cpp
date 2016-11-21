#include "MainMenu.h"
#include "GameMode.h"

MainMenu::MainMenu(StateMachine* sm)
{
	stateMachine = sm;
}

MainMenu::~MainMenu()
{

}

void MainMenu::onInitialize()
{
	server = new Server();
}

void MainMenu::update(const float dt)
{
	for (int i = 0; i < server->clients.size(); ++i)
	{
		clientKey = server->receiveButtonPress(i);
		if (clientKey != -1)
		{
			if (clientKey == sf::Keyboard::F)
			{
				stateMachine->pushState(new GameMode(stateMachine, server, true));
			}
			if (clientKey == sf::Keyboard::Space)
			{
				stateMachine->pushState(new GameMode(stateMachine, server, false));
			}
			clientKey = -1;
		}
	}
}