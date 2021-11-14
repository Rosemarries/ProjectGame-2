#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
#include"Player.h"

class Bullet {
public:
	Bullet();

	void fire(int speed, int bulletVector);
	int getX();
	int getY();
	sf::Vector2f getPosition() {
		return bullet.getPosition();
	}
	void draw(sf::RenderWindow& window);
	void setPos(sf::Vector2f newPos, float dmg, float mvs, int bulletVector);
	void Update(/*sf::Vector2i mousePos, sf::RenderWindow& window, sf::Vector2f player*/);
	sf::FloatRect getHitbox() const;
	sf::RectangleShape getShape() const {
		return bullet;
	}
	bool isHitted() const;
	void setHitted();
	void setBulletVector(int x) {
		bulletVector = x;
	}
	int getbulletVector() {
		return bulletVector;
	}
	float getDamage() const;

private:
	sf::RectangleShape bullet;
	sf::CircleShape hitbox;
	sf::Vector2f pos;
	sf::Vector2f size;
	sf::Texture texture;

	direction d;

	float damage;
	float speed;
	bool is_hitted;
	//int bulletShootTime = 0;
	//int bulletTimer = 60;
	//float bulletSpeed = 1.75;
	float bulletAngle;
	int bulletVector;
	bool bulletState = false;
	int bulletCurrVelocity;
};
