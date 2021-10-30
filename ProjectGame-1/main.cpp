#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<math.h>
#include<SFML/Graphics.hpp>
#include<vector>
#include"Bullet.h"
#include"Enemy.h"
#include"Player.h"
#include"PlayerHeart.h"
#include"Collision.h"

#define screen_x 720
#define screen_y 720

int score = 0;

struct player_status {
	float speed = 0.75;
	int myArtifact = 0;
	float originX = 40;
	float originY = 40;
	float height = 75;
	float width = 60;
};

struct player_bullet {
	int bulletVector;
	float bulletSpeed = 1.75;
	int bulletTimer = 60;
	bool bulletState = false;
	int bulletDamage = 1;
	float bulletAngle;
	float bulletOriginX = 7.5;
	float bulletOriginY = 7.5;
};

struct player_heart {
	int hp = 5;
	int maxHeart = 5;
	int heartType[5] = { 2, 2, 1, 0, 0 };
	int lastHp = 0;
	int remainHp = 0; //Calculate
};

struct artifact {
	int number = 0;
	int boostCharacterHp = 2;
	int boostCharacterSpeed = 1;
	float boostMonsterDropMoney = 0.5;
	int boostCharacterDamage = 1;
	int reduceMonsterDamage = 1;
	int reduceMonsterHp = 1;
	int boostMonsterDropMed = 1;
};

struct room {
	float width = 500;
	float height = 500;
	float wall = 35;
	int number = 0;
	int type = 0;
	float startPosX = 110;
	float startPosY = 110;
};

int main()
{
	player_status player_status;
	player_bullet player_bullet;
	player_heart player_heart;
	artifact artifact;
	room room;

	sf::RenderWindow window(sf::VideoMode(screen_x, screen_y), "GAME START!");
	sf::RectangleShape roomMap(sf::Vector2f(room.width, room.height));
	sf::CircleShape playerBullet;
	sf::RectangleShape door[4];
	for (int i = 0; i < 4; i++) {
		door[i].setSize(sf::Vector2f(room.wall, room.wall));
	}

	//Define Objects:
	Enemy enemy(sf::Vector2f(player_status.width, player_status.height));
	Heart heart(sf::Vector2f(20, 20));

	//std::vector<Bullet> bulletVec;
	enemy.setPos(sf::Vector2f(500, 50));
	roomMap.setPosition(room.startPosX, room.startPosY);

	//Set Texture:
	sf::Texture playerTexture;
	sf::Texture playerBulletTexture;
	sf::Texture roomMapTexture;
	sf::Texture heartTexture[5];
	playerTexture.loadFromFile("TheLost-4.png");
	playerBulletTexture.loadFromFile("CharacterBullet-1.png");
	roomMapTexture.loadFromFile("RoomLevel1-1.png");
	Player player(&playerTexture, sf::Vector2u(4, 10), 0.3f, 200.0f);
	Bullet newBullet(sf::Vector2f(15, 15), &playerBulletTexture);
	roomMap.setTexture(&roomMapTexture);
	for (int i = 0; i < player_heart.hp; i++) {
		heartTexture[i].loadFromFile("PlayerHeart-2.png");
		heart.setTexture(&heartTexture[i], i);
	}

	float deltaTime = 0.0f;
	int playerPicRow = 0;
	int bulletShootTime = 0;
	sf::Clock clock;
	
    while (window.isOpen())
    {
		deltaTime = clock.restart().asSeconds();
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
			switch (evnt.type) {
			case sf::Event::Closed:
				window.close();
				break;
			}
        }

		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
			goto xx;
		}
		

		window.clear(sf::Color(0, 0, 0));
		window.draw(roomMap);
		//Player Animation:
		player.Update(deltaTime);
		player.Draw(window);
		//Player Bullet:
		newBullet.Update(mousePos);
		newBullet.draw(window);
		//Player Heart:
		if (player_heart.lastHp != player_heart.hp) {
			player_heart.remainHp = player_heart.hp;
			for (int i = 0; i < player_heart.maxHeart; i++) {
				if (player_heart.remainHp > 1) {
					player_heart.heartType[i] = 2;
					player_heart.remainHp -= 2;
				}
				else if (player_heart.remainHp == 1) {
					player_heart.heartType[i] = 1;
					player_heart.remainHp -= 1;
				}
				else if (player_heart.remainHp < 1) {
					player_heart.heartType[i] = 0;
				}
				heart.setPos(sf::Vector2f(10 + 20 * i, 10), i);
				if (player_heart.heartType[i] == 0) {
					heartTexture[i].loadFromFile("PlayerHeart-0.png");
				}
				else if (player_heart.heartType[i] == 1) {
					heartTexture[i].loadFromFile("PlayerHeart-1.png");
				}
				else if (player_heart.heartType[i] == 2) {
					heartTexture[i].loadFromFile("PlayerHeart-2.png");
				}
				heart.setTexture(&heartTexture[i], i);
			}
			player_heart.lastHp = player_heart.hp;
		}
		heart.draw(window, player_heart.maxHeart);

		
        window.display();
    }
xx:

    return 0;
}