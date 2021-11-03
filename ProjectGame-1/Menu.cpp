#include "Menu.h"

Menu::Menu(float width, float height) {
	if (!font.loadFromFile("IsaacScript2.ttf") || !bgMenu.loadFromFile("Image/MenuBg-2.png")) {
		abort();
	}

	bg.setSize(sf::Vector2f(width, height));
	bg.setPosition(0.0f, 0.0f);
	bg.setTexture(&bgMenu);

	int size = 75;
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		menu[i].setFont(font);
		menu[i].setCharacterSize(size);
		menu[i].setPosition(sf::Vector2f(150, height / (MAX_NUMBER_OF_ITEMS + 1) * (i + 1) - 60));
		menu[i].setFillColor(sf::Color::Black);
	}
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("PLAY");
	menu[1].setString("OPTIONS");
	menu[2].setString("SCOREBOARD");
	menu[3].setString("EXIT");

	selectedItemIndex = 0;
}

Menu::~Menu() {

}

void Menu::Draw(sf::RenderWindow& window) {
	window.clear(sf::Color(150, 150, 150));
	window.draw(bg);
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		window.draw(menu[i]);
	}
}

void Menu::MoveUp() {
	if (selectedItemIndex - 1 >= 0) {
		menu[selectedItemIndex].setFillColor(sf::Color::Black);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::MoveDown() {
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {
		menu[selectedItemIndex].setFillColor(sf::Color::Black);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}