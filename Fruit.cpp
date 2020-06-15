#include <SFML/Graphics.hpp>

#include "Fruit.h"

using namespace sfSnake;

const float Fruit::Radius = 8.f;
const sf::Color Fruit_Color[5] = {
	sf::Color::Black, sf::Color(210, 105, 30), sf::Color::Red,
	sf::Color::Blue, sf::Color::Green
};
const int Effect[5] = {0, 0, 1, 2, 3}; // effect of fruits

Fruit::Fruit(sf::Vector2f position, int type)
{
	shape_.setPosition(position);
	shape_.setRadius(Fruit::Radius);
	shape_.setFillColor(Fruit_Color[type]);
	effect = Effect[type];
}

void Fruit::render(sf::RenderWindow& window)
{
	window.draw(shape_);
}

sf::FloatRect Fruit::getBounds() const
{
	return shape_.getGlobalBounds();
}