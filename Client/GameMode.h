#ifndef GAMEMODE_H
#define GAMEMODE_H

#include "State.h"
#include "Client.h"
#include "AnimatedSprite.h"

class GameMode : public State
{
public:
	GameMode(StateMachine *sm, Client *cl, bool factory);
	~GameMode();

	void handleInput();
	void update(const float dt);
	void draw(const float dt);

protected:
	void onInitialize();
private:
	Client *client = nullptr;
	sf::Vector2u size, spawn;
	sf::Vector2i position;
	bool factoryMode;
	sf::Texture workerLeftTex, workerRightTex, trackTex;
	AnimatedSprite workerLeft, workerRight, track;
	std::vector<AnimatedSprite> tracks;
};
#endif;

