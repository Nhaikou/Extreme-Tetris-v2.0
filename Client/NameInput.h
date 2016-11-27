#ifndef NAMEINPUT_H
#define NAMEINPUT_H

#include "State.h"
#include "MainMenu.h"

class NameInput : public State
{
public:
	NameInput(StateMachine *sm);
	~NameInput();

	void handleInput();
	void update(const float dt);
	void draw(const float dt);

protected:
	void onInitialize();

private:
	sf::Font font;
	sf::Text nameText;
	std::string nameString;
};

#endif