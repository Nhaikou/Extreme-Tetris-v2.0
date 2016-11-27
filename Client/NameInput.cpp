#include "NameInput.h"


NameInput::NameInput(StateMachine *sm)
{
	stateMachine = sm;
}


NameInput::~NameInput()
{

}

void NameInput::onInitialize()
{
	font.loadFromFile("../Assets/8bitOperatorPlus8-Regular.ttf");
	nameText.setFont(font);
	nameText.setFillColor(sf::Color::White);
	nameText.setCharacterSize(30);
}

void NameInput::handleInput()
{
	if (stateMachine->event.type == sf::Event::TextEntered)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			stateMachine->pushState(new MainMenu(stateMachine, nameString));
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && nameString.size() > 0)
		{
			nameString.pop_back();
		}
		else if (stateMachine->event.text.unicode < 128 && nameString.size() < 10)
		{
			nameString += sf::String(stateMachine->event.text.unicode);
		}
		nameText.setString(nameString);
	}
}

void NameInput::update(const float dt)
{

}

void NameInput::draw(const float dt)
{
	stateMachine->window.draw(nameText);
}
