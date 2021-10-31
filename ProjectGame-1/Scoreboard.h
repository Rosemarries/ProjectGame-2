#pragma once
#include<SFML\Graphics.hpp>
#define MAX_NUMBER_OF_ITEMS 1

class Scoreboard
{
public:
	Scoreboard(float width, float height, sf::Texture* texture);
	~Scoreboard();

	void Draw(sf::RenderWindow& window);
	void Update(char name[10], int score);

private:
	sf::Font font;
	sf::Text scoreboard[5];
	sf::Text text;
	sf::Text back;
	sf::RectangleShape bg;
};

