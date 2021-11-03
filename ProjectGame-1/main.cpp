#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<math.h>
#include<SFML/Graphics.hpp>
#include<vector>
#include"Bullet.h"
#include"Enemy.h"
#include"Player.h"
#include"PlayerHeart.h"
#include"Menu.h"
#include"Scoreboard.h"
#include"Room.h"
#include"Map.h"

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
	char name[10];
	int score;
	int hp = 6;
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

struct room {
	float width = 600;
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
	room room;

	sf::RenderWindow window(sf::VideoMode(screen_x, screen_y), "GAME START!");

	//Set Texture:
	sf::Texture playerTexture;
	sf::Texture playerBulletTexture;
	sf::Texture roomMapTexture;
	playerTexture.loadFromFile("Image/TheLost-4.png");
	playerBulletTexture.loadFromFile("Image/CharacterBullet-1.png");
	roomMapTexture.loadFromFile("Image/RoomLevel1-1.png");

	//Declare:
	Player player(&playerTexture, sf::Vector2u(4, 10), 0.3f, 200.0f);
	Bullet newBullet(sf::Vector2f(15, 15), &playerBulletTexture);
	Menu menu(screen_x, screen_y);
	Scoreboard scoreboard(screen_x, screen_y);
	Room roomMap(&roomMapTexture, sf::Vector2f(room.width, room.height), sf::Vector2f(window.getSize()));
	Heart heart;

	float deltaTime = 0.0f;
	int playerPicRow = 0;
	int bulletShootTime = 0;
	bool menuState = true;
	bool scoreboardState = false;
	bool playerCollis = false;
	sf::Clock clock;
	
	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			if (menuState == true) {
				switch (evnt.type) {
					case sf::Event::KeyReleased: {
						switch (evnt.key.code) {
						case sf::Keyboard::W: {
							menu.MoveUp();
							break;
						}
						case sf::Keyboard::S: {
							menu.MoveDown();
							break;
						}
						case sf::Keyboard::Return:
							switch (menu.GetPressedItem()) {
								case 0: {
									menuState = false;
									break;
								}
								case 1: {
									menuState = false;
									break;
								}
								case 2: {
									menuState = false;
									scoreboardState = true;
									break;
								}
								case 3: {
									menuState = false;
									goto ex;
									break;
									//scoreboard.SaveScoreboardToFile();
								}
							}
							break;
						}
						break;
					}
				}
			}
			else if (scoreboardState == true) {
				switch (evnt.type) {
					case sf::Event::KeyReleased: {
						case sf::Keyboard::Return: {
							menuState = true;
							scoreboardState = false;
							break;
						}
					}
				}
			}

			switch (evnt.type) {
			case sf::Event::Closed:
				window.close();
				break;
			}
		}

		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
			menuState = true;
		}

		window.clear(sf::Color(0, 0, 0));

		if (menuState == true) {
			menu.Draw(window);
		}
		else if (scoreboardState == true) {
			scoreboard.Draw(window);
		}
		else {
			roomMap.Draw(window);
			//Player:
			player.Update(deltaTime);
			playerCollis = true;
			player.Draw(window);
			//Player Bullet:
			newBullet.Update(mousePos, window, sf::Vector2f(player.GetPosition().x, player.GetPosition().y), &playerBulletTexture);
			//Player Heart:
			heart.draw(window, player_status.hp);
		}
		window.display();
	}
ex:

    return 0;
}