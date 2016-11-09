#ifndef SERVER_H
#define SERVER_H

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Server
{
public:
	Server();
	~Server();

	sf::SocketSelector socketSelector;
	sf::TcpSocket tcpSocket;
	sf::TcpListener tcpListener;
	sf::Packet packet;

	void findPlayers();
	void sendRenderTexture(sf::Vector2f position, sf::Vector2u size);
	int receiveButtonPress(unsigned id);

	std::vector<sf::TcpSocket*> clients;
	bool searchPlayers = true;
	char answer;

	sf::RenderTexture renderTexture;

private:
	sf::Texture texture;
	sf::Image image;
};
#endif;

