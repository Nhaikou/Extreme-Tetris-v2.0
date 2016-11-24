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
		createAnimations();

		sf::View newView(sf::FloatRect(0, 0, client->players[client->playerCount - 1]->board->grid[client->players[client->playerCount - 1]->board->getSize().x - 1][client->players[client->playerCount - 1]->board->getSize().y - 1].getPosition().x + 32, client->players[client->playerCount - 1]->board->grid[client->players[client->playerCount - 1]->board->getSize().x - 1][client->players[client->playerCount - 1]->board->getSize().y - 1].getPosition().y + 60));
		stateMachine->window.setView(newView);
		stateMachine->window.setSize(sf::Vector2u(client->players[client->playerCount - 1]->board->grid[client->players[client->playerCount - 1]->board->getSize().x - 1][client->players[client->playerCount - 1]->board->getSize().y - 1].getPosition().x + 32, client->players[client->playerCount - 1]->board->grid[client->players[client->playerCount - 1]->board->getSize().x - 1][client->players[client->playerCount - 1]->board->getSize().y - 1].getPosition().y + 60));
	}
	else
	{
		client->standardInitialize();

		sf::View newView(sf::FloatRect(0, 0, client->players[client->playerCount - 1]->board->grid[client->players[client->playerCount - 1]->board->getSize().x - 1][client->players[client->playerCount - 1]->board->getSize().y - 1].getPosition().x + 32, client->players[client->playerCount - 1]->board->grid[client->players[client->playerCount - 1]->board->getSize().x - 1][client->players[client->playerCount - 1]->board->getSize().y - 1].getPosition().y + 32));
		stateMachine->window.setView(newView);
		stateMachine->window.setSize(sf::Vector2u(client->players[client->playerCount - 1]->board->grid[client->players[client->playerCount - 1]->board->getSize().x - 1][client->players[client->playerCount - 1]->board->getSize().y - 1].getPosition().x + 32, client->players[client->playerCount - 1]->board->grid[client->players[client->playerCount - 1]->board->getSize().x - 1][client->players[client->playerCount - 1]->board->getSize().y - 1].getPosition().y + 32));
	}

	createWalls();
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

	system("cls");
	std::cout << "Score: " << client->players[client->clientNumber]->score << std::endl;
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

	for (int i = 0; i < walls.size(); ++i)
	{
		stateMachine->window.draw(walls[i]);
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

void GameMode::createAnimations()
{
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
}

void GameMode::createWalls()
{
	unsigned boardCount = client->playerCount;

	wallTex.loadFromFile("../Assets/Brick.png");
	floorTex.loadFromFile("../Assets/Brick3.png");
	glassTex.loadFromFile("../Assets/Glass.png");
	wall.setTexture(wallTex);
	if (factoryMode)
	{
		glass.setTexture(glassTex);
		boardCount = 3;
	}
	floor.setTexture(floorTex);

	for (int i = 0; i < boardCount; ++i)
	{
		for (int j = 0; j < client->players[0]->board->getSize().y; ++j)
		{
			if (factoryMode && i > 0)
			{
				glass.setPosition(client->players[i]->board->grid[0][j].getPosition() - sf::Vector2f(16, 0));
				walls.push_back(glass);
			}
			else
			{
				wall.setPosition(client->players[i]->board->grid[0][j].getPosition() - sf::Vector2f(16, 0));
				walls.push_back(wall);
			}
			if (i == boardCount - 1)
			{
				wall.setPosition(client->players[i]->board->grid[client->players[i]->board->getSize().x - 1][j].getPosition() + sf::Vector2f(16, 0));
				walls.push_back(wall);
			}
		}

		for (int j = 0; j < client->players[0]->board->getSize().x; ++j)
		{
			floor.setPosition(client->players[i]->board->grid[j][client->players[i]->board->getSize().y - 1].getPosition() + sf::Vector2f(0, 16));
			if (factoryMode)
			{
				floor.move(0, 32);
			}
			walls.push_back(floor);
		}
		floor.setPosition(client->players[i]->board->grid[0][client->players[i]->board->getSize().y - 1].getPosition() + sf::Vector2f(-16, 16));
		if (factoryMode)
		{
			floor.move(0, 32);
		}
		walls.push_back(floor);
	}
	floor.setPosition(client->players[boardCount - 1]->board->grid[client->players[boardCount - 1]->board->getSize().x - 1][client->players[boardCount - 1]->board->getSize().y - 1].getPosition() + sf::Vector2f(16, 16));
	if (factoryMode)
	{
		floor.move(0, 32);
	}
	walls.push_back(floor);
}