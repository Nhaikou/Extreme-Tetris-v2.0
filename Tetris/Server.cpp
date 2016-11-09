#include "Server.h"


Server::Server()
{
	findPlayers();
}

Server::~Server()
{
	for (int i = 0; i < clients.size(); ++i)
	{
		delete clients[i];
	}
}

void Server::findPlayers()
{
	tcpListener.listen(55001);
	socketSelector.add(tcpListener);

	while (searchPlayers)
	{
		std::cout << "Waiting for players.." << std::endl;
		if (socketSelector.wait() && searchPlayers)
		{
			if (socketSelector.isReady(tcpListener) && searchPlayers)
			{
				sf::TcpSocket* client = new sf::TcpSocket;
				if (tcpListener.accept(*client) == sf::Socket::Done)
				{
					clients.push_back(client);
					clients[clients.size() - 1]->setBlocking(false);
					socketSelector.add(*client);
				}
				else
				{
					delete client;
				}

				std::cout << "Wait for more players? Y/N";
				std::cin >> answer;
				if (answer == 'n')
				{
					for (int i = 0; i < clients.size(); ++i)
					{
						clients[i]->send(packet);
					}
					searchPlayers = false;
				}
			}
		}
	}
}

void Server::sendRenderTexture(sf::Vector2f position, sf::Vector2u size)
{
	packet.clear();
	packet << position.x << position.y;
	packet << size.x << size.y;
	texture = renderTexture.getTexture();
	image = texture.copyToImage();

	for (int j = 0; j < size.y; ++j)
	{
		for (int i = 0; i < size.x; ++i)
		{
			packet << image.getPixel(position.x + i, position.y + j).r << image.getPixel(position.x + i, position.y + j).g << image.getPixel(position.x + i, position.y + j).b << image.getPixel(position.x + i, position.y + j).a;
		}
	}
	for (int i = 0; i < clients.size(); i++)
	{
		clients[i]->send(packet);
	}
}

int Server::receiveButtonPress(unsigned id)
{
	int key;
	clients[id]->receive(packet);
	if (packet.getDataSize() == 0)
	{
		return -1;
	}
	packet >> key;
	return key;
}