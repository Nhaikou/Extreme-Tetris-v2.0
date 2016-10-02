#ifndef MAINMENU_H
#define MAINMENU_H

#include "State.h"

class MainMenu : public State
{
public:
	MainMenu(StateMachine* sm){ stateMachine = sm; }
	~MainMenu(){}

	void draw(const float dt){}
	void update(const float dt){}
	void handleInput(){}

protected:
	void onInitialize(){}
private:

};
#endif;