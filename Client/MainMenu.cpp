#include "MainMenu.h"


MainMenu::MainMenu(StateMachine* sm)
{
	stateMachine = sm;
}


MainMenu::~MainMenu()
{
	delete stateMachine;
	delete client;
}

void MainMenu::onInitialize()
{
	client = new Client();
}

void MainMenu::handleInput()
{
	if (stateMachine->event.type == sf::Event::KeyPressed)
	{
		client->sendInput(stateMachine->event.key.code);
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
