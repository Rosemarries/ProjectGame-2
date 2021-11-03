#pragma once
#include<SFML\Graphics.hpp>
#include<vector>
#include<fstream>
#define MAX_NUMBER_OF_ITEMS 1

#ifndef SCOREBOARD_H
#define SCOREBOARD_H


struct Record {
	std::string name;
	int score;
};

class Scoreboard
{
	std::vector<Record> scoreboard_array;
	static bool compareScore(const Record& sbr1, const Record& sbr2);

public:
	Scoreboard(float width, float height);
	~Scoreboard();

	void Draw(sf::RenderWindow& window);
	void LoadScoreboardFromFile();
	void SaveScoreboardToFile();
	void Reset();
	void Add(const std::string & name, int score);
	int GetLastScore() const;
	std::vector < Record > GetVector() {return scoreboard_array;};

	std::vector < Record >::iterator BEGIN() {return scoreboard_array.begin();};
	std::vector < Record >::iterator END() {return scoreboard_array.end();};

	std::string GetName(int i) const;
	int GetScore(int i) const;
	int GetSize() const;

private:
	sf::Font font;
	sf::Text text;
	sf::Text back;
	sf::Text score_text;
	sf::Text table_name_text;
	sf::Text table_score_text;
	sf::RectangleShape bg;
	sf::Texture texture;
};

#endif // !SCOREBOARD_H