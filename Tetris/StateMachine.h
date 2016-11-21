#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <stack>
#include <time.h>
#include <ctime>

class State;

class StateMachine
{
public:
	StateMachine();
	~StateMachine();

	std::stack<State*> states;

	void pushState(State* state);
	void popState();
	void changeState(State* state);
	State* peekState();
	void gameLoop();

	sf::RenderWindow window;
};
#endif;