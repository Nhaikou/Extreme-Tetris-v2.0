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

		sf::View newView(sf::FloatRect(0, 0, 200 + 64 + client->players[2]->board->grid[client->players[2]->board->getSize().x - 1][client->players[2]->board->getSize().y - 1].getPosition().x + 32, client->players[2]->board->grid[client->players[2]->board->getSize().x - 1][client->players[2]->board->getSize().y - 1].getPosition().y + 60));
		stateMachine->window.setView(newView);
		stateMachine->window.setSize(sf::Vector2u(200 + 64 + client->players[2]->board->grid[client->players[2]->board->getSize().x - 1][client->players[2]->board->getSize().y - 1].getPosition().x + 32, client->players[2]->board->grid[client->players[2]->board->getSize().x - 1][client->players[2]->board->getSize().y - 1].getPosition().y + 60));
	
		createAnimations();
	}
	else
	{
		client->standardInitialize();

		sf::View newView(sf::FloatRect(0, 0, 200 + client->players[client->playerCount - 1]->board->grid[client->players[client->playerCount - 1]->board->getSize().x - 1][client->players[client->playerCount - 1]->board->getSize().y - 1].getPosition().x + 32, client->players[client->playerCount - 1]->board->grid[client->players[client->playerCount - 1]->board->getSize().x - 1][client->players[client->playerCount - 1]->board->getSize().y - 1].getPosition().y + 32));
		stateMachine->window.setView(newView);
		stateMachine->window.setSize(sf::Vector2u(200 + client->players[client->playerCount - 1]->board->grid[client->players[client->playerCount - 1]->board->getSize().x - 1][client->players[client->playerCount - 1]->board->getSize().y - 1].getPosition().x + 32, client->players[client->playerCount - 1]->board->grid[client->players[client->playerCount - 1]->board->getSize().x - 1][client->players[client->playerCount - 1]->board->getSize().y - 1].getPosition().y + 32));
	}

	client->receive();
	createWalls();
	createNames();
	createScoreBoard();
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

	if (factoryMode)
	{
		workerLeft.update(dt);
		workerRight.update(dt);
		for (int i = 0; i < tracks.size(); ++i)
		{
			tracks[i].update(dt);
		}
	}

	for (int i = 0; i < client->players.size(); ++i)
	{
		client->players[i]->updateScoreText();
	}
}

void GameMode::draw(const float dt)
{
	for (int k = 0; k < client->players.size(); ++k)
	{
		for (int j = 2; j < client->players[k]->board->getSize().y; ++j)
		{
			for (int i = 0; i < client->players[k]->board->getSize().x; ++i)
			{
				stateMachine->window.draw(client->players[k]->board->grid[i][j]);
			}
		}

		for (int i = 2; i < client->players[k]->board->getSize().y; ++i)
		{
			stateMachine->window.draw(client->players[k]->board->gridSlice[i]);
		}

		stateMachine->window.draw(client->players[k]->playerInfoBox);
		stateMachine->window.draw(client->players[k]->scoreText);
	}

	for (int i = 0; i < playerNameTexts.size(); ++i)
	{
		stateMachine->window.draw(playerNameTexts[i]);
	}

	if (factoryMode)
	{
		stateMachine->window.draw(workerLeft);
		stateMachine->window.draw(workerRight);
		for (int i = 0; i < tracks.size(); ++i)
		{
			stateMachine->window.draw(tracks[i]);
		}
	}

	for (int i = 0; i < walls.size(); ++i)
	{
		stateMachine->window.draw(walls[i]);
	}

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

	stateMachine->window.draw(scoreBoard);
	for (int i = 0; i < client->playerCount; ++i)
	{
		stateMachine->window.draw(scoreBoardTexts[i]);
	}
}

