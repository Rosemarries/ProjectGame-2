#include "Room.h"

Room::Room(sf::Texture* texture, sf::Vector2f size, sf::Vector2f windowScale) {
	room.setPosition(windowScale / 2.0f);
	room.setOrigin(size / 2.0f);
	room.setTexture(texture);
	room.setSize(size);
}

Room::~Room() {

}

void Room::Draw(sf::RenderWindow& window) {
	window.draw(room);
}

sf::FloatRect Room::GetGlobalRounds() {
	return room.getGlobalBounds();
}