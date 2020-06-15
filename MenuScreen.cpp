#include <SFML/Graphics.hpp>

#include <memory>
#include <string>

#include "GameScreen.h"
#include "MenuScreen.h"
#include "Game.h"

using namespace sfSnake;
std::string colors[4] = {"White", "Black", "Brown", "NULL"};

MenuScreen::MenuScreen()
{
	font_.loadFromFile("Fonts/game_over.ttf");
	text_.setFont(font_);
	text_.setString(
		"\n\n\n\n\n\n\n\n\nPress [SPACE] to play\n\nPress [ESC] to quit"
		"\n\nPress [J] to switch background color: " + colors[GameScreen::BG_color] +
		"\n\nPress [K] to switch grid color: " + colors[GameScreen::grid_color] +
		"\n\n\n\nFight For A Higher Score!!!"
	);
    //text_.setCharacterSize(24);
	snakeText_.setFont(font_);
	snakeText_.setString("Gluttonous Snake!");
	snakeText_.setFillColor(sf::Color::Green);
	snakeText_.setCharacterSize(64);
	snakeText_.setStyle(sf::Text::Bold);

	sf::FloatRect textBounds = text_.getLocalBounds();
	text_.setOrigin(textBounds.left + textBounds.width / 2,
		textBounds.top + textBounds.height / 2);
	text_.setPosition(Game::Width / 2, Game::Height / 2);

	sf::FloatRect snakeTextBounds = snakeText_.getLocalBounds();
	snakeText_.setOrigin(snakeTextBounds.left + snakeTextBounds.width / 2,
		snakeTextBounds.top + snakeTextBounds.height / 2);
	snakeText_.setPosition(Game::Width / 2, Game::Height / 4);
}

void MenuScreen::handleInput(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		Game::Screen = std::make_shared<GameScreen>();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		window.close();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
		GameScreen::BG_color = (GameScreen::BG_color + 1) % 3;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
		GameScreen::grid_color = (GameScreen::grid_color + 1) % 4;
}

void MenuScreen::update(sf::Time delta)
{
	static bool movingLeft = false;
	static bool movingRight = true;

	if (movingRight)
	{
		snakeText_.rotate(delta.asSeconds());

		if (static_cast<int>(snakeText_.getRotation()) == 10)
		{
			movingRight = false;
			movingLeft = true;
		}
	}

	if (movingLeft)
	{
		snakeText_.rotate(-delta.asSeconds());

		if (static_cast<int>(snakeText_.getRotation()) == (360 - 10))
		{
			movingLeft = false;
			movingRight = true;
		}
	}

	text_.setString(
	"\n\n\n\n\n\n\n\n\nPress [SPACE] to play\n\nPress [ESC] to quit"
	"\n\nPress [J] to switch background color: " + colors[GameScreen::BG_color] +
	"\n\nPress [K] to switch grid color: " + colors[GameScreen::grid_color] +
	"\n\n\n\nFight For A Higher Score!!!"
	);
}

void MenuScreen::render(sf::RenderWindow& window)
{
	window.draw(text_);
	window.draw(snakeText_);
}