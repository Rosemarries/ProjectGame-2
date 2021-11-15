#include"Player.h"
//#include"Room.h"

struct room {
	float width = 600;
	float height = 500;
	float wall = 35;
	float originX = width / 2;
	float originY = height / 2;
	int number = 0;
	int type = 0;
	float startPosX = 110;
	float startPosY = 110;
};

Player::Player(){
	speed = 3.0f;
	damage = 2.0f;
	hp = 6;
	this->speed = speed;
	row = 0;
	face = 0;
	texture.loadFromFile("Image/TheLost-4.png");

	body.setSize(sf::Vector2f(60.0f, 75.0f));
	body.setPosition(400.0f, 400.0f);
	body.setTexture(&texture);
	body.setOrigin(30.0f, 32.5f);
	clock.restart();
}

Player::~Player() {

}

void Player::Update(float deltaTime, float speedX) {
	speed = speedX;
	//Animation animation(&texture,imageCount,switchTime);
	sf::Vector2f movement(0.0f, 0.0f);
	room room;
	room.startPosX = 110;
	room.startPosY = 110;
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
		hp -= dmg;
		clock.restart();
	}
}

void Player::Upgrade(int item_id) {
	switch (item_id) {
	case 0:
		hp += 2;
		break;

	case 1:
		damage += 1.5f;
		break;

	case 2:
		fireTime = 0.2f;
		break;

	case 3:
		fireSpeed += 3.0f;
		break;
	}
}

void Player::Reset() {
	body.setPosition(200, 200);
	speed = 3.f;
	damage = 3.5f;
	hp = 6.f;

	clock.restart();
}
