#include "StateMachine.h"
#include "GameMode.h"
#include "MainMenu.h"

int main()
{
	StateMachine sm;
	sm.pushState(new MainMenu(&sm));
	sm.gameLoop();
	return 0;
}