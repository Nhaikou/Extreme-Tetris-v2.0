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
	packet << stateMachine->event.key.code;
	server.send(packet);
}

void Client::update(const float dt)
{
	server.receive(packet);
	if (packet.getDataSize() == 0)
	{
		return;
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
}

void Client::draw(const float dt)
{
	stateMachine->window.draw(sprite);
}

void Client::connectToServer()
{
	ip = sf::IpAddress::getLocalAddress();

	server.connect(ip, 2000);

	std::cout << "Waiting for an answer from server...";
	server.receive(packet);

	std::cout << "Continue";
	//server.setBlocking(false);
}