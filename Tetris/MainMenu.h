#ifndef MAINMENU_H
#define MAINMENU_H

#include "State.h"
#include "Server.h"

class MainMenu : public State
{
public:
	MainMenu(StateMachine* sm);
	~MainMenu();

	void update(const float dt);

protected:
	void onInitialize();
private:
	Server *server = nullptr;
	int clientKey = -1;
};
#endif;