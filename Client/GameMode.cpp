#include "GameMode.h"


GameMode::GameMode(StateMachine *sm, Client *cl, bool factory)
{
	stateMachine = sm;
	client = cl;
	factoryMode = factory;
}


GameMode::~GameMode()
{
	delete client;
	delete stateMachine;
}

void GameMode::onInitialize()
{
	if (factoryMode)
	{
		client->factoryInitialize();
	}
	else
	{
		client->standardInitialize();
	}
	sf::View newView(sf::FloatRect(0, 0, client->players[client->players.size() - 1]->board->walls[client->players[client->players.size() - 1]->board->walls.size() - 1].getPosition().x + 16, client->players[client->players.size() - 1]->board->walls[client->players[client->players.size() - 1]->board->walls.size() - 1].getPosition().y + 16));
	stateMachine->window.setView(newView);
	stateMachine->window.setSize(sf::Vector2u(client->players[client->players.size() - 1]->board->walls[client->players[client->players.size() - 1]->board->walls.size() - 1].getPosition()) + sf::Vector2u(16, 16));
}

void GameMode::handleInput()
{
	if (stateMachine->event.type == sf::Event::KeyPressed)
	{
		client->sendInput(stateMachine->event.key.code);
	}
}

void GameMode::update(const float dt)
{
	client->receiveBoard();
}

void GameMode::draw(const float dt)
{
	for (int k = 0; k < client->players.size(); ++k)
	{
		for (int j = 0; j < client->players[k]->board->getSize().y; ++j)
		{
			for (int i = 0; i < client->players[k]->board->getSize().x; ++i)
			{
				stateMachine->window.draw(client->players[k]->board->grid[i][j]);
			}
		}
	}
	for (int j = 0; j < client->players.size(); ++j)
	{
		for (int i = 0; i < client->players[j]->board->walls.size(); ++i)
		{
			stateMachine->window.draw(client->players[j]->board->walls[i]);
		}
	}
}
