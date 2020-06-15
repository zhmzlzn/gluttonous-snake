#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "Snake.h"
#include "Fruit.h"

namespace sfSnake
{
class GameScreen : public Screen
{
public:
	GameScreen();

	void handleInput(sf::RenderWindow& window) override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;

	void drawBG(sf::RenderWindow& window);
	void drawXline(sf::RenderWindow& window);
	void drawYline(sf::RenderWindow& window);

	void generateFruit();

private:
	Snake snake_;
	std::vector<Fruit> fruit_;

public:
	static int BG_color;
	static int grid_color;
};
}

#endif