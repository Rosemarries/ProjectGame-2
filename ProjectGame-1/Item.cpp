#include "Item.h"

Item::Item(sf::Vector2f pos) {

	if (!hitbox_texture[0].loadFromFile("Image/Item-1.png") || !hitbox_texture[1].loadFromFile("Image/Item-2.png") || !hitbox_texture[2].loadFromFile("Image/Item-3.png") || !hitbox_texture[3].loadFromFile("Image/Item-4.png")) {
		abort();
	}

	//hitbox_sprite.setTexture(hitbox_texture[0]);

	hitbox.setSize(sf::Vector2f(50, 50));
	hitbox.setPosition(pos);
	hitbox_sprite.setPosition(pos);
	//hitbox.setFillColor(sf::Color::Cyan);
	//hitbox.setTexture(&hitbox_texture[0]);

	hitbox.setOrigin(hitbox.getLocalBounds().width / 2, hitbox.getLocalBounds().height / 2);
	hitbox_sprite.setOrigin(hitbox.getLocalBounds().width / 2, hitbox.getLocalBounds().height / 2);
	item_poll = 4;
	picked = false;
	randId();
}

sf::RectangleShape Item::getShape() const {
	return hitbox;
}

sf::FloatRect Item::getHitbox() const {
	return hitbox.getGlobalBounds();
}

sf::Sprite Item::getSprite() const {
	return hitbox_sprite;
}

int Item::getId() const {
	return id;
}

void Item::randId() {
	id = rand() % item_poll;
	hitbox.setTexture(&hitbox_texture[id]);
	hitbox_sprite.setTexture(hitbox_texture[id]);
}