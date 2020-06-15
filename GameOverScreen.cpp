#include <SFML/Graphics.hpp>

#include <iostream>
#include <memory>

#include "Game.h"
#include "GameScreen.h"
#include "GameOverScreen.h"

using namespace sfSnake;
static unsigned highest_scores[] = {0, 0, 0};
static bool champion = false;

GameOverScreen::GameOverScreen(std::size_t score) : score_(score)
{
	// recored high score
	int temp = 0;
	if (score > highest_scores[0])
		champion = true;
	else
		champion = false;
	
	for (int i = 2; i >= 0; i--){
		if (highest_scores[i] < score){
			if (i == 2)
				highest_scores[i] = score;
			else{
				temp = highest_scores[i];
				highest_scores[i] = score;
				highest_scores[i+1] = temp;
			}
		}
	}

	font_.loadFromFile("Fonts/game_over.ttf");

	congra_.setFont(font_);
	congra_.setString(
		"Congratulation!!!"
		"\nYou got the HIGHEST score!"
		"\n\n\nHigh Score:\n\n1. " + std::to_string(highest_scores[0]) +
		"\n\n2. " + std::to_string(highest_scores[1]) +
		"\n\n3. " + std::to_string(highest_scores[2]) +
		"\n\n\nYour score: " + std::to_string(score) + "!"
		"\n\n\nPress [SPACE] to retry"
		"\n\nPress [ESC] to quit"
	);
	congra_.setFillColor(sf::Color::Red);

	sf::FloatRect congraBounds = congra_.getLocalBounds();
	congra_.setOrigin(congraBounds.left + congraBounds.width / 2,
		congraBounds.top + congraBounds.height / 2);
	congra_.setPosition(Game::Width / 2, Game::Height / 2);

	text_.setFont(font_);
	text_.setString(
		"High Score:\n\n1. " + std::to_string(highest_scores[0]) +
		"\n\n2. " + std::to_string(highest_scores[1]) +
		"\n\n3. " + std::to_string(highest_scores[2]) +
		"\n\n\nYour score: " + std::to_string(score) + "!"
		"\n\n\nPress [SPACE] to retry"
		"\n\nPress [ESC] to quit");
	text_.setFillColor(sf::Color::Red);

	sf::FloatRect textBounds = text_.getLocalBounds();
	text_.setOrigin(textBounds.left + textBounds.width / 2,
		textBounds.top + textBounds.height / 2);
	text_.setPosition(Game::Width / 2, Game::Height / 2);
}

void GameOverScreen::handleInput(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		Game::Screen = std::make_shared<GameScreen>();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		window.close();
}

void GameOverScreen::update(sf::Time delta)
{

}

void GameOverScreen::render(sf::RenderWindow& window)
{
	if(champion)
		window.draw(congra_); 
	else
		window.draw(text_);	
}