#include"PlayerHeart.h"
Heart::Heart() {
	size = sf::Vector2f(30.0f, 30.0f);
	if (!texture[0].loadFromFile("Image/PlayerHeart-0.png") || !texture[1].loadFromFile("Image/PlayerHeart-1.png") || !texture[2].loadFromFile("Image/PlayerHeart-2.png")) {
		abort();
	}
	for (int i = 0; i < maxHeart; i++) {
		heart[i].setPosition(sf::Vector2f(10 + 30 * i, 10));
		heart[i].setSize(size);
	}
}

void Heart::draw(sf::RenderWindow& window, int hp) {
	remainHp = hp;
	for (int i = 0; i < maxHeart; i++) {
		if (remainHp > 1) {
			remainHp -= 2;
			heart[i].setTexture(&texture[2]);
		}
		else if (remainHp == 1) {
			remainHp -= 1;
			heart[i].setTexture(&texture[1]);
		}
		else if (remainHp < 1) {
			heart[i].setTexture(&texture[0]);
		}
		window.draw(heart[i]);
	}
}