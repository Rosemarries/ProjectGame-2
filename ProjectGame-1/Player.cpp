#include<SFML\Graphics.hpp>
#include"Player.h"
#include"Collider.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) : animation(texture, imageCount, switchTime){
	this->speed = speed;
	row = 0;
	face = 0;

	body.setSize(sf::Vector2f(60.0f, 75.0f));
	body.setPosition(400, 400);
	body.setTexture(texture);
	body.setOrigin(30.0f, 32.5f);
}

Player::~Player() {

}

void Player::Update(float deltaTime) {
	sf::Vector2f movement(0.0f, 0.0f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		movement.x -= speed * deltaTime;
		face = 3;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		movement.x += speed * deltaTime;
		face = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		movement.y -= speed * deltaTime;
		face = 2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		movement.y += speed * deltaTime;
		face = 0;
	}
	row = face;

	animation.Update(row, deltaTime, face);
	body.setTextureRect(animation.uvRect);
	body.move(movement);
}

void Player::Draw(sf::RenderWindow& window) {
	window.draw(body);
}