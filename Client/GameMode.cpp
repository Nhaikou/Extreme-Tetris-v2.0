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

		workerLeftTex.loadFromFile("../Assets/WorkerLeft.png");
		workerRightTex.loadFromFile("../Assets/WorkerRight.png");
		trackTex.loadFromFile("../Assets/Track.png");

		workerLeft.setTexture(workerLeftTex);
		workerLeft.setFrameSize(sf::Vector2u(16 * 4, 16 * 5));
		workerLeft.setPosition(0, 0);
		workerRight.setTexture(workerRightTex);
		workerRight.setFrameSize(sf::Vector2u(16 * 4, 16 * 5));
		workerRight.setCurrentFrame(sf::Vector2i(6, 0));
		workerRight.setPosition(0, 0);
		track.setTexture(trackTex);
		track.setFrameSize(sf::Vector2u(16 * 2, 16 * 2));
		track.setPosition(workerLeft.getPosition() + sf::Vector2f(0, workerLeft.getGlobalBounds().height));
		for (int i = workerLeft.getPosition().x; i < workerRight.getPosition().x + workerRight.getGlobalBounds().width; i += track.getGlobalBounds().width)
		{
			track.move(sf::Vector2f(track.getGlobalBounds().width, 0));
			tracks.push_back(track);
		}

		int counter = 1;
		while (client->players[0]->board->walls.size() != 0)
		{
			client->players[0]->board->walls.erase(client->players[0]->board->walls.begin());
			client->players[2]->board->walls.erase(client->players[2]->board->walls.begin() + counter);
			counter++;
		}

		sf::View newView(sf::FloatRect(16, 0, client->players[client->players.size() - 1]->board->floors[client->players[client->players.size() - 1]->board->floors.size() - 1].getPosition().x - 16, client->players[client->players.size() - 1]->board->floors[client->players[client->players.size() - 1]->board->floors.size() - 1].getPosition().y + 16));
		stateMachine->window.setView(newView);
		stateMachine->window.setSize(sf::Vector2u(client->players[client->players.size() - 1]->board->floors[client->players[client->players.size() - 1]->board->floors.size() - 1].getPosition()) + sf::Vector2u(-16, 16));
	}
	else
	{
		client->standardInitialize();
		sf::View newView(sf::FloatRect(0, 0, client->players[client->players.size() - 1]->board->floors[client->players[client->players.size() - 1]->board->floors.size() - 1].getPosition().x + 16, client->players[client->players.size() - 1]->board->floors[client->players[client->players.size() - 1]->board->floors.size() - 1].getPosition().y + 16));
		stateMachine->window.setView(newView);
		stateMachine->window.setSize(sf::Vector2u(client->players[client->players.size() - 1]->board->floors[client->players[client->players.size() - 1]->board->floors.size() - 1].getPosition()) + sf::Vector2u(16, 16));
	}
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
	client->receive();

	if (client->updateAnimations)
	{
		workerLeft.update(1);
		workerRight.update(1);
		for (int i = 0; i < tracks.size(); ++i)
		{
			tracks[i].update(1);
		}
		client->updateAnimations = false;
	}
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

		for (int i = 0; i < client->players[k]->board->getSize().y; ++i)
		{
			stateMachine->window.draw(client->players[k]->board->gridSlice[i]);
		}
	}

	for (int j = 0; j < client->players.size(); ++j)
	{
		for (int i = 0; i < client->players[j]->board->walls.size(); ++i)
		{
			stateMachine->window.draw(client->players[j]->board->walls[i]);
		}

		for (int i = 0; i < client->players[j]->board->floors.size(); ++i)
		{
			stateMachine->window.draw(client->players[j]->board->floors[i]);
		}
	}

	/*
	for (int k = 0; k < client->players.size(); ++k)
	{
		for (int j = 0; j < client->players[k]->nextBlockSize.y; ++j)
		{
			for (int i = 0; i < client->players[k]->nextBlockSize.x; ++i)
			{
				stateMachine->window.draw(client->players[k]->nextBlockSprites[i][j]);
			}
		}
	}
	*/

	/*
	if (factoryMode)
	{
		stateMachine->window.draw(workerLeft);
		stateMachine->window.draw(workerRight);
		for (int i = 0; i < tracks.size(); ++i)
		{
			stateMachine->window.draw(tracks[i]);
		}
	}
	*/
}

