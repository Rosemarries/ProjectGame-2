#pragma once
#include<SFML/Graphics.hpp>

class Bullet {
public:
	int currVelocity;
	Bullet(sf::Vector2f size, sf::Texture* texture);

	void fire(int speed, int bulletVector);

	int getX();

	int getY();
	
	int getRight() {
		return bullet.getPosition().x + bullet.getSize().x;
	}

	int getLeft() {
		return bullet.getPosition().x;
	}

	int getTop() {
		return bullet.getPosition().y;
	}

	int getBottom() {
		return bullet.getPosition().y + bullet.getSize().y;
	}

	void draw(sf::RenderWindow& window);

	void setPos(sf::Vector2f newPos);

	void Update(sf::Vector2i mousePos, sf::RenderWindow& window, sf::Vector2f player, sf::Texture* texture);

private:
	sf::RectangleShape bullet;
};
