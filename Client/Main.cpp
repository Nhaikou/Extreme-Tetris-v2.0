#include "StateMachine.h"
#include "Client.h"

int main()
{
	StateMachine* stateMachine = new StateMachine;

	sf::IpAddress ip = "172.13.16.142";
	sf::TcpSocket server;
	sf::Packet packet;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Image image;
	sf::Vector2u windowSize;
	sf::Color color;

	//ip = sf::IpAddress::getLocalAddress();

	server.connect(ip, 2000);

	std::cout << "Waiting for an answer from server...";
	server.receive(packet);

	std::cout << "Continue";
	server.setBlocking(false);

	while (true)
	{
		while (true)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				packet.clear();
				packet << stateMachine->event.key.code;
				server.send(packet);
			}

			packet.clear();
			server.receive(packet);
			if (packet.getDataSize() == 0)
			{
				break;
			}

			packet >> windowSize.x >> windowSize.y;
			if (windowSize != stateMachine->window.getSize())
			{
				stateMachine->window.setSize(windowSize);
			}
			image.create(windowSize.x, windowSize.y);

			for (int j = 0; j < windowSize.y; ++j)
			{
				for (int i = 0; i < windowSize.x; ++i)
				{
					packet >> color.r >> color.g >> color.b >> color.a;
					image.setPixel(i, j, color);
				}
			}

			texture.loadFromImage(image);
			sprite.setTexture(texture);
			sprite.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));

			stateMachine->window.clear(sf::Color::Black);
			stateMachine->window.draw(sprite);
			stateMachine->window.display();
		}
	}

	/*
	srand(time(NULL));
	StateMachine sm;
	sm.pushState(new Client(&sm));
	sm.gameLoop();
	*/

	return 0;
}