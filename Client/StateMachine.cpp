#include "StateMachine.h"
#include "State.h"

StateMachine::StateMachine()
{
	windowWidth = 500;
	windowHeight = 50;
	window.create(sf::VideoMode(windowWidth, windowHeight), "Tetris");	/* Needs better name.. */
	window.setFramerateLimit(60);
}

StateMachine::~StateMachine()
{
	while (!states.empty())
	{
		popState();
	}
}

void StateMachine::pushState(State* state)
{
	state->initialize();
	states.push(state);
}

void StateMachine::popState()
{
	delete states.top();
	states.pop();
}

void StateMachine::changeState(State* state)
{
	if (!states.empty())
	{
		popState();
	}

	pushState(state);
}

State* StateMachine::peekState()
{
	if (states.empty())
	{
		return nullptr;
	}
	return states.top();
}

void StateMachine::gameLoop()
{
	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Time elapsed = clock.restart();
		float dt = elapsed.asMilliseconds();

		if (peekState() == nullptr)
		{
			continue;
		}
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			peekState()->handleInput();
		}
		peekState()->update(dt);
		window.clear(sf::Color(0, 0, 0, 0));
		peekState()->draw(dt);
		window.display();
	}
}