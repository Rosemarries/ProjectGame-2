#pragma once
#ifndef BOSS_H
#define BOSS_H

#include "Enemy.h"
#include "Animation.h"

class Boss : public Enemy {
public:
	explicit Boss(sf::Vector2f pos, sf::Vector2f size = sf::Vector2f(160, 120), float hp = 70.f, float damage = 1.f, float movement_speed = 3.f);
	void update(sf::Vector2f player_pos, bool reverse = false, move m = BOTH) override;
	void setAnime(sf::IntRect uvRect) {
		hitbox.setTextureRect(uvRect);
	}
	sf::FloatRect fakeUpdate(move m, bool reverse) override;
};

#endif