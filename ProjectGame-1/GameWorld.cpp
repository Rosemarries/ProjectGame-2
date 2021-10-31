#include "GameWorld.h"

GameWorld::GameWorld() {
	gridLength = 8;
	setUpInitialState();
}

void GameWorld::setUpInitialState() {
	exitPos = sf::Vector2i(1, 0);
	playerPos = sf::Vector2i(gridLength - 1, gridLength - 1);
	setUpEnemyPos();
	setUpTiles();
}

void GameWorld::setUpEnemyPos() {
	enemyPos.clear();
	enemyPos.push_back(sf::Vector2i(0, 2));
	enemyPos.push_back(sf::Vector2i(6, 0));
	enemyPos.push_back(sf::Vector2i(2, 7));
}

void GameWorld::setUpTiles() {
	tiles.clear();
	std::vector<GameTile*> firstRow;
	firstRow.push_back(new GameTile("image/RoomWallLevel1-1.png", 0, 0, false, false));
	firstRow.push_back(new GameTile("image/Door-1.png", 50, 0, true, true));
}