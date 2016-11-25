#include "Player.h"


Player::Player(sf::Vector2u size, sf::Vector2u spawn, unsigned clientNumber, bool factory)
{
	if (factory)
	{
		board = new Board(size, sf::Vector2i(64 + clientNumber * (size.x + 1) * 16 + 16, 0), spawn);
	}
	else
	{
		board = new Board(size, sf::Vector2i(clientNumber * (size.x + 1) * 16 + 16, 0), spawn);
	}

	emptyTex.create(16, 16);
	nextBlockSprites.resize(nextBlockSize.x);
	for (int i = 0; i < nextBlockSprites.size(); ++i)
	{
		nextBlockSprites[i].resize(nextBlockSize.y);
	}

	for (int j = 0; j < nextBlockSize.y; ++j)
	{
		for (int i = 0; i < nextBlockSize.x; ++i)
		{
			nextBlockSprites[i][j].setTexture(emptyTex);
			nextBlockSprites[i][j].setPosition(board->getPosition().x + (board->getSize().x - 4) * 16 + i * 16, j * 16);
		}
	}

	playerInfoBox.setPosition(sf::Vector2f(board->getPosition()) + sf::Vector2f(2, 2));
	playerInfoBox.setSize(sf::Vector2f(board->getSize().x * 16 - 4, 32 - 4));
	playerInfoBox.setFillColor(sf::Color(185, 122, 87, 255));
	playerInfoBox.setOutlineThickness(2);
	playerInfoBox.setOutlineColor(sf::Color::Black);

	font.loadFromFile("../Assets/8bitOperatorPlus8-Regular.ttf");
	scoreText.setFont(font);
	scoreText.setCharacterSize(24);
	scoreText.setPosition(board->getPosition().x + 16, 0);
	scoreText.setColor(sf::Color::Black);
}

Player::~Player()
{
}

void Player::updateScoreText()
{
	ss.str("");
	ss << score;
	scoreText.setString(ss.str());
}

void Player::updateNextBlock(unsigned blockType)
{
	for (int j = 0; j < nextBlockSize.y; ++j)
	{
		for (int i = 0; i < nextBlockSize.x; ++i)
		{
			nextBlockSprites[i][j].setTexture(emptyTex);
		}
	}

	if (blockType == BlockType::BLOCKI)
	{
		for (int i = 0; i < 4; ++i)
		{
			nextBlockSprites[i][0].setTexture(board->blockTex);
			nextBlockSprites[i][0].setColor(sf::Color::Cyan);
		}
	}
	else if (blockType == BlockType::BLOCKO)
	{
		nextBlockSprites[1][0].setTexture(board->blockTex);
		nextBlockSprites[1][0].setColor(sf::Color::Yellow);
		nextBlockSprites[1][1].setTexture(board->blockTex);
		nextBlockSprites[1][1].setColor(sf::Color::Yellow);
		nextBlockSprites[2][1].setTexture(board->blockTex);
		nextBlockSprites[2][1].setColor(sf::Color::Yellow);
		nextBlockSprites[2][0].setTexture(board->blockTex);
		nextBlockSprites[2][0].setColor(sf::Color::Yellow);
	}
	else if (blockType == BlockType::BLOCKZ)
	{
		nextBlockSprites[1][0].setTexture(board->blockTex);
		nextBlockSprites[1][0].setColor(sf::Color::Red);
		nextBlockSprites[2][0].setTexture(board->blockTex);
		nextBlockSprites[2][0].setColor(sf::Color::Red);
		nextBlockSprites[2][1].setTexture(board->blockTex);
		nextBlockSprites[2][1].setColor(sf::Color::Red);
		nextBlockSprites[3][1].setTexture(board->blockTex);
		nextBlockSprites[3][1].setColor(sf::Color::Red);
	}
	else if (blockType == BlockType::BLOCKS)
	{
		nextBlockSprites[1][1].setTexture(board->blockTex);
		nextBlockSprites[1][1].setColor(sf::Color::Green);
		nextBlockSprites[2][1].setTexture(board->blockTex);
		nextBlockSprites[2][1].setColor(sf::Color::Green);
		nextBlockSprites[2][0].setTexture(board->blockTex);
		nextBlockSprites[2][0].setColor(sf::Color::Green);
		nextBlockSprites[3][0].setTexture(board->blockTex);
		nextBlockSprites[3][0].setColor(sf::Color::Green);
	}
	else if (blockType == BlockType::BLOCKL)
	{
		nextBlockSprites[1][0].setTexture(board->blockTex);
		nextBlockSprites[1][0].setColor(sf::Color(255, 130, 0));
		nextBlockSprites[2][0].setTexture(board->blockTex);
		nextBlockSprites[2][0].setColor(sf::Color(255, 130, 0));
		nextBlockSprites[3][0].setTexture(board->blockTex);
		nextBlockSprites[3][0].setColor(sf::Color(255, 130, 0));
		nextBlockSprites[3][1].setTexture(board->blockTex);
		nextBlockSprites[3][1].setColor(sf::Color(255, 130, 0));
	}
	else if (blockType == BlockType::BLOCKJ)
	{
		nextBlockSprites[1][1].setTexture(board->blockTex);
		nextBlockSprites[1][1].setColor(sf::Color::Blue);
		nextBlockSprites[1][0].setTexture(board->blockTex);
		nextBlockSprites[1][0].setColor(sf::Color::Blue);
		nextBlockSprites[2][0].setTexture(board->blockTex);
		nextBlockSprites[2][0].setColor(sf::Color::Blue);
		nextBlockSprites[3][0].setTexture(board->blockTex);
		nextBlockSprites[3][0].setColor(sf::Color::Blue);
	}
	else if (blockType == BlockType::BLOCKT)
	{
		nextBlockSprites[1][0].setTexture(board->blockTex);
		nextBlockSprites[1][0].setColor(sf::Color::Magenta);
		nextBlockSprites[2][0].setTexture(board->blockTex);
		nextBlockSprites[2][0].setColor(sf::Color::Magenta);
		nextBlockSprites[3][0].setTexture(board->blockTex);
		nextBlockSprites[3][0].setColor(sf::Color::Magenta);
		nextBlockSprites[2][1].setTexture(board->blockTex);
		nextBlockSprites[2][1].setColor(sf::Color::Magenta);
	}
}