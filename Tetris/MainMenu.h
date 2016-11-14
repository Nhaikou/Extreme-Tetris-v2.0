#ifndef MAINMENU_H
#define MAINMENU_H

#include "State.h"
#include "Server.h"

class MainMenu : public State
{
public:
	MainMenu(StateMachine* sm);
	~MainMenu();

	void handleInput();
	void update(const float dt);
	void draw(const float dt);

protected:
	void onInitialize();
private:
	Server *server = nullptr;
	sf::Font font;
	sf::Text text;
	int clientKey = -1;
};
#endif;