#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<math.h>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include"Animation.h"

#define screen_x 720
#define screen_y 720
#define PI 3.14159265

struct player_status {
	int hp = 5;
	int myArtifact = 0;
	float vectorX = 0;
	float vectorY = 0;
	int lookside = 2;
	float originX = 40;
	float originY = 50.5;
	float height = 75;
	float width = 60;
};

struct player_bullet {
	float bulletVectorX;
	float bulletVectorY;
	float bulletSpeed = 2;
	int bulletState = 0;
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
	player_bullet player_bullet[5];
	artifact artifact;
	room room;

	sf::RenderWindow window(sf::VideoMode(screen_x, screen_y), "GAME START!");
	sf::RectangleShape player(sf::Vector2f(player_status.width, player_status.height));
	sf::RectangleShape roomMap(sf::Vector2f(room.width, room.height));
	sf::CircleShape playerBullet[5];

	player.setOrigin(player_status.originX, player_status.originY);
	player.setPosition(200.0f, 200.0f);
	roomMap.setPosition(room.startPosX, room.startPosY);

	sf::Texture playerTexture;
	sf::Texture playerBulletTexture;
	sf::Texture roomMapTexture;
	playerTexture.loadFromFile("TheLost-4.png");
	playerBulletTexture.loadFromFile("CharacterBullet-1.png");
	roomMapTexture.loadFromFile("RoomLevel1-1.png");
	player.setTexture(&playerTexture);
	roomMap.setTexture(&roomMapTexture);
	for (int i = 0; i < 5; i++) {
		playerBullet[i].setRadius(15.0f);
		playerBullet[i].setTexture(&playerBulletTexture);
		playerBullet[i].setOrigin(player_bullet->bulletOriginX, player_bullet->bulletOriginY);
	}

	Animation animation(&playerTexture, sf::Vector2u(4, 10), 0.3f);

	float deltaTime = 0.0f;
	int playerPicRow = 0;
	sf::Clock clock;
	sf::Clock bulletTime;
	
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

		sf::Vector2f playerPos = player.getPosition();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
			goto xx;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			if (playerPos.x - player_status.originX > room.wall + room.startPosX) {
				player.move(-0.75f, 0.0f);
			}
			playerPicRow = 3;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			if (playerPos.x + player_status.originX < room.width + room.startPosX) {
				player.move(0.75f, 0.0f);
			}
			playerPicRow = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
			if (playerPos.y > room.wall + room.startPosY) {
				player.move(0.0f, -0.75f);
			}
			playerPicRow = 2;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
			if (playerPos.y + player_status.originY < room.height + room.startPosY) {
				player.move(0.0f, 0.75f);
			}
			playerPicRow = 0;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			for (int i = 0; i < 5; i++) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				if (player_bullet[i].bulletState == 0) {
					player_bullet[i].bulletState = 1;
					player_bullet[i].bulletAngle = (float)180 / PI * atan2(abs(mousePos.y - playerPos.y), abs(mousePos.x - playerPos.x));
					playerBullet[i].setPosition(playerPos);
					if (playerPos.x <= mousePos.x) {
						if (player_bullet[i].bulletAngle <= 45) {
							player_bullet[i].bulletVectorX = player_bullet[i].bulletSpeed;
							player_bullet[i].bulletVectorY = 0;
						}
						else {
							if (playerPos.y < mousePos.y) {
								player_bullet[i].bulletVectorX = 0;
								player_bullet[i].bulletVectorY = player_bullet[i].bulletSpeed;
							}
							else {
								player_bullet[i].bulletVectorX = 0;
								player_bullet[i].bulletVectorY = (-1) * player_bullet[i].bulletSpeed;
							}
						}
					}
					else {
						if (player_bullet[i].bulletAngle <= 45) {
							player_bullet[i].bulletVectorX = (-1) * player_bullet[i].bulletSpeed;
							player_bullet[i].bulletVectorY = 0;
						}
						else {
							if (playerPos.y < mousePos.y) {
								player_bullet[i].bulletVectorX = 0;
								player_bullet[i].bulletVectorY = player_bullet[i].bulletSpeed;
							}
							else {
								player_bullet[i].bulletVectorX = 0;
								player_bullet[i].bulletVectorY = (-1) * player_bullet[i].bulletSpeed;
							}
						}
					}
					break;
				}
			}
		}

		animation.Update(playerPicRow, deltaTime);
		player.setTextureRect(animation.uvRect);
		window.clear(sf::Color(0, 0, 0));
		window.draw(roomMap);
		window.draw(player);
		for (int i = 0; i < 5; i++) {
			if (player_bullet[i].bulletState == 1) {
				playerBullet[i].move(player_bullet[i].bulletVectorX, player_bullet[i].bulletVectorY);
				sf::Vector2f playerBulletPos = playerBullet[i].getPosition();
				if (playerBulletPos.x <= room.wall + room.startPosX || playerBulletPos.y <= room.wall + room.startPosY || playerBulletPos.x + player_bullet->bulletOriginX >= room.width - room.wall + room.startPosX || playerBulletPos.y + player_bullet->bulletOriginY >= room.height - room.wall + room.startPosY) {
					player_bullet[i].bulletState = 0;
				}
				else {
					window.draw(playerBullet[i]);
				}
			}
		}
        window.display();
    }
xx:

    return 0;
}