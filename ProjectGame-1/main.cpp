#define _CRT_SECURE_NO_WARNINGS 1
#include"Engine.h"

#define screen_x 720
#define screen_y 720

int score = 0;

int main(int argc,char const*argv[])
{
	srand(time(0));
	sf::Texture playerTexture;
	sf::Texture bossTexture;
	playerTexture.loadFromFile("Image/TheLost-4.png");
	bossTexture.loadFromFile("Image/Boss2.png");
	Engine game(&playerTexture, &bossTexture);
	game.run();
	return 0;

	/*player_status player_status;
	player_bullet player_bullet;
	room room;

	sf::RenderWindow window(sf::VideoMode(screen_x, screen_y), "GAME START!");

	//Set Texture:
	sf::Texture roomMapTexture;
	roomMapTexture.loadFromFile("Image/RoomLevel1-1.png");

	//Declare:
	Player player;
	Bullet newBullet;
	Menu menu;
	Scoreboard scoreboard;
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
			newBullet.Update(mousePos, window, sf::Vector2f(player.GetPosition().x, player.GetPosition().y));
			//Player Heart:
			heart.draw(window, player_status.hp);
		}
		window.display();
	}
ex:

    return 0;*/
}