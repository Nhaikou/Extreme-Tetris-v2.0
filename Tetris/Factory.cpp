#include "Factory.h"

Factory::Factory(StateMachine* sm, sf::Vector2u size, Server *srvr)
{
	stateMachine = sm;
	boardSize = size;
	server = srvr;
}

Factory::~Factory()
{

}

void Factory::onInitialize()
{
	server->packet.clear();
	server->packet << 0; // secretCode;
	server->packet << server->players[0]->board->getSize().x << server->players[0]->board->getSize().y << server->players[0]->board->getSpawnPoint().x << server->players[0]->board->getSpawnPoint().y;

	for (int i = 0; i < server->clients.size(); ++i)
	{
		server->packet << server->players[i]->board->getPosition().x << server->players[i]->board->getPosition().y;
	}

	for (int i = 0; i < server->clients.size(); ++i)
	{
		server->clients[i]->send(server->packet);
	}

	for (int i = 0; i < server->clients.size(); ++i)
	{
		server->sendBoard(i);
	}
}

void Factory::handleInput()
{

}

void Factory::update(const float dt)
{
	for (int i = 0; i < server->clients.size(); ++i)
	{
		server->players[i]->clientKey = server->receiveButtonPress(i);

		if (server->players[i]->clientKey != -1)
		{
			server->players[i]->updateClient();
			server->sendBoard(i);
			server->players[i]->clientKey = -1;
		}

		if (server->players[i]->dropUpdate(dt))
		{
			server->sendBoard(i);
		}
	}

	server->updateLine(dt);
}

void Factory::draw(const float dt)
{

}