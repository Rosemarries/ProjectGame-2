#include "Blood.h"

Blood::Blood(sf::Vector2f pos) {
	if (!texture.loadFromFile("Image/Blood-1.png")) {
		abort();
	}
	blood.setSize(sf::Vector2f(70.0f, 70.0f));
	blood.setTexture(&texture);
	blood.setPosition(pos);
	blood.setOrigin(sf::Vector2f(25.0f, 25.0f));

	blood_sprite.setTexture(texture, true);
	blood_sprite.setPosition(pos);
}