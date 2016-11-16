#ifndef CLIENT_H
#define CLIENT_H

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

#include "State.h"
#include "Board.h"
#include "Player.h"

class Client : public State
{
public:
	Client(StateMachine* sm);
	~Client();

	void handleInput();
	void update(const float dt);
	void draw(const float dt);

	void connectToServer();

protected:
	void onInitialize();
private:
	sf::IpAddress ip;
	sf::TcpSocket server;
	sf::Packet packet;

	unsigned playerCount;
	std::vector<Player*> players;
};
#endif;