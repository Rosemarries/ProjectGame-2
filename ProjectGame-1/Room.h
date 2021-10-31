#pragma once
#include<SFML\Graphics.hpp>

class Room
{
public:
	Room(sf::Texture* texture, sf::Vector2f size, sf::Vector2f windowScale);
	~Room();

	void Draw(sf::RenderWindow& window);
	sf::FloatRect GetGlobalRounds();

private:
	sf::RectangleShape room;
	sf::RectangleShape wall;

};

