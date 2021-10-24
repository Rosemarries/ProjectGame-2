#pragma once
#include<SFML/Graphics.hpp>
#include"Animation.h"

class Player {
public:
	Player(sf::Vector2f size) {
		player.setSize(size);
	}

	void setOrigin() {
		player.setOrigin(40, 40);
	}

	void setPos(sf::Vector2f newPos) {
		player.setPosition(newPos);
	}

	void move(sf::Vector2f dir) {
		player.move(dir);
	}

	int getX() {
		return player.getPosition().x;
	}

	int getY() {
		return player.getPosition().y;
	}

	void draw(sf::RenderWindow& window) {
		window.draw(player);
	}

	void setTexture(sf::Texture* playerTexture) {
		player.setTexture(playerTexture);
	}

	void loadAnime(sf::IntRect uvRect) {
		player.setTextureRect(uvRect);
	}

private:
	sf::RectangleShape player;
};