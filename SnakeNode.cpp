#include <SFML/Graphics.hpp>
#include <cmath>

#include "SnakeNode.h"

using namespace sfSnake;

const float SnakeNode::Diameter = 20.f;
sf::Texture headTex;
sf::Texture bodyTex;

SnakeNode::SnakeNode(sf::Vector2f position, sf::Vector2f direction)
: position_(position)
{
	headshape_.setPosition(position_);
	headTex.loadFromFile("Img/head.png");
	headshape_.setTexture(headTex);	
	headshape_.setOrigin(sf::Vector2f(15.f, 10.f));
	bodyshape_.setPosition(position_);
	bodyTex.loadFromFile("Img/body.png");
	bodyshape_.setTexture(bodyTex);
	bodyshape_.setOrigin(sf::Vector2f(10.f, 10.f));
	double x = direction.x;
	double y = direction.y;
	if (fabs(x) < 0.1){
		if (y > 0){
			headshape_.setRotation(180.f);
			bodyshape_.setRotation(180.f);
		}
		// else Rotation == 0 
	}
	else if (fabs(y) < 0.1){
		if (x > 0){
			headshape_.setRotation(90.f);
			bodyshape_.setRotation(90.f);
		}
		else if (x < 0){
			headshape_.setRotation(-90.f);
			bodyshape_.setRotation(-90.f);
		}
	}
	else if (x > 0 && y > 0){
		headshape_.setRotation(180.f - std::atan((x / y)) / 3.14 * 180.f);
		bodyshape_.setRotation(180.f - std::atan((x / y)) / 3.14 * 180.f);
	}
    else if (x > 0 && y < 0){
		headshape_.setRotation(std::atan((-x / y)) / 3.14 * 180.f);
		bodyshape_.setRotation(std::atan((-x / y)) / 3.14 * 180.f);
	}
    else if (x < 0 && y > 0){
		headshape_.setRotation(-180.f + std::atan((-x / y)) / 3.14 * 180.f);
		bodyshape_.setRotation(-180.f + std::atan((-x / y)) / 3.14 * 180.f);
	}
    else if (x < 0 && y < 0){
		headshape_.setRotation(-std::atan((x / y)) / 3.14 * 180.f);
		bodyshape_.setRotation(-std::atan((x / y)) / 3.14 * 180.f);
	}

}

void SnakeNode::setPosition(sf::Vector2f position, bool isHead)
{
	position_ = position;
	if(isHead)
		headshape_.setPosition(position_);
	else
		bodyshape_.setPosition(position_);
}

void SnakeNode::setPosition(float x, float y, bool isHead)
{
	position_.x = x;
	position_.y = y;
	if(isHead)
		headshape_.setPosition(position_);
	else
		bodyshape_.setPosition(position_);
}

sf::FloatRect SnakeNode::getBounds(bool isHead) const
{
	if(isHead)
		return headshape_.getGlobalBounds();
	else 
		return bodyshape_.getGlobalBounds();
}

sf::Vector2f SnakeNode::getPosition() const
{
	return position_;
}

void SnakeNode::render(sf::RenderWindow& window, bool isHead)
{
	if (isHead)
		window.draw(headshape_);
	else
		window.draw(bodyshape_);
	
}