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
	answer.setFont(font);
	answer.setFillColor(sf::Color::White);
	answer.setCharacterSize(30);
	question = answer;
	question.setString("Player Name: ");
	answer.move(question.getGlobalBounds().width, 0);
}

void NameInput::handleInput()
{
	if (stateMachine->event.type == sf::Event::TextEntered)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			if (!nameSet)
			{
				nameString = answerString;
				nameSet = true;
				question.setString("Ip Address: ");
				answerString = sf::IpAddress::getLocalAddress().toString();
				while (answerString[answerString.size() - 1] != '.')
				{
					answerString.pop_back();
				}
				maxSize = 15;
			}
			else
			{
				stateMachine->pushState(new MainMenu(stateMachine, nameString, answerString));
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && answerString.size() > 0)
		{
			answerString.pop_back();
		}
		else if (stateMachine->event.text.unicode < 128 && answerString.size() < maxSize && !sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
		{
			answerString += sf::String(stateMachine->event.text.unicode);
		}
		answer.setString(answerString);
	}
}

void NameInput::update(const float dt)
{

}

void NameInput::draw(const float dt)
{
	stateMachine->window.draw(question);
	stateMachine->window.draw(answer);
}
