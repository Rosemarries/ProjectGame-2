#pragma once
#ifndef GAPER_H
#define GAPER_H

#include "Enemy.h"

class Gaper : public Enemy {
public:
	explicit Gaper(sf::Vector2f pos, sf::Vector2f size = sf::Vector2f(50, 50), float hp = 10.f, float damage = 0.5f, float movement_speed = 2.f);
	void update(sf::Vector2f player_pos, bool reverse = false, move m = BOTH) override;
	sf::FloatRect fakeUpdate(move m, bool reverse) override;
};

#endif


