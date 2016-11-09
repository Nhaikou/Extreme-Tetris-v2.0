#include "StateMachine.h"
#include "Client.h"

int main()
{
	StateMachine sm;
	sm.pushState(new Client(&sm));
	sm.gameLoop();
	return 0;
}