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
	//projectile_array.clear();
	visited_room_map.clear();

	map.Generate();

	room_map_pos_y = room_map_pos_x = map.GetStartPosition();
	addVisitedRoom();
	map.SetupTileMap(room_map_pos_y, room_map_pos_x);

	player.Reset();
	player.setNewPosition(sf::Vector2f(win_width / 2, win_height / 2));

	new_room = true;
	isWin = false;
	treasure_picked = false;
	boss_defeated = false;
	score = 0;

	clock_to_delay_between_projectiles.restart();
}

void Engine::statePLAY() {
	win.setTitle("Score : 0");
	std::vector < std::shared_ptr < Enemy >> enemy_array;
	while (current_state == PLAY) {
		if (new_room) {
			prepareRoomTileMap();
			if (checkIsUniqueVisitedRoom(room_map_pos_y, room_map_pos_x)) {
				int i = 0;
				while (i < 2) {
					std::shared_ptr<Gaper> gaper = std::make_shared<Gaper>(sf::Vector2f(100 * i + 100, 100 * i + 100));
					enemy_array.push_back(gaper);
					++i;
				}
			}
			new_room = false;
		}

		sf::Event evnt;
		while (win.pollEvent(evnt)) {
			if (evnt.type == sf::Event::Closed) {
				scoreboard.SaveScoreboardToFile();
				current_state = PERM_END;
				win.close();
			}
		}

		movePlayer();
		playerShoot();

		if (enemy_array.size() == 0) {
			addVisitedRoom();
			unlockDoors();
			movePlayerNextRoom();
		}

		for (int i = 0; i < enemy_array.size(); i++) {
			//Player:
			if (enemy_array[i]->getHitbox().intersects(player.getHitbox())) {
				player.Hitted(enemy_array[i]->getDamage());
			}

			//Bullet:
			for (iter_bullet = bullet_array.begin(); iter_bullet != bullet_array.end(); iter_bullet++) {
				if (enemy_array[i]->getHitbox().intersects(iter_bullet->getHitbox())) {
					iter_bullet->setHitted();
					enemy_array[i]->hitted(iter_bullet->getDamage());
				}
			}

			//CollisWall:
			enemy_array[i]->update(player.GetPosition());
			if (isCollsionWithWall(enemy_array[i]->getHitbox())) {
				while (isCollsionWithWall(enemy_array[i]->getHitbox())) {
					enemy_array[i]->update(player.GetShape().getPosition(), true);
				}

				if (isCollsionWithWall(enemy_array[i]->fakeUpdate(HORIZONTAL, false))) {
					enemy_array[i]->update(player.GetShape().getPosition(), false, VERTICAL);
				}

				if (isCollsionWithWall(enemy_array[i]->fakeUpdate(HORIZONTAL, true))) {
					enemy_array[i]->update(player.GetShape().getPosition(), false, VERTICAL);
				}

				if (isCollsionWithWall(enemy_array[i]->fakeUpdate(VERTICAL, false))) {
					enemy_array[i]->update(player.GetShape().getPosition(), false, HORIZONTAL);
				}

				if (isCollsionWithWall(enemy_array[i]->fakeUpdate(VERTICAL, true))) {
					enemy_array[i]->update(player.GetShape().getPosition(), false, HORIZONTAL);
				}
			}

			//Enemy Dead:
			if (enemy_array[i]->getHp() <= 0) {
				enemy_array.erase(enemy_array.begin() + i);
				score++;
				win.setTitle("Score : " + std::to_string(score));
				--i;
			}
		}

		//Bullet hitted Wall:
		for (iter_bullet = bullet_array.begin(); iter_bullet != bullet_array.end(); iter_bullet++) {
			if (isCollsionWithWall(iter_bullet->getHitbox(), true) or iter_bullet->isHitted() or iter_bullet->getX() <= 0 or iter_bullet->getX() + iter_bullet->getHitbox().width >= win_width or iter_bullet->getY() <= 0 or iter_bullet->getY() + iter_bullet->getHitbox().height >= win_height) {
				bullet_array.erase(iter_bullet);
				--iter_bullet;
			}
		}

		if (player.GetHp() <= 0) {
			isWin = false;
			current_state = END;
		}

		win.clear();
		drawRoom();

		for (iter_bullet = bullet_array.begin(); iter_bullet != bullet_array.end(); iter_bullet++) {
			iter_bullet->Update();
			win.draw(iter_bullet->getShape());
		}

		for (int i = 0; i < enemy_array.size(); i++) {
			win.draw(enemy_array[i]->getSprite());
		}

		win.draw(player.GetShape());
		heart.draw(win,player.GetHp());
		win.display();
	}
}
