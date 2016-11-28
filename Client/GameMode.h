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

	void createAnimations();
	void createWalls();
	void createNames();
	void createScoreBoard();

protected:
	void onInitialize();
private:
	Client *client = nullptr;
	sf::Vector2u size, spawn;
	sf::Vector2i position;
	bool factoryMode;
	sf::Texture workerLeftTex, workerRightTex, trackTex, wallTex, floorTex, glassTex;
	AnimatedSprite workerLeft, workerRight, track;
	std::vector<AnimatedSprite> tracks;
	std::vector<sf::Sprite> walls;
	sf::Sprite wall, floor, glass;
	sf::Font font;
	sf::Text playerNameText;
	std::vector<sf::Text> playerNameTexts;
	std::vector<sf::Text> scoreBoardTexts;
	sf::RectangleShape scoreBoard;
};
#endif;

