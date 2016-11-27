#include "StateMachine.h"
#include "NameInput.h"

int main()
{
	StateMachine sm;
	sm.pushState(new NameInput(&sm));
	sm.gameLoop();
	return 0;
}