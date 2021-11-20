#pragma once
#include <SFML\Graphics.hpp>

class Blood
{
public:
	Blood(sf::Vector2f pos);
	void SetPos(sf::Vector2f pos) {
		blood.setPosition(pos);
	}
	sf::RectangleShape GetShape() const {
		return blood;
	}
	void Draw(sf::RenderWindow& win) {
		win.draw(blood);
	}

private:
	sf::RectangleShape blood;
	sf::Sprite blood_sprite;
	sf::Texture texture;
};