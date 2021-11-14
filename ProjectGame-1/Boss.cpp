#include "Boss.h"
#include <math.h>

Boss::Boss(sf::Vector2f pos, sf::Vector2f size, float hp, float damage, float movement_speed) {
	if (!hitbox_texture.loadFromFile("Image/Boss1.png")) {
		abort();
	}
	hitbox_sprite.setTexture(hitbox_texture);

	position = pos;
	hitbox.setPosition(position);
	hitbox_sprite.setPosition(position);
	hitbox.setSize(size);
	//hitbox.setFillColor(sf::Color::Green);
	hitbox.setTexture(&hitbox_texture);
	this->hp = hp;
	this->damage = damage;
	this->movement_speed = sf::Vector2f(movement_speed, movement_speed);
	fly = false;
}

void Boss::update(sf::Vector2f player_pos, bool reverse, move m) {
	if (m == HORIZONTAL) {
		movement_speed.x *= (-1);
	}
	else if (m == VERTICAL) {
		movement_speed.y *= (-1);
	}

	if (reverse and m == BOTH) {
		movement_speed.x *= (-1);
		movement_speed.y *= (-1);
	}

	position.x += movement_speed.x;
	position.y += movement_speed.y;
	hitbox_sprite.setPosition(position);
	hitbox.setPosition(position);
}

sf::FloatRect Boss::fakeUpdate(move m, bool reverse) {
	sf::Vector2f r_pos = position;

	if (m == HORIZONTAL) {
		if (!reverse) {
			r_pos.x += movement_speed.x;
		}
		else {
			r_pos.x -= movement_speed.x;
		}
	}
	else {
		if (!reverse) {
			r_pos.y += movement_speed.y;
		}
		else {
			r_pos.y -= movement_speed.y;
		}
	}

	sf::FloatRect r(r_pos, hitbox.getSize());
	return r;
}
