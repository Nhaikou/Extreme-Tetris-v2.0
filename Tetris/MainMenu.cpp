#include "MainMenu.h"
#include "Standard.h"
#include "Factory.h"

MainMenu::MainMenu(StateMachine* sm)
{
	stateMachine = sm;
}

MainMenu::~MainMenu()
{

}

void MainMenu::onInitialize()
{
	if (!font.loadFromFile("../Assets/8bitOperatorPlus8-Bold.ttf"))
	{
		std::cout << "Error loading font" << std::endl;
	}
	
	text.setFont(font);

	tex.loadFromFile("../Assets/Block.png");
	spr.setTexture(tex);

}

void MainMenu::handleInput()
{
	sf::Keyboard key;

	if (clientKey != 0)
	{
		std::cout << "Hauskaa! Se toimii!" << std::endl;
	}

	// Close program
	if (key.isKeyPressed(key.BackSpace))
	{
		stateMachine->window.close();
	}
	if (key.isKeyPressed(key.Space))
	{
		stateMachine->pushState(new Standard(stateMachine));
	}
	if (key.isKeyPressed(key.Return))
	{
		//stateMachine->pushState(new Factory(stateMachine, sf::Vector2u(10, 20), network));
	}
	if (key.isKeyPressed(key.N))
	{
		//network = new Network;
		//stateMachine->pushState(new Factory(stateMachine, sf::Vector2u(10, 20), network));
	}

	text.setString("Main Menu soon...");
	text.setCharacterSize(48);
	text.setColor(sf::Color::White);
}

void MainMenu::update(const float dt)
{
	timer += dt;
	if (timer >= 1000)
	{
		server.packet << stateMachine->window.getSize().x << stateMachine->window.getSize().y;
		image = stateMachine->window.capture();

		for (int j = 0; j < image.getSize().y; ++j)
		{
			for (int i = 0; i < image.getSize().x; ++i)
			{
				server.packet << image.getPixel(i, j).r << image.getPixel(i, j).g << image.getPixel(i, j).b << image.getPixel(i, j).a;
			}
		}
		server.clients[0]->send(server.packet);
	}

	server.clients[0]->receive(server.packet);
	if (server.packet.getDataSize() == 0)
	{
		return;
	}
	server.packet >> clientKey;
}

void MainMenu::draw(const float dt)
{
	stateMachine->window.draw(text);
	stateMachine->window.draw(spr);
}