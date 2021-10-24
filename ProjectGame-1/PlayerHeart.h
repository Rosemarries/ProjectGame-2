#pragma once
#include<SFML/Graphics.hpp>

class Heart {
public:
	Heart(sf::Vector2f size) {
		heart.setSize(size);
	}

	void setPos(sf::Vector2f newPos) {
		heart.setPosition(newPos);
	}

	void draw(sf::RenderWindow &window) {
		window.draw(heart);
	}

	void setTexture(sf::Texture* playerTexture) {
		heart.setTexture(playerTexture);
	}

private:
	sf::RectangleShape heart;
};