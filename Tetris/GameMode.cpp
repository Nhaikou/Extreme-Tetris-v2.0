#include "GameMode.h"


GameMode::GameMode(StateMachine* sm, Server *srvr, bool factory)
{
	server = srvr;
	stateMachine = sm;
	factoryMode = factory;
}


GameMode::~GameMode()
{

}

void GameMode::onInitialize()
{
	if (factoryMode)
	{
		factoryInitialize();
	}
	else
	{
		standardInitialize();
	}
	for (int i = 0; i < server->clients.size(); ++i)
	{
		server->sendBoard(i, factoryMode);
	}
}

void GameMode::standardInitialize()
{
	server->packet.clear();

	server->packet << 0;
	server->packet << server->players[0]->board->getSize().x << server->players[0]->board->getSize().y << server->players[0]->board->getSpawnPoint().x << server->players[0]->board->getSpawnPoint().y;

	for (int i = 0; i < server->clients.size(); ++i)
	{
		server->packet << server->players[i]->board->getPosition().x << server->players[i]->board->getPosition().y;
	}

	for (int i = 0; i < server->clients.size(); ++i)
	{
		server->clients[i]->send(server->packet);
	}
}

void GameMode::factoryInitialize()
{
	for (int i = 0; i < server->clients.size(); ++i)
	{
		server->packet.clear();
		server->packet << 1;
		server->packet << i;
		server->packet << server->players[0]->board->getSize().x << server->players[0]->board->getSize().y << server->players[0]->board->getSpawnPoint().x << server->players[0]->board->getSpawnPoint().y;
		server->clients[i]->send(server->packet);
	}
}

void GameMode::update(const float dt)
{
	for (int i = 0; i < server->clients.size(); ++i)
	{
		server->players[i]->clientKey = server->receiveButtonPress(i);

		if (server->players[i]->clientKey != -1)
		{
			server->players[i]->updateClient();
			server->sendBoard(i, factoryMode);
			server->players[i]->clientKey = -1;
		}

		if (server->players[i]->dropUpdate(dt))
		{
			server->sendBoard(i, factoryMode);
		}
	}

	if (factoryMode)
	{
		server->updateLine(dt);
	}
}