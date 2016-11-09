#ifndef MAINMENU_H
#define MAINMENU_H

#include "State.h"
#include "Network.h"
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
	Server server;
	sf::Font font;
	sf::Text text;
	Network *network = nullptr;
	int clientKey = 0;
	sf::Image image;
	sf::Texture tex;
	sf::Sprite spr;
	float timer = 0;
};
#endif;