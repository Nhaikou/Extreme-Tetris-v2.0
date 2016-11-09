#ifndef SERVER_H
#define SERVER_H

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

enum Networking
{
	SINGLEPLAYER = false,
	MULTIPLAYER = true,
};

class Server
{
public:
	Server(bool multiplayer);
	~Server();

	sf::SocketSelector socketSelector;
	sf::TcpSocket tcpSocket;
	sf::TcpListener tcpListener;
	sf::Packet packet;

	void findPlayers();
	void sendRenderTexture(sf::Vector2f position, sf::Vector2u size);
	int receiveButtonPress(unsigned id);

	std::vector<sf::TcpSocket*> clients;
	sf::RenderTexture renderTexture;
	bool networking;

private:
	sf::Texture texture;
	sf::Image image;
	bool searchPlayers = true;
	char answer;
};
#endif;

