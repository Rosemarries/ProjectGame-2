#include"Bullet.h"
#include"Player.h"
#include<SFML/Graphics.hpp>

#define PI 3.14159265
int bulletShootTime = 0;
int bulletTimer = 60;
float bulletSpeed = 1.75;
float bulletAngle;
bool bulletState = false;
int bulletCurrVelocity;
std::vector<Bullet> bulletVec;

struct room {
	float width = 500;
	float height = 500;
	float wall = 35;
	int number = 0;
	int type = 0;
	float startPosX = 110;
	float startPosY = 110;
};

Bullet::Bullet(sf::Vector2f size, sf::Texture* texture) {
	bullet.setSize(size);
	bullet.setTexture(texture);
	bullet.setOrigin(7.5f, 7.5f);
}

int Bullet::getX() {
	return bullet.getPosition().x;
}

int Bullet::getY() {
	return bullet.getPosition().y;
}

void Bullet::setPos(sf::Vector2f newPos) {
	bullet.setPosition(newPos);
}

void Bullet::fire(int speed, int bulletVector) {
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

void Bullet::draw(sf::RenderWindow& window) {
	room room;
	for (int i = 0; i < bulletVec.size(); i++) {
		bulletVec[i].draw(window);
		bulletVec[i].fire(bulletSpeed, bulletVec[i].currVelocity);
		if (bulletVec[i].getX() <= room.wall + room.startPosX || bulletVec[i].getY() <= room.wall + room.startPosY || bulletVec[i].getX() + bullet.getOrigin().x >= room.width - room.wall + room.startPosX || bulletVec[i].getY() + bullet.getOrigin().y >= room.height - room.wall + room.startPosY) {
			bulletVec.erase(bulletVec.begin() + i);
		}
	}
}

void Bullet::Update(sf::Vector2i mousePos) {
	int bulletVector;
	sf::Texture playerTexture;
	Player player(&playerTexture, sf::Vector2u(4, 10), 0.3f, 200.0f);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && bulletShootTime >= bulletTimer) {
		bulletState = true;
		bulletShootTime = 0;
	}
	if (bulletShootTime < bulletTimer) {
		bulletShootTime++;
	}

	if (bulletState == true) {
		sf::Texture playerBulletTexture;
		Bullet newBullet(sf::Vector2f(15, 15), &playerBulletTexture);
		bulletAngle = (float)(180 / PI * atan2(abs(mousePos.y - player.getY()), abs(mousePos.x - player.getX())));
		bulletState = false;
		if (player.getX() <= mousePos.x) {
			if (bulletAngle <= 45) {
				bulletVector = 2;
			}
			else {
				if (player.getY() < mousePos.y) {
					bulletVector = 3;
				}
				else {
					bulletVector = 1;
				}
			}
		}
		else {
			if (bulletAngle <= 45) {
				bulletVector = 4;
			}
			else {
				if (player.getY() < mousePos.y) {
					bulletVector = 3;
				}
				else {
					bulletVector = 1;
				}
			}
		}
		newBullet.setPos(sf::Vector2f(player.getX(), player.getY()));
		newBullet.currVelocity = bulletVector;
		bulletVec.push_back(newBullet);
	}
}