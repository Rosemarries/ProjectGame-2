#pragma once
#include<SFML\Graphics.hpp>
#include"GameTile.h"
#include<vector>

#ifndef GAMEWORLD_H
#define GAMEWORLD_H

class GameWorld
{
	sf::Vector2i exitPos;
	sf::Vector2i playerPos;
	std::vector<sf::Vector2i> enemyPos;
	void setUpInitialState();
	void setUpEnemyPos();
	void setUpTiles();

public:
	std::vector<std::vector<GameTile*>>tiles;
	int gridLength;
	GameWorld();
};

#endif // !GAMEWORLD_H