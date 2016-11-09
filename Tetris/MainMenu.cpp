#include "MainMenu.h"
#include "Standard.h"
#include "Factory.h"

MainMenu::MainMenu(StateMachine* sm)
{
	stateMachine = sm;
	server = new Server();
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

	text.setString("Main Menu soon...");
	text.setCharacterSize(48);
	text.setColor(sf::Color::White);

	tex.loadFromFile("../Assets/Block.png");
	spr.setTexture(tex);

	sf::Texture tex2;
	sf::RenderTexture renderTexture;
	renderTexture.create(500, 500);
	renderTexture.draw(spr);
	renderTexture.display();
	tex2 = renderTexture.getTexture();
	image = tex2.copyToImage();
}

void MainMenu::handleInput()
{
	sf::Keyboard key;

	// Close program
	if (key.isKeyPressed(key.BackSpace))
	{
		stateMachine->window.close();
	}
	if (key.isKeyPressed(key.Space))
	{
		stateMachine->pushState(new Standard(stateMachine));
	}
	if (key.isKeyPressed(key.F))
	{
		stateMachine->pushState(new Factory(stateMachine, sf::Vector2u(10, 20), server));
	}
}

void MainMenu::update(const float dt)
{
	timer += dt;
	if (timer >= 1000)
	{
		server->sendRenderTexture(text.getPosition(), sf::Vector2u(500, 100));
	}

	for (int i = 0; i < server->clients.size(); ++i)
	{
		clientKey = server->receiveButtonPress(i);
		if (clientKey != -1)
		{
			if (clientKey == sf::Keyboard::Escape)
			{
				stateMachine->window.close();
			}
			if (clientKey == sf::Keyboard::F)
			{
				stateMachine->pushState(new Factory(stateMachine, sf::Vector2u(10, 20), server));
			}
			else
			{
				std::cout << "Client " << i << " pressed button " << clientKey << std::endl;
			}
			clientKey = -1;
		}
	}
}

void MainMenu::draw(const float dt)
{
	stateMachine->window.draw(text);
	stateMachine->window.draw(spr);
	server->renderTexture.create(stateMachine->window.getSize().x, stateMachine->window.getSize().y);
	server->renderTexture.clear(sf::Color::Black);
	server->renderTexture.draw(text);
	server->renderTexture.draw(spr);
	server->renderTexture.display();
}