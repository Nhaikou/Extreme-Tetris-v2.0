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
}