#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

enum move { BOTH, HORIZONTAL, VERTICAL };

class Enemy {
protected:
	sf::RectangleShape hitbox;
	sf::Texture hitbox_texture;
	sf::Sprite hitbox_sprite;
	sf::Vector2f position;
	float hp;
	float damage;
	sf::Vector2f movement_speed;
	bool fly;
public:
	virtual int sign(float number);

	virtual sf::RectangleShape getShape() const;
	virtual sf::FloatRect getHitbox() const;
	virtual sf::Sprite getSprite() const;
	virtual float getDamage() const;
	virtual bool isFlying() const;
	virtual float getHp() const;
	virtual void hitted(float dmg);
	virtual void update(sf::Vector2f player_pos, bool reverse = false, move m = BOTH) = 0;
	virtual void setAnime(sf::IntRect uvRect) {
		hitbox.setTextureRect(uvRect);
	}
	virtual sf::FloatRect fakeUpdate(move m, bool reverse) = 0;
	virtual ~Enemy() = 0;
};

#endif
