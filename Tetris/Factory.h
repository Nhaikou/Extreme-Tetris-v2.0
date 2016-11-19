#ifndef FACTORY_H
#define FACTORY_H

#include "Bag.h"
#include "Server.h"
#include "State.h"
#include "Board.h"
#include "Block.h"
#include "BlockI.h"
#include "BlockO.h"
#include "BlockZ.h"
#include "BlockS.h"
#include "BlockL.h"
#include "BlockJ.h"
#include "BlockT.h"

class Factory : public State
{
public:
	Factory(StateMachine* sm, sf::Vector2u size, Server *srvr);
	~Factory();

	void handleInput();
	void update(const float dt);
	void draw(const float dt);

	void moveLineLeft();
	void moveLineRight();

protected:
	void onInitialize();

private:
	Server *server = nullptr;
	sf::Vector2u boardSize;
};

#endif