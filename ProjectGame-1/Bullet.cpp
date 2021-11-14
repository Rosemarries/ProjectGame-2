#include"Bullet.h"

#define PI 3.14159265
//std::vector<Bullet> bulletVec;

Bullet::Bullet() {
	texture.loadFromFile("Image/CharacterBullet-1.png");
	size = sf::Vector2f(15.0f, 15.0f);

	bullet.setSize(size);
	bullet.setTexture(&texture);
	bullet.setOrigin(size/2.0f);

	hitbox.setRadius(10.0f);
	hitbox.setOrigin(hitbox.getLocalBounds().width / 2, hitbox.getLocalBounds().height / 2);
	hitbox.setPosition(sf::Vector2f(0, 0));
	hitbox.setTexture(&texture);

	speed = 0.0f;
	damage = 0.0f;
	is_hitted = false;
}

void Bullet::setPos(sf::Vector2f newPos, float dmg, float mvs, int bulletVec) {
	bullet.setPosition(newPos);
	pos = newPos;
	hitbox.setPosition(pos);
	damage = dmg;
	speed = mvs;
	bulletVector = bulletVec;
	//d = dir;
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
	window.draw(bullet);
}

int Bullet::getX() {
	return bullet.getPosition().x;
}

int Bullet::getY() {
	return bullet.getPosition().y;
}

float Bullet::getDamage() const {
	return damage;
}

bool Bullet::isHitted() const {
	return is_hitted;
}

void Bullet::setHitted() {
	is_hitted = true;
}

void Bullet::Update(/*sf::Vector2i mousePos, sf::RenderWindow& window, sf::Vector2f player*/) {
	/*if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && bulletShootTime >= bulletTimer) {
		bulletState = true;
		//bulletShootTime = 0;
	}
	/*if (bulletShootTime < bulletTimer) {
		bulletShootTime++;
	}*/

	/*if (bulletState == true) {
		Bullet newBullet;
		bulletAngle = (float)(180 / PI * atan2(abs(mousePos.y - player.x), abs(mousePos.x - player.x)));
		bulletState = false;
		if (player.x <= mousePos.x) {
			if (bulletAngle <= 45) {
				bulletVector = 2;
				d = Right;
			}
			else {
				if (player.y < mousePos.y) {
					bulletVector = 3;
					d = Up;
				}
				else {
					bulletVector = 1;
					d = Down;
				}
			}
		}
		else {
			if (bulletAngle <= 45) {
				bulletVector = 4;
				d = Left;
			}
			else {
				if (player.y < mousePos.y) {
					bulletVector = 3;
					d = Up;
				}
				else {
					bulletVector = 1;
					d = Down;
				}
			}
		}
		/*newBullet.setPos(sf::Vector2f(player.x, player.y));
		newBullet.currVelocity = bulletVector;
		bulletVec.push_back(newBullet);*/
	//}
	/*room room;
	for (int i = 0; i < bulletVec.size(); i++) {
		bulletVec[i].draw(window);
		bulletVec[i].fire(bulletSpeed, bulletVec[i].currVelocity);
		if (bulletVec[i].getX() <= room.startPosX || bulletVec[i].getY() <= room.wall + room.startPosY || bulletVec[i].getX() >= 720 - room.startPosX || bulletVec[i].getY() >= room.height - room.wall + room.startPosY) {
			bulletVec.erase(bulletVec.begin() + i);
		}
	}*/

	/*if (d == Up) {
		pos.y -= speed;
	}
	if (d == Down) {
		pos.y += speed;
	}
	if (d == Left) {
		pos.x -= speed;
	}
	if (d == Right) {
		pos.x += speed;
	}
	bullet.setPosition(pos);
	hitbox.setPosition(pos);*/
}

sf::FloatRect Bullet::getHitbox() const {
	return bullet.getGlobalBounds();
}