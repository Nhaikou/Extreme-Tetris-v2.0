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

void Standard::handleInput()
{
	
}

void Standard::update(const float dt)
{
	for (int i = 0; i < server->clients.size(); ++i)
	{
		server->players[i]->clientKey = server->receiveButtonPress(0);

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
}

void Standard::draw(const float dt)
{
	
}