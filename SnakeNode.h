#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
class SnakeNode
{
public:
	SnakeNode(sf::Vector2f position = sf::Vector2f(0, 0), 
		sf::Vector2f direction = sf::Vector2f(0, 0));

	void setPosition(sf::Vector2f position, bool isHead);
	void setPosition(float x, float y, bool isHead);

	void render(sf::RenderWindow& window, bool isHead);

	sf::Vector2f getPosition() const;
	sf::FloatRect getBounds(bool isHead) const;

	static const float Diameter;

private:
	sf::Sprite headshape_;
	sf::Sprite bodyshape_;
	sf::Vector2f position_;
};
}

#endif