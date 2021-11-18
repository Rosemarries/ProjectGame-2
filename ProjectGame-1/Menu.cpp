#include "Menu.h"

Menu::Menu() {
	if (!font.loadFromFile("IsaacScript2.ttf") || !bgMenu.loadFromFile("Image/MenuBg-3.png")) {
		abort();
	}

	float width = 1050.0f, height = 720.0f;
	bg.setSize(sf::Vector2f(width, height));
	bg.setOrigin(sf::Vector2f(width / 2.0f, height / 2.0f));
	bg.setPosition(1050.0f / 2.0f, 720.0f / 2.0f);
	bg.setTexture(&bgMenu);

	int size = 75;
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		menu[i].setFont(font);
		menu[i].setCharacterSize(size);
		menu[i].setPosition(sf::Vector2f(320.0f + 20 * i, height / (MAX_NUMBER_OF_ITEMS + 1) * (i + 1) - 50));
		menu[i].setFillColor(sf::Color::Black);
		menu[i].setRotation(-5.0);
	}
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("PLAY");
	menu[1].setString("SCOREBOARD");
	menu[2].setString("CREDIT");
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