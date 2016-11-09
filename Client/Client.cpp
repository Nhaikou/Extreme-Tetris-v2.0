#include "Client.h"


Client::Client(StateMachine* sm)
{
	stateMachine = sm;
}


Client::~Client()
{
}

void Client::onInitialize()
{
	connectToServer();
}

void Client::handleInput()
{
	if (stateMachine->event.type == sf::Event::KeyPressed)
	{
		packet.clear();
		packet << stateMachine->event.key.code;
		server.send(packet);
	}
}

void Client::update(const float dt)
{
	packet.clear();
	server.receive(packet);
	if (packet.getDataSize() == 0)
	{
		return;
	}

	packet >> texturePosition.x >> texturePosition.y;
	packet >> textureSize.x >> textureSize.y;
	image.create(textureSize.x, textureSize.y);

	for (int j = 0; j < textureSize.y; ++j)
	{
		for (int i = 0; i < textureSize.x; ++i)
		{
			packet >> color.r >> color.g >> color.b >> color.a;
			image.setPixel(i, j, color);
		}
	}

	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
	sprite.setPosition(texturePosition);
}

void Client::draw(const float dt)
{
	stateMachine->window.draw(sprite);
}

void Client::connectToServer()
{
	ip = sf::IpAddress::getLocalAddress();

	server.connect(ip, 55001);

	std::cout << "Waiting for an answer from server...";
	server.receive(packet);

	std::cout << "Continue";
	server.setBlocking(false);
}