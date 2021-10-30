#pragma once
#include<SFML\Graphics.hpp>
#include"Animation.h"

class Player {
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
	~Player();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	int getX() {
		return body.getPosition().x;
	}
	int getY() {
		return body.getPosition().y;
	}

private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
	float speed;
	int face;
};