#pragma once
#include<SFML\Graphics.hpp>
#include"Animation.h"

enum direction { Up, Down, Left, Right };

class Player {
	Animation animation;

public:
	Player();
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
	int GetHp() {
		return hp;
	}

	sf::Vector2f GetPosition() {
		return body.getPosition();
	}
	sf::FloatRect GetBody() const {
		return body.getGlobalBounds();
	}
	sf::RectangleShape GetShape() const {
		return body;
	}
	sf::FloatRect getHitbox() const {
		return body.getGlobalBounds();
	}

private:
	sf::RectangleShape body;
	sf::Vector2f position;
	sf::Vector2u imageCount = sf::Vector2u(4, 10);
	sf::Texture texture;
	sf::Clock clock;
	unsigned int row;
	float switchTime = 0.3f;
	float speed = 200.0f;
	float damage = 3.0f;
	int hp = 6;
	int face;
};