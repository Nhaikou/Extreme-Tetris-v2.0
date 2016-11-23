#ifndef GAMEMODE_H
#define GAMEMODE_H

#include "State.h"
#include "Server.h"
#include "Board.h"
#include "Block.h"
#include "BlockI.h"
#include "BlockO.h"
#include "BlockZ.h"
#include "BlockS.h"
#include "BlockL.h"
#include "BlockJ.h"
#include "BlockT.h"
#include "Bag.h"

#include <sstream>

class GameMode : public State
{
public:
	GameMode(StateMachine* sm, Server *srvr, bool factory);
	~GameMode();

	void update(const float dt);
	void spawnUpdate();

protected:
	void onInitialize();

private:
	Server *server = nullptr;
	bool factoryMode;
};

#endif