#pragma once
#include<SFML\Graphics.hpp>
#define MAX_NUMBER_OF_ITEMS 5

class Menu
{
public:
	Menu();
	~Menu();

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

