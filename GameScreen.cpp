#include <SFML/Graphics.hpp>

#include <random>
#include <memory>
#include <string>

#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Game.h"

using namespace sfSnake;
int GameScreen::BG_color = 0; // default: white
int GameScreen::grid_color = 3; // default: NULL
const sf::Color colors[4] = {sf::Color::White, sf::Color::Black,
                        sf::Color(210, 105, 30), sf::Color::Transparent};

GameScreen::GameScreen() : snake_()
{

}

void GameScreen::handleInput(sf::RenderWindow& window)
{
	snake_.handleInput(window);
}

void GameScreen::update(sf::Time delta)
{
	static std::default_random_engine random(time(NULL));
	static std::uniform_int_distribution<int> dis(0, 3);

	if (fruit_.size() < 6)
		for (int i = 0; i <= dis(random); i++)
			generateFruit();

	snake_.update(delta);
	snake_.checkFruitCollisions(fruit_);

	if (snake_.hitSelf())
		Game::Screen = std::make_shared<GameOverScreen>(snake_.getSize());
}

void GameScreen::render(sf::RenderWindow& window)
{
	drawBG(window);
	drawXline(window);
	drawYline(window);
	snake_.render(window);

	for (auto fruit : fruit_)
		fruit.render(window);
}

void GameScreen::drawBG(sf::RenderWindow& window)
{
    auto color = colors[GameScreen::BG_color];
    sf::RectangleShape shape_;
    shape_.setPosition(sf::Vector2f(0, 0));
    shape_.setFillColor(color);
    shape_.setSize(sf::Vector2f(Game::Width, Game::Height));
    window.draw(shape_);
}

void GameScreen::drawXline(sf::RenderWindow& window)
{
    auto color = colors[GameScreen::grid_color];
    for (int i = SnakeNode::Diameter + 2; i < Game::Height; i += SnakeNode::Diameter + 2)
	{
        sf::RectangleShape shape_;
        shape_.setPosition(sf::Vector2f(0, i));
        shape_.setFillColor(color);
        shape_.setSize(sf::Vector2f(Game::Width, 1));
        window.draw(shape_);
    }
}

void GameScreen::drawYline(sf::RenderWindow& window)
{
    auto color = colors[GameScreen::grid_color];
    for (int i = SnakeNode::Diameter + 2; i < Game::Width; i += SnakeNode::Diameter + 2) {
        sf::RectangleShape shape_;
        shape_.setPosition(sf::Vector2f(i, 0));
        shape_.setFillColor(color);
        shape_.setSize(sf::Vector2f(1, Game::Height));
        window.draw(shape_);
    }
}

void GameScreen::generateFruit()
{
	static std::default_random_engine engine(time(NULL));
	static std::uniform_int_distribution<int> xDistribution(0, Game::Width - SnakeNode::Diameter);
	static std::uniform_int_distribution<int> yDistribution(0, Game::Height - SnakeNode::Diameter);
	static std::uniform_int_distribution<int> fruitDis(0, 7);
	int fruit_idx = fruitDis(engine);
	int fruit_type = 0;
	switch(fruit_idx)
	{
		case 0:
			fruit_type = 0;
			break;
		case 1:
			fruit_type = 1;
			break;
		case 2:
		case 3:
			fruit_type = 2;
			break;
		case 4:
		case 5:
			fruit_type = 3;
			break;
		case 6:
		case 7:
			fruit_type = 4;
			break;
	}

	fruit_.push_back(Fruit(sf::Vector2f(xDistribution(engine), yDistribution(engine)), fruit_type));
}

