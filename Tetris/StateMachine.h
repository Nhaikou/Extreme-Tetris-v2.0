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

	sf::RenderWindow window;
	sf::Event event;

	void pushState(State* state);
	void popState();
	void changeState(State* state);
	State* peekState();
	void gameLoop();

	float getWindowWidth(){ return windowWidth; }
	float getWindowHeight(){ return windowHeight; }
private:
	float windowWidth, windowHeight = 0;
};
#endif;