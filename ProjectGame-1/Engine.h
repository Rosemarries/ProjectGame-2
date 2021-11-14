#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>

#include "Map.h"
#include "Menu.h"
#include "Player.h"
#include "Bullet.h"
#include "Item.h"
#include "PlayerHeart.h"
#include "Scoreboard.h"
#include "Enemy.h"
#include "Gaper.h"
#include "Boss.h"
#include "Pause.h"
#include "Animation.h"
#define PI 3.14159265

struct Room {
	int row;
	int col;
};

struct Tile {
	sf::RectangleShape shape;
	sf::Sprite shape_sprite;
	bool is_wall;
	bool can_go_through;
	bool can_shoot_through;
	bool is_door;
};

class Engine {
	Animation playerAnimation;
	Animation bossAnimation;

	sf::RenderWindow win;
	sf::Font font;
	sf::Clock clock_to_delay_between_bullet;
	sf::Clock clock;

	std::vector <sf::Texture> room_texture;

	Map map;
	Menu menu;
	Pause pause;
	sf::Texture playerTexture;
	sf::Texture bossTexture;
	Player player;
	Bullet bullet;
	Heart heart;
	Scoreboard scoreboard;

	std::vector < Bullet > bullet_array;
	std::vector < Bullet > ::iterator iter_bullet;

	int win_width = 1050;
	int win_height = 720;

	std::vector <std::vector<Tile>> room_tile_map;
	std::vector <Room> visited_room_map;

	int room_map_pos_y;
	int room_map_pos_x;
	int score;
	bool new_room;
	bool isWin;
	bool treasure_picked;
	bool boss_defeated;
	float deltaTime = 0.0f;

	float fireSpeed = 0.5f;
	int randomHeart;

	void stateMachine();
	void stateMENU();
	void statePLAY();
	void stateSCOREBOARD();
	void stateTR(); 	// TR - treasure room
	void stateBR(); 	// BR - boss room
	void stateEND();
	void statePAUSE();

	void reset();

	bool checkIsUniqueVisitedRoom(int row, int col) const;
	void addVisitedRoom();

	void movePlayer(float deltaTime);
	bool movePlayerNextRoom();
	void unlockDoors();

	void prepareRoomTileMap();
	void drawRoom();
	void playerShoot();

	bool isCollsionWithWall(sf::FloatRect objectPos, bool isBullet = false) const;

	enum states { MENU, PLAY, TREASURE_ROOM, BOSS_ROOM, SCOREBOARD, END, PERM_END, PAUSE };
	states current_state;
	states roomNow;
public:
	Engine(sf::Texture* playerTexture, sf::Texture* bossTexture);
	void run();
};

#endif