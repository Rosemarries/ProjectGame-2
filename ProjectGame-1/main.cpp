#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<math.h>
#include<SFML/Graphics.hpp>
#include<vector>
#include"Animation.h"
#include"Bullet.h"
#include"Enemy.h"
#include"Player.h"
#include"PlayerHeart.h"

#define screen_x 720
#define screen_y 720
#define PI 3.14159265

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

	//Define Objects:
	Player player(sf::Vector2f(player_status.width, player_status.height));
	Enemy enemy(sf::Vector2f(player_status.width, player_status.height));
	Bullet newBullet(sf::Vector2f(15, 15));
	Heart heart(sf::Vector2f(20, 20));

	std::vector<Bullet> bulletVec;
	enemy.setPos(sf::Vector2f(500, 50));
	player.setOrigin();
	player.setPos(sf::Vector2f(300, 300));
	roomMap.setPosition(room.startPosX, room.startPosY);

	//Set Texture:
	sf::Texture playerTexture;
	sf::Texture playerBulletTexture;
	sf::Texture roomMapTexture;
	sf::Texture heartTexture[5];
	playerTexture.loadFromFile("TheLost-4.png");
	playerBulletTexture.loadFromFile("CharacterBullet-1.png");
	roomMapTexture.loadFromFile("RoomLevel1-1.png");
	player.setTexture(&playerTexture);
	roomMap.setTexture(&roomMapTexture);
	newBullet.setTexture(&playerBulletTexture);
	for (int i = 0; i < player_heart.hp; i++) {
		heartTexture[i].loadFromFile("PlayerHeart-2.png");
		heart.setTexture(&heartTexture[i], i);
	}

	Animation animation(&playerTexture, sf::Vector2u(4, 10), 0.3f);

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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
			goto xx;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			if (player.getX() - player_status.originX > room.wall + room.startPosX) {
				player.move(sf::Vector2f(-player_status.speed, 0));
			}
			playerPicRow = 3;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			if (player.getX() + player_status.originX < room.width + room.startPosX) {
				player.move(sf::Vector2f(player_status.speed, 0));
			}
			playerPicRow = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
			if (player.getY() > room.wall + room.startPosY) {
				player.move(sf::Vector2f(0, -player_status.speed));
			}
			playerPicRow = 2;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
			if (player.getY() + 2 * player_status.originY < room.height + room.startPosY) {
				player.move(sf::Vector2f(0, player_status.speed));
			}
			playerPicRow = 0;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && bulletShootTime >= player_bullet.bulletTimer) {
			player_bullet.bulletState = true;
			bulletShootTime = 0;
		}
		if (bulletShootTime < player_bullet.bulletTimer) {
			bulletShootTime++;
		}

		//Player Animation:
		animation.Update(playerPicRow, deltaTime);
		player.loadAnime(animation.uvRect);

		window.clear(sf::Color(0, 0, 0));
		window.draw(roomMap);

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

		if (player_bullet.bulletState == true) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			player_bullet.bulletAngle = (float)(180 / PI * atan2(abs(mousePos.y - player.getY()), abs(mousePos.x - player.getX())));
			player_bullet.bulletState = false;
			if (player.getX() <= mousePos.x) {
				if (player_bullet.bulletAngle <= 45) {
					player_bullet.bulletVector = 2;
					playerPicRow = 1;
				}
				else {
					if (player.getY() < mousePos.y) {
						player_bullet.bulletVector = 3;
						playerPicRow = 0;
					}
					else {
						player_bullet.bulletVector = 1;
						playerPicRow = 2;
					}
				}
			}
			else {
				if (player_bullet.bulletAngle <= 45) {
					player_bullet.bulletVector = 4;
					playerPicRow = 3;
				}
				else {
					if (player.getY() < mousePos.y) {
						player_bullet.bulletVector = 3;
						playerPicRow = 0;
					}
					else {
						player_bullet.bulletVector = 1;
						playerPicRow = 2;
					}
				}
			}
			newBullet.setPos(sf::Vector2f(player.getX(), player.getY()));
			newBullet.currVelocity = player_bullet.bulletVector;
			bulletVec.push_back(newBullet);
		}
		for (int i = 0; i < bulletVec.size(); i++) {
			bulletVec[i].draw(window);
			bulletVec[i].fire(player_bullet.bulletSpeed, bulletVec[i].currVelocity);
			enemy.checkColl(bulletVec[i]);
			if (bulletVec[i].getX() <= room.wall + room.startPosX || bulletVec[i].getY() <= room.wall + room.startPosY || bulletVec[i].getX() + player_bullet.bulletOriginX >= room.width - room.wall + room.startPosX || bulletVec[i].getY() + player_bullet.bulletOriginY >= room.height - room.wall + room.startPosY) {
				bulletVec.erase(bulletVec.begin() + i);
			}
		}
		//enemy.draw(window);
		player.draw(window);
        window.display();
    }
xx:

    return 0;
}