#include <iostream>
#include <math.h>
#include "Gaper.h"


Gaper::Gaper(sf::Vector2f pos, sf::Vector2f size, float hp, float damage, float movement_speed) {

	if (!hitbox_texture.loadFromFile("textures/enemy_gaper.png")) {
		abort();
	}

	hitbox_sprite.setTexture(hitbox_texture);

	position = pos;
	hitbox.setPosition(position);
	hitbox_sprite.setPosition(position);
	hitbox.setSize(size);
	hitbox.setFillColor(sf::Color::Green);
	this->hp = hp;
	this->damage = damage;
	this->movement_speed = sf::Vector2f(movement_speed, movement_speed);
	fly = false;
}

void Gaper::update(sf::Vector2f player_pos, bool reverse, move m) {
	sf::Vector2f new_position;
	new_position.x = player_pos.x - position.x;
	new_position.y = player_pos.y - position.y;

	float new_position_length = sqrt(new_position.x * new_position.x + new_position.y * new_position.y);
	if (new_position_length > movement_speed.x) {
		new_position.x /= new_position_length;
		new_position.y /= new_position_length;

		if (!reverse) {
			new_position.x *= movement_speed.x;
			new_position.y *= movement_speed.y;
		}
		else {
			new_position.x *= movement_speed.x * (-1);
			new_position.y *= movement_speed.y * (-1);
		}
	}

	if (m == BOTH) {
		position.x += new_position.x;
		position.y += new_position.y;
	}
	else if (m == HORIZONTAL) {
		float correct_speed = fmin(movement_speed.x, abs(player_pos.x - position.x));
		position.x += sign(new_position.x) * correct_speed;
	}
	else if (m == VERTICAL) {
		float correct_speed = fmin(movement_speed.y, abs(player_pos.y - position.y));
		position.y += sign(new_position.y) * correct_speed;
	}
	hitbox_sprite.setPosition(position);
	hitbox.setPosition(position);
}

sf::FloatRect Gaper::fakeUpdate(move m, bool reverse) {
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
