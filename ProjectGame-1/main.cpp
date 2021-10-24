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

struct player_status {
	int hp = 5;
	int heartType[5] = { 2, 2, 1, 0, 0 };
	int lastHp = 0;
	float speed = 1;
	int myArtifact = 0;
	float originX = 40;
	float originY = 40;
	float height = 75;
	float width = 60;
};

struct player_bullet {
	int bulletVector = 0;
	float bulletSpeed = 2;
	bool bulletState = false;
	int bulletDamage = 1;
	float bulletAngle;
	float bulletOriginX = 7.5;
	float bulletOriginY = 7.5;
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

	sf::Texture playerTexture;
	sf::Texture playerBulletTexture;
	sf::Texture roomMapTexture;
	playerTexture.loadFromFile("TheLost-4.png");
	playerBulletTexture.loadFromFile("CharacterBullet-1.png");
	roomMapTexture.loadFromFile("RoomLevel1-1.png");
	player.setTexture(&playerTexture);
	roomMap.setTexture(&roomMapTexture);
	newBullet.setTexture(&playerBulletTexture);
	sf::Texture heartTexture;

	Animation animation(&playerTexture, sf::Vector2u(4, 10), 0.3f);

	float deltaTime = 0.0f;
	int playerPicRow = 0;
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
			if (player.getY() + player_status.originY < room.height + room.startPosY) {
				player.move(sf::Vector2f(0, player_status.speed));
			}
			playerPicRow = 0;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			player_bullet.bulletState = true;
		}

		animation.Update(playerPicRow, deltaTime);
		player.loadAnime(animation.uvRect);
		window.clear(sf::Color(0, 0, 0));
		window.draw(roomMap);
		for (int i = 0; i < player_status.hp; i++) {
			heart.setPos(sf::Vector2f(10 + 20 * i, 10));
			if (player_status.lastHp != player_status.hp) {
				if (player_status.heartType[i] == 0) {
					heartTexture.loadFromFile("PlayerHeart-0.png");
				}
				else if (player_status.heartType[i] == 1) {
					heartTexture.loadFromFile("PlayerHeart-1.png");
				}
				else if (player_status.heartType[i] == 2) {
					heartTexture.loadFromFile("PlayerHeart-2.png");
				}
				heart.setTexture(&heartTexture);
			}
			heart.draw(window);
			player_status.lastHp = player_status.hp;
		}

		if (player_bullet.bulletState == true) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			player_bullet.bulletAngle = (float)(180 / PI * atan2(abs(mousePos.y - player.getY()), abs(mousePos.x - player.getX())));
			newBullet.setPos(sf::Vector2f(player.getX(), player.getY()));
			bulletVec.push_back(newBullet);
			player_bullet.bulletState = false;
			if (player.getX() <= mousePos.x) {
				if (player_bullet.bulletAngle <= 45) {
					player_bullet.bulletVector = 2;
				}
				else {
					if (player.getY() < mousePos.y) {
						player_bullet.bulletVector = 3;
					}
					else {
						player_bullet.bulletVector = 1;
					}
				}
			}
			else {
				if (player_bullet.bulletAngle <= 45) {
					player_bullet.bulletVector = 4;
				}
				else {
					if (player.getY() < mousePos.y) {
						player_bullet.bulletVector = 3;
					}
					else {
						player_bullet.bulletVector = 1;
					}
				}
			}
		}

		for (int i = 0; i < bulletVec.size(); i++) {
			bulletVec[i].draw(window);
			bulletVec[i].fire(player_bullet.bulletSpeed, player_bullet.bulletVector);
			enemy.checkColl(bulletVec[i]);
		}
		enemy.draw(window);
		player.draw(window);
		/*for (int i = 0; i < 5; i++) {
			if (player_bullet.bulletState == 1) {
				playerBullet.move(player_bullet.bulletVectorX, player_bullet.bulletVectorY);
				sf::Vector2f playerBulletPos = playerBullet.getPosition();
				printf("%d : %f , %f\n", i, playerBulletPos.x, playerBulletPos.y); //check bullet's positions
				if (playerBulletPos.x <= room.wall + room.startPosX || playerBulletPos.y <= room.wall + room.startPosY || playerBulletPos.x + player_bullet.bulletOriginX >= room.width - room.wall + room.startPosX || playerBulletPos.y + player_bullet.bulletOriginY >= room.height - room.wall + room.startPosY) {
					player_bullet.bulletState = 0;
				}
				else {
					window.draw(playerBullet);
				}
			}
		}*/
        window.display();
    }
xx:

    return 0;
}