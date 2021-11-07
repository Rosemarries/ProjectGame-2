#pragma once
#include<SFML/Graphics.hpp>
#include"Player.h"

class Bullet {
public:
	int currVelocity;
	Bullet();

	void fire(int speed, int bulletVector);

	int getX();

	int getY();

	sf::Vector2f getPosition() {
		return bullet.getPosition();
	}

	void draw(sf::RenderWindow& window);

	void setPos(sf::Vector2f newPos);

	void Update(sf::Vector2i mousePos, sf::RenderWindow& window, sf::Vector2f player);

	sf::FloatRect getHitbox() const;

	sf::RectangleShape getShape() const {
		return bullet;
	}

	bool isHitted() const;

	void setHitted();

	float getDamage() const;

private:
	sf::RectangleShape bullet;
	sf::Vector2f pos;
	sf::Vector2f size;
	sf::Texture texture;
	float damage;
	float speed;
	bool is_hitted;
};
