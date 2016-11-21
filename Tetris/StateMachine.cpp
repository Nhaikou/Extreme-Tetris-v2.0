#include "StateMachine.h"
#include "State.h"

StateMachine::StateMachine()
{
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
	while (true)
	{
		sf::Time elapsed = clock.restart();
		float dt = elapsed.asMilliseconds();
		peekState()->update(dt);
		window.display();
	}
}