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
	spawnUpdate();
	for (int i = 0; i < server->players.size(); ++i)
	{
		server->players[i]->spawnBlock();
	}


	if (factoryMode)
	{
		server->factoryInitialize();
	}
	else
	{
		server->standardInitialize();
	}
	for (int i = 0; i < server->clients.size(); ++i)
	{
		server->sendBoard(i, factoryMode);
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

	spawnUpdate();
}

void GameMode::spawnUpdate()
{
	unsigned smallestNumber = server->players[0]->currentBlockId;

	for (int i = 0; i < server->clients.size(); ++i)
	{
		if (server->players[i]->blockSpawned)
		{
			server->players[i]->blockSpawned = false;
			if (server->players[i]->currentBlockId >= server->bags.size())
			{
				server->newBag();
			}
			server->players[i]->nextBlock = server->bags[server->players[i]->currentBlockId];
			server->players[i]->currentBlockId++;
		}

		if (server->players[i]->currentBlockId < smallestNumber)
		{
			smallestNumber = server->players[i]->currentBlockId;
		}
	}

	for (int i = 0; i < smallestNumber; ++i)
	{
		server->bags.erase(server->bags.begin());
	}

	for (int i = 0; i < server->clients.size(); ++i)
	{
		server->players[i]->currentBlockId -= smallestNumber;
	}
}