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
			server->sendBoard(i);
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
	
}