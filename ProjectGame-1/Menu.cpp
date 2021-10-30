#include "Menu.h"

Menu::Menu(float width, float height) {
	if (!font.loadFromFile("IsaacScript2.ttf")) {
		//handle error
	}

	int size = 75;
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		menu[i].setFont(font);
		menu[i].setCharacterSize(size);
		menu[i].setPosition(sf::Vector2f(size, height / (MAX_NUMBER_OF_ITEMS + 1) * (i + 1)));
		menu[i].setFillColor(sf::Color::White);
	}
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("PLAY");
	menu[1].setString("OBTIONS");
	menu[2].setString("SCOREBOARD");
	menu[3].setString("EXIT");

	selectedItemIndex = 0;
}

Menu::~Menu() {

}

void Menu::Draw(sf::RenderWindow& window) {
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		window.draw(menu[i]);
	}
}

void Menu::MoveUp() {
	if (selectedItemIndex - 1 >= 0) {
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::MoveDown() {
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}