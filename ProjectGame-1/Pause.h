#pragma once

#include<SFML/Graphics.hpp>
#define MAX_NUMBER_OF_ITEMS 2

class Pause
{
public:
	Pause();
	void Draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() {
		return selectedItemIndex;
	}

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
	sf::RectangleShape bg;
	sf::Texture bgMenu;
};

