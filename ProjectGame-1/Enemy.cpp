#include "enemy.h"

sf::RectangleShape Enemy::getShape() const {
	return hitbox;
}

sf::FloatRect Enemy::getHitbox() const {
	return hitbox.getGlobalBounds();
}

sf::Sprite Enemy::getSprite() const {
	return hitbox_sprite;
}

float Enemy::getDamage() const {
	return damage;
}

bool Enemy::isFlying() const {
	return fly;
}

float Enemy::getHp() const {
	return hp;
}

void Enemy::hitted(float dmg) {
	hp -= dmg;
}

int Enemy::sign(float number) {
	if (number == 0)
		return 0;
	else if (number > 0)
		return 1;
	else // (number < 0)
		return -1;
}

Enemy::~Enemy() {

}
