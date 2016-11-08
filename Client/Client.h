#ifndef CLIENT_H
#define CLIENT_H

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

#include "State.h"

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
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Image image;
	sf::Vector2u windowSize;
	sf::Color color;
};
#endif;