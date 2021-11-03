#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>

#include "Map.h"
#include "Menu.h"
#include "Player.h"
#include "Bullet.h"
//#include "Item.h"
#include "PlayerHeart.h"
#include "Scoreboard.h"
#include "Enemy.h"
//#include "Gaper.h"
#include "Boss.h"

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

	sf::RenderWindow win;
	sf::Font font;
	sf::Clock clock_to_delay_between_projectiles;

	std::vector <sf::Texture> room_texture;

	Map map;
	Menu menu;
	sf::Texture playerTexture;
	Player player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
	Bullet bullet(sf::Vector2f size, sf::Texture* texture);
	Heart heart;
	Scoreboard scoreboard;

	//std::vector < Projectile > projectile_array;
	//std::vector < Projectile > ::iterator iter_proj;

	int win_width = 720;
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

	void stateMachine();
	void stateMENU();
	void statePLAY();
	void stateSCOREBOARD();
	void stateTR(); 	// TR - treasure room
	void stateBR(); 	// BR - boss room
	void stateEND();

	void reset();

	bool checkIsUniqueVisitedRoom(int row, int col) const;
	void addVisitedRoom();

	void movePlayer();
	bool movePlayerNextRoom();
	void unlockDoors();

	void prepareRoomTileMap();
	void drawRoom();
	void playerShoot();

	bool isCollsionWithWall(sf::FloatRect objectPos, bool isProjectile = false) const;

	enum states { MENU, PLAY, TREASURE_ROOM, BOSS_ROOM, SCOREBOARD, END, PERM_END };
	states current_state;
public:
	Engine();
	void run();
};

#endif

