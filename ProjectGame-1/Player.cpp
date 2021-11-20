#include"Player.h"

Player::Player(){
	speed = 3.0f;
	damage = 2.0f;
	hp = 10;
	this->speed = speed;
	row = 0;
	face = 0;
	texture.loadFromFile("Image/TheLost-4.png");

	if (!soundHeartPickBuffer.loadFromFile("Sound/bloodbank touched.wav")) {
		abort();
	}
	soundHeartPick.setBuffer(soundHeartPickBuffer);

	body.setSize(sf::Vector2f(60.0f, 75.0f));
	body.setPosition(400.0f, 400.0f);
	body.setTexture(&texture);
	body.setOrigin(30.0f, 37.5f);
	clock.restart();
}

Player::~Player() {

}

void Player::Update(float deltaTime, float speedX) {
	speed = speedX;
	//Animation animation(&texture,imageCount,switchTime);
	sf::Vector2f movement(0.0f, 0.0f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		if(body.getPosition().x > 0.0f)
			movement.x -= speed;// *deltaTime;
		face = 3;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		if(body.getPosition().x < 1050.0f)
			movement.x += speed;// *deltaTime;
		face = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		if(body.getPosition().y > 0.0f)
			movement.y -= speed;// *deltaTime;
		face = 2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		if(body.getPosition().y < 720.0f)
			movement.y += speed;// *deltaTime;
		face = 0;
	}
	row = face;

	//Animation animation(&texture, imageCount, switchTime);
	//animation.Update(row, deltaTime);
	//body.setTextureRect(animation.uvRect);
	body.move(movement);
}

void Player::Draw(sf::RenderWindow& window) {
	window.draw(body);
}

void Player::Hitted(float dmg) {
	if (clock.getElapsedTime() >= sf::seconds(0.5f)) {
		body.setFillColor(sf::Color::Red);
		hp -= dmg;
		clock.restart();
	}
	else {
		body.setFillColor(sf::Color::White);
	}
}

void Player::Upgrade(int item_id) {
	soundHeartPick.play();
	switch (item_id) {
	case 0:
		hp += 2;
		if (hp > 10) { hp = 10; }
		break;

	case 1:
		damage += 1.5f;
		break;

	case 2:
		fireTime -= 0.1f;
		if (fireTime < 0.1f) { fireTime = 0.1f; }
		break;

	case 3:
		fireSpeed += 3.0f;
		break;
	}
}

void Player::Reset() {
	body.setPosition(200, 200);
	speed = 3.f;
	damage = 2.0f;
	fireSpeed = 3.0f;
	fireTime = 0.5f;
	hp = 10;

	clock.restart();
}