void GameMode::createAnimations()
{
	workerLeftTex.loadFromFile("../Assets/WorkerLeft.png");
	workerRightTex.loadFromFile("../Assets/WorkerRight.png");
	trackTex.loadFromFile("../Assets/Track.png");

	workerLeft.setTexture(workerLeftTex);
	workerLeft.setFrameSize(sf::Vector2u(16 * 4, 16 * 5));
	workerLeft.setPosition(0, stateMachine->window.getSize().y - 16 * 5);
	workerLeft.setFrequenzy(100);
	workerRight.setTexture(workerRightTex);
	workerRight.setFrameSize(sf::Vector2u(16 * 4, 16 * 5));
	workerRight.setCurrentFrame(sf::Vector2i(6, 0));
	workerRight.setPosition(stateMachine->window.getSize().x - 16 * 4 - 200, stateMachine->window.getSize().y - 16 * 5);
	workerRight.setFrequenzy(100);
	track.setTexture(trackTex);
	track.setFrameSize(sf::Vector2u(16 * 2, 16 * 2));
	track.setFrequenzy(100);
	track.setPosition(client->players[0]->board->grid[0][client->players[0]->board->getSize().y - 1].getPosition() + sf::Vector2f(0, 16));
	tracks.push_back(track);
	while (track.getPosition().x + 16 < client->players[2]->board->grid[client->players[2]->board->getSize().x - 1][0].getPosition().x)
	{
		track.move(32, 0);
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
			if (factoryMode && i > 0 && j <= 1)
			{
				wall.setPosition(client->players[i]->board->grid[0][j].getPosition() - sf::Vector2f(16, 0));
				walls.push_back(wall);
			}
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

			if (factoryMode && j == client->players[0]->board->getSize().y - 1)
			{
				glass.setPosition(client->players[i]->board->grid[client->players[i]->board->getSize().x - 1][j].getPosition() + sf::Vector2f(16, 16));
				walls.push_back(glass);
				glass.setPosition(client->players[i]->board->grid[client->players[i]->board->getSize().x - 1][j].getPosition() + sf::Vector2f(16, 32));
				walls.push_back(glass);
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

	if (factoryMode)
	{
		wall.setPosition(client->players[0]->board->grid[0][client->players[0]->board->getSize().y - 1].getPosition() + sf::Vector2f(-16, 16));
		walls.push_back(wall);
		wall.setPosition(client->players[0]->board->grid[0][client->players[0]->board->getSize().y - 1].getPosition() + sf::Vector2f(-16, 32));
		walls.push_back(wall);
		wall.setPosition(client->players[2]->board->grid[client->players[2]->board->getSize().x - 1][client->players[2]->board->getSize().y - 1].getPosition() + sf::Vector2f(16, 16));
		walls.push_back(wall);
		wall.setPosition(client->players[2]->board->grid[client->players[2]->board->getSize().x - 1][client->players[2]->board->getSize().y - 1].getPosition() + sf::Vector2f(16, 32));
		walls.push_back(wall);
	}

	floor.setPosition(client->players[boardCount - 1]->board->grid[client->players[boardCount - 1]->board->getSize().x - 1][client->players[boardCount - 1]->board->getSize().y - 1].getPosition() + sf::Vector2f(16, 16));
	if (factoryMode)
	{
		floor.move(0, 32);
	}
	walls.push_back(floor);
}

void GameMode::createNames()
{
	font.loadFromFile("../Assets/8bitOperatorPlus8-Regular.ttf");
	playerNameText.setFont(font);
	playerNameText.setCharacterSize(16);
	playerNameText.setColor(sf::Color::Black);

	if (factoryMode)
	{
		playerNameText.setPosition(client->players[0]->board->getPosition().x + 2, -2);
		if (client->clientNumber == 0)
		{
			playerNameText.setString(client->playerNames[client->playerCount - 1]);
		}
		else
		{
			playerNameText.setString(client->playerNames[client->clientNumber - 1]);
		}
		playerNameTexts.push_back(playerNameText);

		playerNameText.setPosition(client->players[1]->board->getPosition().x + 2, -2);
		playerNameText.setString(client->playerNames[client->clientNumber]);
		playerNameTexts.push_back(playerNameText);

		playerNameText.setPosition(client->players[2]->board->getPosition().x + 2, -2);
		if (client->clientNumber == client->playerCount - 1)
		{
			playerNameText.setString(client->playerNames[0]);
		}
		else
		{
			playerNameText.setString(client->playerNames[client->clientNumber + 1]);
		}
		playerNameTexts.push_back(playerNameText);
	}
	else
	{
		playerNameText.setPosition(client->players[0]->board->getPosition().x + 2, -2);
		playerNameText.setString(client->playerNames[client->clientNumber]);
		playerNameTexts.push_back(playerNameText);

		for (int i = 0; i < client->playerCount; ++i)
		{
			if (i < client->clientNumber && i + 1 < client->playerCount)
			{
				playerNameText.setPosition(client->players[i + 1]->board->getPosition().x + 2, -2);
				playerNameText.setString(client->playerNames[i]);
				playerNameTexts.push_back(playerNameText);
			}
			else if (i > client->clientNumber)
			{
				playerNameText.setPosition(client->players[i]->board->getPosition().x + 2, -2);
				playerNameText.setString(client->playerNames[i]);
				playerNameTexts.push_back(playerNameText);
			}
		}
	}	
}

void GameMode::createScoreBoard()
{
	sf::Text scoreBoardText;
	scoreBoardText.setFont(font);
	scoreBoardText.setCharacterSize(16);
	scoreBoardText.setColor(sf::Color::Black);

	scoreBoard.setPosition(walls[walls.size() - 1].getPosition().x + 16, 0);
	if (factoryMode)
	{
		scoreBoard.move(64, 0);
	}
	scoreBoard.setSize(sf::Vector2f(200, client->playerCount * 30));
	scoreBoard.setFillColor(sf::Color(185, 122, 87, 255));

	scoreBoardText.setPosition(scoreBoard.getPosition() + sf::Vector2f(5, 5));
	for (int i = 0; i < client->playerCount; ++i)
	{
		scoreBoardTexts.push_back(scoreBoardText);
		scoreBoardText.move(0, scoreBoardText.getGlobalBounds().height + 10);
	}
}