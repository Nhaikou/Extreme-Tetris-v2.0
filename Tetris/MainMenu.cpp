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

	keys.resize(server->clients.size());
}

void MainMenu::update(const float dt)
{
	for (int i = 0; i < server->clients.size(); ++i)
	{
		clientKey = server->receiveButtonPress(i);
		if (clientKey == sf::Keyboard::F || clientKey == sf::Keyboard::S)
		{
			keys[i] = clientKey;
		}
	}

	
	int counterS = 0, counterF = 0, playerCounter = 0;

	for (int j = 0; j < keys.size(); ++j)
	{
		if (keys[j] == sf::Keyboard::F)
		{
			counterF++;
			playerCounter++;
		}
		if (keys[j] == sf::Keyboard::S)
		{
			counterS++;
			playerCounter++;
		}
	}
	if (keys.size() == playerCounter)
	{
		if (counterF > counterS)
		{
			server->sendState(true);
			stateMachine->pushState(new GameMode(stateMachine, server, true));
		}
		else if (counterF < counterS)
		{
			server->sendState(false);
			stateMachine->pushState(new GameMode(stateMachine, server, false));
		}
		else if (counterF == counterS)
		{
			int randomState = rand() % 2;
			server->sendState(randomState);
			stateMachine->pushState(new GameMode(stateMachine, server, randomState));
		}
	}
}