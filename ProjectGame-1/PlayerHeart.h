#pragma once
#include<SFML/Graphics.hpp>

class Heart {
public:
	Heart();

	void draw(sf::RenderWindow& window, int hp);

private:
	sf::RectangleShape heart[5];
	sf::Texture texture[3];
	sf::Vector2f size;
	int maxHeart = 5;
	int remainHp;
};