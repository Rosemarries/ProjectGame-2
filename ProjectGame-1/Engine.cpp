#include "Engine.h"

Engine::Engine() {
    win.create(sf::VideoMode(win_width, win_height), "GAME START!");
	win.setFramerateLimit(60);

	room_tile_map.resize(11, std::vector < Tile >(15));
	clock_to_delay_between_projectiles.restart();
	scoreboard.LoadScoreboardFromFile();
	current_state = MENU;
}

void Engine::run() {
    stateMachine();
}

void Engine::stateMachine() {
    while (current_state != PERM_END) {
        switch (current_state) {
        case MENU:
            stateMENU();
            break;
        case PLAY:
            statePLAY();
            break;
        case SCOREBOARD:
            stateSCOREBOARD();
            break;
        case TREASURE_ROOM:
            stateTR();
            break;
        case BOSS_ROOM:
            stateBR();
            break;
        case END:
            stateEND();
            break;
        }
    }
}

void Engine::stateMENU() {
    while (current_state == MENU) {
        sf::Event evnt;
        while (win.pollEvent(evnt)) {
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
							current_state = PLAY;
							break;
						}
						case 1: {
							current_state = SCOREBOARD;
							break;
						}
						case 2: {
							current_state = PERM_END;
							break;
						}
						}
						break;
					}
					break;
				}
			}
            if (evnt.type == sf::Event::Closed) {
                scoreboard.SaveScoreboardToFile();
                current_state = PERM_END;
                win.close();
            }
        }
		win.clear();
		menu.Draw(win);
		win.display();
    }
}

void Engine::stateSCOREBOARD() {
	while (current_state == SCOREBOARD) {
		sf::Event evnt;
		while (win.pollEvent(evnt)) {
			switch (evnt.type) {
				case sf::Event::KeyReleased: {
					case sf::Keyboard::Return: {
						current_state = MENU;
					}
				}
			}
		}
		win.clear();
		scoreboard.Draw(win);
		win.display();
	}
}

void Engine::reset() {
	playerTexture.loadFromFile("Image/TheLost-4.png");
	player(&playerTexture, sf::Vector2u(4, 10), 0.3f, 200.0f);

	//projectile_array.clear();
	visited_room_map.clear();

	map.Generate();

	room_map_pos_y = room_map_pos_x = map.GetStartPosition();
	addVisitedRoom();
	map.SetupTileMap(room_map_pos_y, room_map_pos_x);

	player(&playerTexture, sf::Vector2u(4, 10), 0.3f, 200.0f).Reset();
	player(&playerTexture, sf::Vector2u(4, 10), 0.3f, 200.0f).setNewPosition(sf::Vector2f(win_width / 2, win_height / 2));

	new_room = true;
	isWin = false;
	treasure_picked = false;
	boss_defeated = false;
	score = 0;

	clock_to_delay_between_projectiles.restart();
}
