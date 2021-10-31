#define _CRT_SECURE_NO_WARNINGS 1
#include "Scoreboard.h"
#include<string.h>

struct top5 {
	char name[10];
	int score = 0;
};

Scoreboard::Scoreboard(float width, float height, sf::Texture* texture) {
	if (!font.loadFromFile("IsaacScript2.ttf")) {
		//handle error
	}

	bg.setSize(sf::Vector2f(width, height));
	bg.setPosition(0.0f, 0.0f);
	bg.setTexture(texture);

	int size = 50;
	text.setFont(font);
	text.setCharacterSize(2 * size);
	text.setPosition(sf::Vector2f(160.0f, 50.0f));
	text.setFillColor(sf::Color::Black);
	text.setString("SCOREBOARD");

	back.setFont(font);
	back.setCharacterSize(size);
	back.setPosition(sf::Vector2f(150.0f, 500.0f));
	back.setFillColor(sf::Color::Red);
	back.setString("BACK");
}

Scoreboard::~Scoreboard() {

}

void Scoreboard::Update(char name[10], int score) {
	top5 top[5];
	top5 temp;
	FILE* fpw = fopen("Text/Top5.txt", "w");
	if (fpw == (FILE*)NULL) printf("Cannot open file\n");
	else {
		int i = 0;
		for (int i = 0; i < 5; i++) {
			fprintf(fpw, "%s %d\n", "Aa", 10 + i);
		}
		FILE* fpr = fopen("Text/Top5.txt", "r");
		while (!feof(fpr)) {
			fscanf(fpr, "%s", top[i].name);
			fscanf(fpr, "%d", &top[i].score);
			printf("%s %d\n", top[i].name, top[i].score);
			i++;
		}
		fclose(fpr);
	}
	fclose(fpw);
}

void Scoreboard::Draw(sf::RenderWindow& window) {
	window.clear(sf::Color(150, 150, 150));
	window.draw(bg);
	window.draw(text);
	window.draw(back);
	for (int i = 0; i < 5; i++) {
		window.draw(scoreboard[i]);
	}
}