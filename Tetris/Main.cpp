#include "StateMachine.h"
#include "MainMenu.h"

int main()
{
	srand(time(NULL));
	StateMachine sm;
	sm.pushState(new MainMenu(&sm));
	sm.gameLoop();

	return 0;
}