#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>
#include <cmath>

#include "Snake.h"
#include "Game.h"
#include "Fruit.h"
#include "SnakeNode.h"
#include "GameOverScreen.h"

using namespace sfSnake;

const int Snake::InitialSize = 5;

Snake::Snake() : direction_(sf::Vector2f(0, -1)), hitSelf_(false)
{
	initNodes();

	pickupBuffer_.loadFromFile("Sounds/pickup.wav");
	pickupSound_.setBuffer(pickupBuffer_);
	pickupSound_.setVolume(30);

	dieBuffer_.loadFromFile("Sounds/die.wav");
	dieSound_.setBuffer(dieBuffer_);
	dieSound_.setVolume(50);
}

void Snake::initNodes()
{
	for (int i = 0; i < Snake::InitialSize; ++i)
	{
		nodes_.push_back(SnakeNode(sf::Vector2f(
			Game::Width / 2 - SnakeNode::Diameter / 2, 
			Game::Height / 2 - (SnakeNode::Diameter / 2) + (SnakeNode::Diameter * i)),
			sf::Vector2f(0.f, -1.f)));
	}
}

void Snake::handleInput(sf::RenderWindow& window)
{
	auto new_direction = direction_;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		new_direction = sf::Vector2f(0, -1);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		new_direction = sf::Vector2f(0, 1);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		new_direction = sf::Vector2f(-1, 0);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		new_direction = sf::Vector2f(1, 0);
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		double dx = sf::Mouse::getPosition(window).x - nodes_[0].getPosition().x;
		double dy = sf::Mouse::getPosition(window).y - nodes_[0].getPosition().y;
		auto length = hypotf(dx, dy);
		if (length != 0){
			dx /= length;
			dy /= length;
			new_direction = sf::Vector2f(dx, dy);
		}
	}
	auto dir_change = new_direction - direction_;
	if (hypotf(dir_change.x, dir_change.y) < 1.8) // exclude sharp turn
		direction_ = new_direction;
}

void Snake::update(sf::Time delta)
{
	move();
	checkEdgeCollisions();
	checkSelfCollisions();
}

void Snake::checkFruitCollisions(std::vector<Fruit>& fruits)
{
	decltype(fruits.begin()) toRemove = fruits.end();

	for (auto it = fruits.begin(); it != fruits.end(); ++it)
	{
		if (it->getBounds().intersects(nodes_[0].getBounds(true)))
			toRemove = it;
	}

	if (toRemove != fruits.end())
	{
		pickupSound_.play();
		new_body += toRemove->effect;
		fruits.erase(toRemove);
	}
}

void Snake::grow()
{
	if (new_body >= 0)
		new_body--;
	else
		nodes_.pop_back();
}

unsigned Snake::getSize() const
{
	return nodes_.size();
}

bool Snake::hitSelf() const
{
	return hitSelf_;
}

void Snake::checkSelfCollisions()
{
	SnakeNode& headNode = nodes_[0];

	for (decltype(nodes_.size()) i = 1; i < nodes_.size(); ++i)
	{
		if (isIntersect(headNode.getPosition(), nodes_[i].getPosition()))
		{
			dieSound_.play();
			sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
			hitSelf_ = true;
			break;
		}
	}
}

bool Snake::isIntersect(const sf::Vector2f& head, const sf::Vector2f& body)
{
	auto dis_vec = head - body;
	auto dis = hypotf(dis_vec.x, dis_vec.y);
	return dis < SnakeNode::Diameter/1.5;
}

void Snake::checkEdgeCollisions()
{
	SnakeNode& headNode = nodes_[0];

	if (headNode.getPosition().x <= 0)
		headNode.setPosition(Game::Width, headNode.getPosition().y, true);
	else if (headNode.getPosition().x >= Game::Width)
		headNode.setPosition(0, headNode.getPosition().y, true);
	else if (headNode.getPosition().y <= 0)
		headNode.setPosition(headNode.getPosition().x, Game::Height, true);
	else if (headNode.getPosition().y >= Game::Height)
		headNode.setPosition(headNode.getPosition().x, 0, true);
}

void Snake::move()
{	
	// put the last node to front
    nodes_.insert(nodes_.begin(), SnakeNode(
        sf::Vector2f(nodes_[0].getPosition().x + direction_.x * SnakeNode::Diameter,
                     nodes_[0].getPosition().y + direction_.y * SnakeNode::Diameter),
        direction_));
	grow();
}

void Snake::render(sf::RenderWindow& window)
{
    for (long long unsigned int i = 0; i < nodes_.size(); ++i)
        nodes_[i].render(window, !i);
}