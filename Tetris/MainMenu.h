#ifndef MAINMENU_H
#define MAINMENU_H

#include "State.h"

class MainMenu : public State
{
public:
	MainMenu(StateMachine* sm){ stateMachine = sm; }
	~MainMenu(){}

	void handleInput(){}
	void update(const float dt){}
	void draw(const float dt){}

protected:
	void onInitialize(){}
private:

};
#endif;