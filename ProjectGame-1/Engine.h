#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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
	static const float VIEW_WIDTH;
	static const float VIEW_HEIGHT;

	Animation playerAnimation;
	Animation bossAnimation;

	sf::RenderWindow win;
	sf::View view;
	sf::Font font;
	sf::Clock clock_to_delay_between_bullet;
	sf::Clock clock;
	sf::Texture doorTexture;

	//Sound:
	sf::SoundBuffer soundBgBuffer;
	sf::SoundBuffer soundEffectBuffer;
	sf::SoundBuffer soundChangePageBuffer;
	sf::SoundBuffer soundBulletBuffer;
	sf::SoundBuffer soundBulletHittedBuffer;
	sf::SoundBuffer soundPlayerHurtBuffer;
	sf::SoundBuffer soundUnlockDoorBuffer;
	sf::SoundBuffer soundTRBuffer;
	sf::SoundBuffer soundBossDiedBuffer;
	sf::SoundBuffer soundItemSpawnBuffer;
	sf::SoundBuffer soundPLAYBuffer;
	sf::SoundBuffer soundBOSSBuffer;
	sf::Sound soundBOSS;
	sf::Sound soundPLAY;
	sf::Sound soundBg;
	sf::Sound soundEffect;
	sf::Sound soundChangePage;
	sf::Sound soundBullet;
	sf::Sound soundBulletHitted;
	sf::Sound soundPlayerHurt;
	sf::Sound soundUnlockDoor;
	sf::Sound soundTR;
	sf::Sound soundBossDied;
	sf::Sound soundItemSpawn;

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

	float win_width = 1050;
	float win_height = 720;

	std::vector <std::vector<Tile>> room_tile_map;
	std::vector <Room> visited_room_map;

	int room_map_pos_y;
	int room_map_pos_x;
	int score;
	int level = 1;
	int la = 1;
	bool new_room;
	bool isWin;
	bool treasure_picked;
	bool treasure_picked_play;
	bool boss_defeated[3];
	float deltaTime = 0.0f;

	int randomHeart;

	//isaac:
	int isaachp;
	float isaacfireSpeed;
	float isaacfireTime;
	float isaacdamage;
	int isaacscore;

	void stateMachine();
	void stateMENU();
	void statePLAY();
	void stateSCOREBOARD();
	void stateTR(); 	// TR - treasure room
	void stateBR(); 	// BR - boss room
	void stateEND();
	void statePAUSE();
	void stateCREDIT();
	void stateGAME_START();

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
	void ResizeView(sf::RenderWindow& window, sf::View& view, float width, float height);

	enum states { MENU, PLAY, TREASURE_ROOM, BOSS_ROOM, SCOREBOARD, END, PERM_END, PAUSE, CREDIT, GAME_START };
	states current_state;
	states roomNow;
public:
	Engine(sf::Texture* playerTexture, sf::Texture* bossTexture);
	void run();
};

#endif