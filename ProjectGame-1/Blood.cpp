#include "Blood.h"

Blood::Blood(sf::Vector2f pos) {
	if (!texture.loadFromFile("Image/Blood-1.png")) {
		abort();
	}
	blood.setSize(sf::Vector2f(50.0f, 50.0f));
	blood.setTexture(&texture);
	blood.setPosition(pos);
}