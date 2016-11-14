#include "Standard.h"

Standard::Standard(StateMachine* sm, Server *srvr)
{
	stateMachine = sm;
	server = srvr;
}

Standard::~Standard()
{

}

void Standard::onInitialize()
{
	if (!font.loadFromFile("../Assets/8bitOperatorPlus8-Bold.ttf"))
	{
		std::cout << "Error loading font" << std::endl;
	}
	scoreText.setFont(font);
	scoreText.setColor(sf::Color::White);
	scoreText.setCharacterSize(12);
	scoreText.setPosition(300, 10);
}

void Standard::handleInput()
{
	
}

void Standard::update(const float dt)
{
	bool updateClient = false;
	for (int i = 0; i < server->clients.size(); ++i)
	{
		server->players[i]->clientKey = server->receiveButtonPress(0);

		if (server->players[i]->updateClient())
		{
			MinMaxPositions minMax = server->players[i]->currentBlock->calculateMinAndMaxPositions();
			server->sendRenderTexture(sf::Vector2f(minMax.minX, minMax.minY), sf::Vector2u(minMax.maxX, minMax.maxY));
			server->players[i]->clientKey = -1;
		}

		//ss.str("");
		//ss << board->getScore();
		//scoreText.setString(ss.str());
		
		server->players[i]->dropUpdate(dt);
	}
}

void Standard::draw(const float dt)
{
	server->renderTexture.clear(sf::Color::Black);
	for (int k = 0; k < server->players.size(); ++k)
	{
		for (int j = 0; j < server->players[k]->board->getSize().y; ++j)
		{
			for (int i = 0; i < server->players[k]->board->getSize().x; ++i)
			{
				if (server->networking)
				{
					server->renderTexture.draw(server->players[k]->board->grid[i][j]);
				}
				else
				{
					stateMachine->window.draw(server->players[k]->board->grid[i][j]);
				}
			}
		}
	}

	//stateMachine->window.draw(scoreText);
	server->renderTexture.display();
}