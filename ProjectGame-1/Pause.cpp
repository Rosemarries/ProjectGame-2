#include "Pause.h"
Pause::Pause() {
	if (!font.loadFromFile("IsaacScript2.ttf") || !bgMenu.loadFromFile("Image/MenuBg-1.png")) {
		abort();
	}

	float width = 720.0f, height = 720.0f;
	bg.setSize(sf::Vector2f(width, height));
	bg.setOrigin(sf::Vector2f(width / 2.0f, height / 2.0f));
	bg.setPosition(1050.0f / 2.0f, 720.0f / 2.0f);
	bg.setTexture(&bgMenu);

	int size = 75;
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		menu[i].setFont(font);
		menu[i].setCharacterSize(size);
		menu[i].setPosition(sf::Vector2f(320.0f, height / (MAX_NUMBER_OF_ITEMS + 1) * (i + 1) - 60));
		menu[i].setFillColor(sf::Color::Black);
	}
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("PLAY");
	menu[1].setString("MAIN MENU");

	selectedItemIndex = 0;
}

void Pause::Draw(sf::RenderWindow& window) {
	window.clear();
	window.draw(bg);
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		window.draw(menu[i]);
	}
}

void Pause::MoveUp() {
	if (selectedItemIndex - 1 >= 0) {
		menu[selectedItemIndex].setFillColor(sf::Color::Black);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Pause::MoveDown() {
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {
		menu[selectedItemIndex].setFillColor(sf::Color::Black);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}