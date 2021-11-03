#pragma once
#include<SFML/Graphics.hpp>
#include"Player.h"

class Bullet {
public:
	int currVelocity;
	Bullet(sf::Vector2f size, sf::Texture* texture);

	void fire(int speed, int bulletVector);

	int getX();

	int getY();

	void draw(sf::RenderWindow& window);

	void setPos(sf::Vector2f newPos);

	void Update(sf::Vector2i mousePos, sf::RenderWindow& window, sf::Vector2f player, sf::Texture* texture);

	bool isHitted() const;

	void setHitted();

	float getDamage() const;

private:
	sf::RectangleShape bullet;
	sf::Vector2f pos;
	float damage;
	float speed;
	bool is_hitted;
};
