#pragma once
#include<SFML\Graphics.hpp>
#include"Animation.h"

class Player {
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
	~Player();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void Hitted(float dmg);
	void Upgrade(int item_id);
	void setNewPosition(sf::Vector2f pos) {
		position = pos;
		body.setPosition(position);
	}
	void Reset();

	sf::Vector2f GetPosition() {
		return body.getPosition();
	}
	sf::FloatRect GetBody() const {
		return body.getGlobalBounds();
	}
	sf::RectangleShape GetShape() const {
		return body;
	}

private:
	sf::RectangleShape body;
	sf::Vector2f position;
	sf::Clock clock;
	Animation animation;
	unsigned int row;
	float speed;
	float damage;
	float hp;
	int face;
};