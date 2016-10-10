#ifndef MAINMENU_H
#define MAINMENU_H

#include "State.h"
#include "Network.h"

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
	sf::Font font;
	sf::Text text;
	Network *network = nullptr;
};
#endif;