#pragma once
#include<SFML/Graphics.hpp>

class Bullet {
public:
	int currVelocity;
	Bullet(sf::Vector2f size) 
	{
		bullet.setSize(size);
	}

	void fire(int speed, int bulletVector) {
		if (bulletVector == 1) {
			bullet.move(0, -speed);
		}
		else if (bulletVector == 2) {
			bullet.move(speed, 0);
		}
		else if (bulletVector == 3) {
			bullet.move(0, speed);
		}
		else if (bulletVector == 4) {
			bullet.move(-speed, 0);
		}
	}

	int getX() {
		return bullet.getPosition().x;
	}

	int getY() {
		return bullet.getPosition().y;
	}
	
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

	void draw(sf::RenderWindow& window) {
		window.draw(bullet);
	}

	void setPos(sf::Vector2f newPos) {
		bullet.setPosition(newPos);
	}

	void setTexture(sf::Texture* bulletTexture) {
		bullet.setTexture(bulletTexture);
	}

private:
	sf::RectangleShape bullet;
};
