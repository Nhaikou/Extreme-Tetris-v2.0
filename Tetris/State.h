#ifndef STATE_H
#define STATE_H

#include "StateMachine.h"

class State
{
public:
	State(){ initialized = false; }
	~State(){}

	StateMachine* stateMachine;

	void initialize()
	{
		if (initialized)
		{
			return;
		}

		onInitialize();

		initialized = true;
	}

	virtual void update(const float dt) = 0;

private:
	bool initialized;

protected:
	virtual void onInitialize(){}
};
#endif;