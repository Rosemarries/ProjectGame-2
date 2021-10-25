#pragma once
#include<SFML/Graphics.hpp>

class Heart {
public:
	Heart(sf::Vector2f size) {
		for (int i = 0; i < 5; i++) {
			heart[i].setSize(size);
		}
	}

	void setPos(sf::Vector2f newPos, int i) {
		heart[i].setPosition(newPos);
	}

	void draw(sf::RenderWindow &window, int n) {
		for (int i = 0; i < n; i++) {
			window.draw(heart[i]);
		}
	}

	void setTexture(sf::Texture* playerHeartTexture, int i) {
		heart[i].setTexture(playerHeartTexture);
	}

private:
	sf::RectangleShape heart[5];
};