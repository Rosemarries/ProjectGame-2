#pragma once
#include<SFML\Graphics.hpp>
#ifndef GAMETILE_H
#define GAMETILE_H


class GameTile
{
public:
	sf::Vector2f pos;
	sf::Texture texture;
	sf::Sprite sprite;

	bool isPassable;
	bool isExit;

	GameTile(std::string, float, float, bool, bool);
	bool setUpSprite(std::string);

};

#endif // !GAMETILE_H
