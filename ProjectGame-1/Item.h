#pragma once
#ifndef ITEM_H
#define ITEM_H

#include <SFML/Graphics.hpp>

class Item {
	sf::RectangleShape hitbox;
	sf::Texture hitbox_texture;
	sf::Sprite hitbox_sprite;
	int id;
	int item_poll;

public:
	explicit Item(sf::Vector2f pos = sf::Vector2f(0, 0));
	sf::RectangleShape getShape() const;
	sf::FloatRect getHitbox() const;
	sf::Sprite getSprite() const;
	int getId() const;
	void randId();
};

#endif