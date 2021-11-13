#include "Item.h"

Item::Item(sf::Vector2f pos) {

	if (!hitbox_texture.loadFromFile("Image/Item-1.png")) {
		abort();
	}

	hitbox_sprite.setTexture(hitbox_texture);

	hitbox.setSize(sf::Vector2f(40, 50));
	hitbox.setPosition(pos);
	hitbox_sprite.setPosition(pos);
	hitbox.setFillColor(sf::Color::Cyan);

	hitbox.setOrigin(hitbox.getLocalBounds().width / 2, hitbox.getLocalBounds().height / 2);
	hitbox_sprite.setOrigin(hitbox.getLocalBounds().width / 2, hitbox.getLocalBounds().height / 2);
	item_poll = 1;
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
}