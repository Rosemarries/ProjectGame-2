#define _CRT_SECURE_NO_WARNINGS 1
#include "Scoreboard.h"
#include<iostream>
#include<algorithm>

Scoreboard::Scoreboard() {
	if (!font.loadFromFile("IsaacScript2.ttf")) {
		//handle error
	}
	float width = 1050.0f, height = 720.0f;
	scoreboard_array.resize(5);
	Reset();
	LoadScoreboardFromFile();

	texture.loadFromFile("Image/ScoreboardBg-1.png");
	bg.setSize(sf::Vector2f(width, height));
	bg.setOrigin(sf::Vector2f(width / 2.0f, height / 2.0f));
	bg.setPosition(1050.0f / 2.0f, 720.0f / 2.0f);
	bg.setTexture(&texture);

	int size = 50;
	text.setFont(font);
	text.setCharacterSize(2 * size);
	text.setPosition(sf::Vector2f(300.0f, 100.0f));
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold);
	text.setString("SCOREBOARD");

	back.setFont(font);
	back.setCharacterSize(size);
	back.setPosition(sf::Vector2f(150.0f, 550.0f));
	back.setFillColor(sf::Color::Red);
	back.setString("BACK");

	sf::Text table_name_text;
	table_name_text.setFont(font);
	table_name_text.setCharacterSize(90);
	table_name_text.setString("Name");
	table_name_text.setStyle(sf::Text::Bold);
	table_name_text.setFillColor(sf::Color::Black);
	table_name_text.setPosition(sf::Vector2f(width / 2 - (table_name_text.getLocalBounds().width + 70), 120));

	sf::Text table_score_text;
	table_score_text.setFont(font);
	table_score_text.setCharacterSize(90);
	table_score_text.setString("Score");
	table_score_text.setStyle(sf::Text::Bold);
	table_score_text.setFillColor(sf::Color::Black);
	table_score_text.setPosition(sf::Vector2f(width / 2 + 70, 120));

	score_text.setFont(font);
	score_text.setCharacterSize(70);
	score_text.setFillColor(sf::Color::Black);
}

Scoreboard::~Scoreboard() {

}

void Scoreboard::Draw(sf::RenderWindow& window) {
	window.clear(sf::Color(150, 150, 150));
	window.draw(bg);
	window.draw(text);
	window.draw(back);
	window.draw(table_name_text);
	window.draw(table_score_text);
	int i = 0;
	for (auto it = Scoreboard::BEGIN(); it != Scoreboard::END(); ++it) {
		score_text.setString(it->name);
		score_text.setPosition(250.0f, i * 50 + 225);
		window.draw(score_text);
		score_text.setString(std::to_string(it->score));
		score_text.setPosition(650.0f, i * 50 + 225);
		window.draw(score_text);
		i++;
	}
}

void Scoreboard::Reset() {
	if (scoreboard_array.size() == 5) {
		Record empty;
		empty.name = "-----";
		empty.score = 0;
		for (auto it = scoreboard_array.begin(); it != scoreboard_array.end(); ++it) {
			*it = empty;
		}
	}
}

void Scoreboard::Add(const std::string& name, int score) {
	Record r;
	r.name = name;
	r.score = score;
	scoreboard_array.back() = r;
	std::sort(scoreboard_array.begin(), scoreboard_array.end(), [](const Record& sbr1, const Record& sbr2) {return (sbr1.score > sbr2.score); });
}

void Scoreboard::LoadScoreboardFromFile() {
	std::ifstream file;
	file.open("Text/Top5.txt");
	if (!file.good()) {
		std::cout << "Cannot open file.\n";
		abort();
	}

	scoreboard_array.clear();
	Record sbr;
	std::string line_str = "";
	int line_counter = 0;
	while (std::getline(file, line_str)) {
		switch (line_counter) {
		case 0: {
			sbr.name = line_str;
		}
			  break;
		case 1: {
			sbr.score = std::stoi(line_str);
		}
			  break;
		}

		line_counter++;
		if (line_counter == 2) {
			line_counter = 0;
			scoreboard_array.push_back(sbr);
		}
	}

	file.close();
}

void Scoreboard::SaveScoreboardToFile() {
	std::ofstream file;
	file.open("Text/Top5.txt");
	if (!file.good()) {
		std::cout << "Cannot open file.\n";
		abort();
	}

	for (auto it = scoreboard_array.begin(); it != scoreboard_array.end(); ++it) {
		file << it->name << "\n";
		file << it->score << "\n";
	}

	file.close();
}

int Scoreboard::GetLastScore() const {
	return scoreboard_array[scoreboard_array.size() - 1].score;
}

std::string Scoreboard::GetName(int i) const {
	return scoreboard_array[i].name;
}

int Scoreboard::GetScore(int i) const {
	return scoreboard_array[i].score;
}

int Scoreboard::GetSize() const {
	return scoreboard_array.size();
}
