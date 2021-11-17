#include "Engine.h"

Engine::Engine(sf::Texture* playerTexture, sf::Texture* bossTexture) : playerAnimation(playerTexture,sf::Vector2u(4,10),0.3f), bossAnimation(bossTexture, sf::Vector2u(1,9), 0.3f) {
    win.create(sf::VideoMode(win_width, win_height), "GAME START!");
	view.setSize(sf::Vector2f(win_width, win_height));
	win.setFramerateLimit(60);
	font.loadFromFile("IsaacScript2.ttf");
	room_tile_map.resize(11, std::vector < Tile >(15));

	if (!soundPlayerHurtBuffer.loadFromFile("Sound/Isaac_Hurt_Grunt1.wav") || !soundBulletBuffer.loadFromFile("Sound/plop.wav") || !soundUnlockDoorBuffer.loadFromFile("Sound/Unlock00.wav") || !soundTRBuffer.loadFromFile("Sound/weapon room.wav") || !soundChangePageBuffer.loadFromFile("Sound/Book Page Turn 12.wav") || !soundBulletHittedBuffer.loadFromFile("Sound/animal_squish1.wav") || !soundBossDiedBuffer.loadFromFile("Sound/boss1_explosions1.wav") || !soundItemSpawnBuffer.loadFromFile("Sound/bloodbank spawn1.wav")) {
		abort();
	}
	soundPlayerHurt.setBuffer(soundPlayerHurtBuffer);
	soundBullet.setBuffer(soundBulletBuffer);
	soundUnlockDoor.setBuffer(soundUnlockDoorBuffer);
	soundTR.setBuffer(soundTRBuffer);
	soundChangePage.setBuffer(soundChangePageBuffer);
	soundBulletHitted.setBuffer(soundBulletHittedBuffer);
	soundBossDied.setBuffer(soundBossDiedBuffer);
	soundItemSpawn.setBuffer(soundItemSpawnBuffer);

	sf::Texture tmp_texture;
	for (int i = 0; i < 4; ++i) {
		if (!tmp_texture.loadFromFile("Image/" + std::to_string(i) + ".png")) {
			abort();
		}
		room_texture.push_back(tmp_texture);
	}
	clock_to_delay_between_bullet.restart();
	scoreboard.LoadScoreboardFromFile();
	current_state = MENU;
}

/*void ResizeView(sf::RenderWindow& window, sf::View& view, float width, float height) {
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(width * aspectRatio, height);
}*/

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
	if (!soundBgBuffer.loadFromFile("Sound/7689.wav")) {
		abort();
	}
	soundChangePage.play();
	soundBg.setBuffer(soundBgBuffer);
	soundBg.play();
    while (current_state == MENU) {
		win.setTitle("MENU");
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
							level = 1;
							isaachp = 10;
							isaacfireSpeed = 3.0f;
							isaacfireTime = 0.5f;
							isaacdamage = 2.0f;
							isaacscore = 0;
							reset();
							soundBg.stop();
							current_state = PLAY;
							break;
						}
						case 1: {
							soundBg.stop();
							current_state = SCOREBOARD;
							break;
						}
						case 2: {
							soundBg.stop();
							current_state = PERM_END;
							scoreboard.SaveScoreboardToFile();
							win.close();
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
			/*if (evnt.type == sf::Event::Resized) {
				ResizeView(win, view, win_width, win_height);
			}*/
        }
		win.clear();
		menu.Draw(win);
		win.display();
    }
}

void Engine::stateSCOREBOARD() {
	if (!soundBgBuffer.loadFromFile("Sound/7702.wav")) {
		abort();
	}
	soundChangePage.play();
	soundBg.setBuffer(soundBgBuffer);
	soundBg.play();

	while (current_state == SCOREBOARD) {
		win.setTitle("SCOREBOARD");
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

void Engine::statePAUSE() {
	soundChangePage.play();
	while (current_state == PAUSE) {
		win.setTitle("PAUSE");
		sf::Event evnt;
		while (win.pollEvent(evnt)) {
			switch (evnt.type) {
			case sf::Event::KeyReleased: {
				switch (evnt.key.code) {
				case sf::Keyboard::W: {
					pause.MoveUp();
					break;
				}
				case sf::Keyboard::S: {
					pause.MoveDown();
					break;
				}
				case sf::Keyboard::Return:
					switch (pause.GetPressedItem()) {
					case 0: {
						current_state = roomNow;
						break;
					}
					case 1: {
						current_state = MENU;
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
		pause.Draw(win);
		win.display();
	}
}

void Engine::reset() {
	bullet_array.clear();
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
	treasure_picked_play = false;
	boss_defeated = false;

	if (level > 1) {
		player.SetDamage(isaacdamage);
		player.SetFireSpeed(isaacfireSpeed);
		player.SetFireTime(isaacfireTime);
		player.SetHp(isaachp);
		score = isaacscore;
	}
	else {
		score = 0;
	}

	clock_to_delay_between_bullet.restart();
}

void Engine::statePLAY() {
	if (!soundEffectBuffer.loadFromFile("Sound/Death_Burst_Small_1.wav")) {
		abort();
	}
	soundEffect.setBuffer(soundEffectBuffer);

	sf::RectangleShape roomBg;
	roomBg.setSize(sf::Vector2f(win_width, win_height));
	roomBg.setPosition(sf::Vector2f(0.0f, 0.0f));
	sf::Texture roomTexture;
	if (level == 1) {
		roomTexture.loadFromFile("Image/RoomLevel1.png");
	}
	else if (level == 2) {
		roomTexture.loadFromFile("Image/RoomLevel2-1.png");
	}
	else {
		roomTexture.loadFromFile("Image/RoomLevel3-1.png");
	}
	roomBg.setTexture(&roomTexture);
	Item item;
	std::vector <Item> item_array;

	win.setTitle("Score : " + std::to_string(score));
	std::vector < std::shared_ptr < Enemy >> enemy_array;
	while (current_state == PLAY) {
		deltaTime = clock.restart().asSeconds();
		if (new_room) {
			prepareRoomTileMap();
			if (checkIsUniqueVisitedRoom(room_map_pos_y, room_map_pos_x)) {
				int maxMon = rand() % 7;
				int i = 0;
				while (i < maxMon) {
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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				roomNow = PLAY;
				current_state = PAUSE;
				statePAUSE();
				break;
			}
		}

		movePlayer(deltaTime);
		playerShoot();

		if (enemy_array.size() == 0) {
			addVisitedRoom();
			unlockDoors();
			movePlayerNextRoom();
		}

		for (int i = 0; i < enemy_array.size(); ++i) {
			//Bullet:
			for (iter_bullet = bullet_array.begin(); iter_bullet != bullet_array.end(); ++iter_bullet) {
				if (enemy_array[i]->getHitbox().intersects(iter_bullet->getHitbox())) {
					soundBulletHitted.play();
					iter_bullet->setHitted();
					score++;
					enemy_array[i]->hitted(iter_bullet->getDamage());
				}
			}
		}

		for (int i = 0; i < enemy_array.size(); ++i) {
			//Player:
			if (enemy_array[i]->getHitbox().intersects(player.getHitbox())) {
				player.Hitted(enemy_array[i]->getDamage());
				soundPlayerHurt.play();
			}
		}

		for (int i = 0; i < enemy_array.size(); ++i) {
			//CollisWall:
			enemy_array[i]->update(player.GetShape().getPosition());
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
		}

		//Bullet hitted Wall:
		for (auto iter_bullet = bullet_array.begin(); iter_bullet != bullet_array.end();) {
			if (isCollsionWithWall(iter_bullet->getHitbox(), true)
				or iter_bullet->isHitted()
				or iter_bullet->getShape().getPosition().x <= 0
				or iter_bullet->getShape().getPosition().x + iter_bullet->getHitbox().width >= win_width
				or iter_bullet->getShape().getPosition().y <= 0 or iter_bullet->getShape().getPosition().y + iter_bullet->getHitbox().height >= win_height) {

				soundBulletHitted.play();
				iter_bullet = bullet_array.erase(iter_bullet);
			}
			else {
				++iter_bullet;
			}
		}

		for (int i = 0; i < enemy_array.size(); ++i) {
			//Enemy Dead:
			if (enemy_array[i]->getHp() <= 0) {
				soundEffect.play();
				randomHeart = rand() % 10;
				if (randomHeart >= 8) {
					soundItemSpawn.play();
					item.setPos(enemy_array[i]->getPos());
					item_array.push_back(item);
				}
				enemy_array.erase(enemy_array.begin() + i);
				score += 10;
				win.setTitle("Score : " + std::to_string(score));
				--i;
			}
		}

		for (int i = 0; i < item_array.size(); i++) {
			if (item_array[i].getHitbox().intersects(player.getHitbox()) and treasure_picked_play == false) {
				player.Upgrade(item.getId());
				treasure_picked_play = true;
				item_array.erase(item_array.begin() + i);
				score += 10;
				win.setTitle("Score : " + std::to_string(score));
			}
		}

		if (player.GetHp() <= 0) {
			isWin = false;
			current_state = END;
		}

		win.clear();
		win.draw(roomBg);
		drawRoom();

		for (int i = 0; i < item_array.size(); i++) {
			if (!treasure_picked_play) {
				win.draw(item_array[i].getShape());
			}
		}

		for (iter_bullet = bullet_array.begin(); iter_bullet != bullet_array.end(); ++iter_bullet) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(win);
			iter_bullet->Update(/*mousePos, win, player.GetPosition()*/);
			iter_bullet->fire(player.GetFireSpeed(), iter_bullet->getbulletVector());
			win.draw(iter_bullet->getShape());
		}

		for (int i = 0; i < enemy_array.size(); ++i) {
			win.draw(enemy_array[i]->getShape());
		}

		win.draw(player.GetShape());
		heart.draw(win,player.GetHp());
		win.display();
	}
}

void Engine::stateBR() {
	sf::RectangleShape roomBg;
	roomBg.setSize(sf::Vector2f(win_width, win_height));
	roomBg.setPosition(sf::Vector2f(0.0f, 0.0f));
	sf::Texture roomTexture;
	roomTexture.loadFromFile("Image/RoomLevel1-Boss.png");
	roomBg.setTexture(&roomTexture);

	prepareRoomTileMap();
	addVisitedRoom();

	std::vector<std::shared_ptr<Enemy>> enemy_array;
	if (boss_defeated == false) {
		std::shared_ptr<Boss> boss = std::make_shared<Boss>(sf::Vector2f(win_width / 2, win_height / 2));
		enemy_array.push_back(boss);
	}

	sf::RectangleShape trophy;
	sf::Texture trophyTexture;
	sf::Sprite trophySprite;
	sf::RectangleShape portal;
	sf::Texture portalTexture;
	sf::Sprite portalSprite;

	if (!trophyTexture.loadFromFile("Image/Trophy-1.png")) {
		abort();
	}
	if (!portalTexture.loadFromFile("Image/Portal-2.png")) {
		abort();
	}
	

	trophy.setSize(sf::Vector2f(100, 100));
	trophy.setOrigin(trophy.getLocalBounds().width / 2, trophy.getLocalBounds().height / 2);
	trophy.setPosition(sf::Vector2f(win_width / 2, win_height / 2));
	trophy.setTexture(&trophyTexture);

	portal.setSize(sf::Vector2f(100, 150));
	portal.setOrigin(portal.getLocalBounds().width / 2, portal.getLocalBounds().height / 2);
	portal.setPosition(sf::Vector2f(win_width / 2, win_height / 2));
	portal.setTexture(&portalTexture);

	Animation portalAnimation(&portalTexture, sf::Vector2u(1,4), 0.3f);

	while (current_state == BOSS_ROOM) {
		sf::Event evnt;
		deltaTime = clock.restart().asSeconds();
		while (win.pollEvent(evnt)) {
			if (evnt.type == sf::Event::Closed) {
				scoreboard.SaveScoreboardToFile();
				current_state = PERM_END;
				win.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				roomNow = BOSS_ROOM;
				current_state = PAUSE;
				statePAUSE();
				break;
			}
		}

		movePlayer(deltaTime);
		movePlayerNextRoom();

		if (player.getHitbox().intersects(trophy.getGlobalBounds()) and enemy_array.size() == 0) {
			score += 10;
			isaacdamage = player.GetDamage();
			isaacfireSpeed = player.GetFireSpeed();
			isaacfireTime = player.GetFireTime();
			isaachp = player.GetHp();
			isaacscore = score;
			win.setTitle("Score : " + std::to_string(score));
			if (level < 3) { level++; reset(); current_state = PLAY; }
			else { isWin = true; current_state = END; }
		}

		if (player.GetHp() <= 0) {
			isWin = false;
			current_state = END;
		}

		playerShoot();

		if (enemy_array.size() == 0) {
			win.setTitle("Score : " + std::to_string(score));
			addVisitedRoom();
			unlockDoors();
			movePlayerNextRoom();
			boss_defeated = true;
		}

		for (int i = 0; i < enemy_array.size(); ++i) {
			enemy_array[i]->update(player.GetShape().getPosition());
			if (isCollsionWithWall(enemy_array[i]->getHitbox())) {
				while (isCollsionWithWall(enemy_array[i]->getHitbox())) {
					enemy_array[i]->update(player.GetShape().getPosition(), true);
				}

				if (isCollsionWithWall(enemy_array[i]->fakeUpdate(HORIZONTAL, false)) or isCollsionWithWall(enemy_array[i]->fakeUpdate(HORIZONTAL, true))) {
					enemy_array[i]->update(player.GetShape().getPosition(), false, VERTICAL);
				}
				else if (isCollsionWithWall(enemy_array[i]->fakeUpdate(VERTICAL, false)) or isCollsionWithWall(enemy_array[i]->fakeUpdate(VERTICAL, true))) {
					enemy_array[i]->update(player.GetShape().getPosition(), false, HORIZONTAL);
				}
			}
		}

		for (int i = 0; i < enemy_array.size(); ++i) {
			for (iter_bullet = bullet_array.begin(); iter_bullet != bullet_array.end(); ++iter_bullet) {
				if (enemy_array[i]->getHitbox().intersects(iter_bullet->getHitbox())) {
					soundBulletHitted.play();
					iter_bullet->setHitted();
					score++;
					enemy_array[i]->hitted(iter_bullet->getDamage());
				}
			}
		}

		for (int i = 0; i < enemy_array.size(); ++i) {
			if (enemy_array[i]->getHitbox().intersects(player.getHitbox())) {
				soundPlayerHurt.play();
				player.Hitted(enemy_array[i]->getDamage());
			}
		}

		for (auto iter_bullet = bullet_array.begin(); iter_bullet != bullet_array.end();) {
			if (isCollsionWithWall(iter_bullet->getHitbox(), true)
				or iter_bullet->isHitted()
				or iter_bullet->getShape().getPosition().x <= 0
				or iter_bullet->getShape().getPosition().x + iter_bullet->getHitbox().width >= win_width
				or iter_bullet->getShape().getPosition().y <= 0 or iter_bullet->getShape().getPosition().y + iter_bullet->getHitbox().height >= win_height) {

				soundBulletHitted.play();
				iter_bullet = bullet_array.erase(iter_bullet);
			}
			else {
				++iter_bullet;
			}
		}

		for (int i = 0; i < enemy_array.size(); ++i) {
			if (enemy_array[i]->getHp() <= 0) {
				score += 100;
				soundBossDied.play();
				enemy_array.erase(enemy_array.begin() + i);
				--i;
			}
		}

		win.clear();
		win.draw(roomBg);
		drawRoom();
		win.draw(player.GetShape());

		for (iter_bullet = bullet_array.begin(); iter_bullet != bullet_array.end(); ++iter_bullet) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(win);
			iter_bullet->Update(/*mousePos, win, player.GetPosition()*/);
			iter_bullet->fire(player.GetFireSpeed(), iter_bullet->getbulletVector());
			win.draw(iter_bullet->getShape());
		}

		if (enemy_array.size() == 0) {
			if(level == 3) { win.draw(trophy); }
			else { 
				portalAnimation.Update(0, deltaTime);
				portal.setTextureRect(portalAnimation.uvRect);
				win.draw(portal); 
			}
		}
		else {
			for (int i = 0; i < enemy_array.size(); ++i) {
				bossAnimation.Update(0, deltaTime);
				enemy_array[i]->setAnime(bossAnimation.uvRect);
				win.draw(enemy_array[i]->getShape());
			}
		}

		heart.draw(win, player.GetHp());
		win.display();
	}
}

void Engine::stateTR() {
	sf::RectangleShape roomBg;
	roomBg.setSize(sf::Vector2f(win_width, win_height));
	roomBg.setPosition(sf::Vector2f(0.0f, 0.0f));
	sf::Texture roomTexture;
	roomTexture.loadFromFile("Image/RoomLevel2.png");
	roomBg.setTexture(&roomTexture);
	Item item(sf::Vector2f(win_width / 2, win_height / 2));
	prepareRoomTileMap();
	unlockDoors();
	addVisitedRoom();
	soundTR.play();

	while (current_state == TREASURE_ROOM) {
		sf::Event evnt;
		deltaTime = clock.restart().asSeconds();
		while (win.pollEvent(evnt)) {
			if (evnt.type == sf::Event::Closed) {
				scoreboard.SaveScoreboardToFile();
				current_state = PERM_END;
				win.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				roomNow = TREASURE_ROOM;
				current_state = PAUSE;
				statePAUSE();
				break;
			}
		}

		movePlayer(deltaTime);
		if (item.getHitbox().intersects(player.getHitbox()) and treasure_picked == false) {
			player.Upgrade(item.getId());
			treasure_picked = true;
			score += 10;
			win.setTitle("Score : " + std::to_string(score));
		}

		movePlayerNextRoom();
		win.clear();
		win.draw(roomBg);
		drawRoom();

		if (!treasure_picked) {
			win.draw(item.getShape());
		}
		win.draw(player.GetShape());
		heart.draw(win, player.GetHp());
		win.display();
	}
}

void Engine::stateEND() {
	std::string user_str;
	font.loadFromFile("IsaacScript2.ttf");
	sf::Text top_score_text;
	top_score_text.setFont(font);
	top_score_text.setStyle(sf::Text::Bold);
	top_score_text.setFillColor(sf::Color::Magenta);
	top_score_text.setCharacterSize(120);
	top_score_text.setString("New Score");
	top_score_text.setOrigin(top_score_text.getLocalBounds().width / 2, top_score_text.getLocalBounds().height / 2);
	top_score_text.setPosition(sf::Vector2f(win.getSize().x / 2, 100));

	sf::Text player_score_text;
	player_score_text.setFont(font);
	player_score_text.setStyle(sf::Text::Bold);
	player_score_text.setCharacterSize(80);
	player_score_text.setString("Score: " + std::to_string(score));
	player_score_text.setOrigin(player_score_text.getLocalBounds().width / 2, player_score_text.getLocalBounds().height / 2);
	player_score_text.setPosition(sf::Vector2f(win.getSize().x / 2, 260));

	sf::Text enter_text;
	enter_text.setFont(font);
	enter_text.setStyle(sf::Text::Bold);
	enter_text.setFillColor(sf::Color::Yellow);
	enter_text.setCharacterSize(50);
	enter_text.setString("Enter your name:        ");
	enter_text.setOrigin(enter_text.getLocalBounds().width / 2, 0);
	enter_text.setPosition(sf::Vector2f(win.getSize().x / 2 - 40, 370));

	sf::Text user_text;
	user_text.setFont(font);
	user_text.setCharacterSize(50);
	user_text.setString(".....");
	user_text.setPosition(sf::Vector2f(win.getSize().x / 2 + 150, 370));

	sf::Text confirmation_text;
	confirmation_text.setFont(font);
	confirmation_text.setStyle(sf::Text::Bold);
	confirmation_text.setCharacterSize(70);
	confirmation_text.setString("Press SPACE to confirm");
	confirmation_text.setOrigin(confirmation_text.getLocalBounds().width / 2, confirmation_text.getLocalBounds().height / 2);
	confirmation_text.setPosition(sf::Vector2f(win.getSize().x / 2, win.getSize().y - 230));

	while (current_state == END) {
		sf::Event event;
		while (win.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				scoreboard.SaveScoreboardToFile();
				current_state = PERM_END;
				win.close();
			}

			if (event.type == sf::Event::TextEntered) {
				int user_input = event.text.unicode;

				if ((user_input >= 65 and user_input <= 90) or
					(user_input >= 97 and user_input <= 122)) {
					if (user_str.length() < 5) {
						user_str += event.text.unicode;
					}
				}

				if (user_input == 8) {
					if (user_str.length() > 0) {
						user_str.erase(user_str.length() - 1);
					}
				}

				if (user_input == 32) {
					if (score > scoreboard.GetLastScore()) { scoreboard.Add(user_str, score); }
					current_state = MENU;
				}

				user_text.setString(user_str);
			}
		}

		win.clear();
		win.draw(top_score_text);
		win.draw(player_score_text);
		win.draw(enter_text);
		win.draw(user_text);
		win.draw(confirmation_text);
		win.display();
	}

	if (score <= scoreboard.GetLastScore() or isWin == false) {
		current_state = MENU;
	}
}

void Engine::playerShoot() {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)  and clock_to_delay_between_bullet.getElapsedTime() >= sf::seconds(player.GetFireTime())) {
		soundBullet.play();
		sf::Vector2i mousePos = sf::Mouse::getPosition(win);
		int bulletVector = 0;
		float bulletAngle = (float)(180 / PI * atan2(abs(mousePos.y - player.GetPosition().y), abs(mousePos.x - player.GetPosition().x)));

		if (player.GetPosition().x <= mousePos.x) {
			if (bulletAngle <= 45) {
				bulletVector = 2;
			}
			else {
				if (player.GetPosition().y < mousePos.y) {
					bulletVector = 3;
				}
				else {
					bulletVector = 1;
				}
			}
		}
		else if (player.GetPosition().x > mousePos.x) {
			if (bulletAngle <= 45) {
				bulletVector = 4;
			}
			else {
				if (player.GetPosition().y < mousePos.y) {
					bulletVector = 3;
				}
				else {
					bulletVector = 1;
				}
			}
		}
		
		bullet.setBulletVector(bulletVector);
		bullet.setPos(sf::Vector2f(player.GetShape().getPosition().x + player.getHitbox().width / 2, player.GetShape().getPosition().y + player.getHitbox().height / 2), player.GetDamage(), player.GetFireSpeed(), bulletVector);
		bullet_array.push_back(bullet);
		clock_to_delay_between_bullet.restart();
	}
}

void Engine::movePlayer(float deltaTime) {
	float playerspeed = 5.0f;
	if (isCollsionWithWall(player.getHitbox())) {
		playerspeed = 1.0f;
	}
	player.Update(deltaTime, playerspeed);
	playerAnimation.Update(player.GetRow(), deltaTime);
	player.setAnime(playerAnimation.uvRect);
}

bool Engine::movePlayerNextRoom() {
	sf::Vector2f position = player.GetShape().getPosition();

	if (player.GetShape().getPosition().y <= 0 or player.GetShape().getPosition().y + player.getHitbox().height > win_height or player.GetShape().getPosition().x <= 0 or player.GetShape().getPosition().x + player.getHitbox().width >= win_width) {
		if (player.GetShape().getPosition().y <= 0) {
			if (map.IsMovePossible(room_map_pos_y - 1, room_map_pos_x)) {
				room_map_pos_y -= 1;
				map.SetupTileMap(room_map_pos_y, room_map_pos_x);
				prepareRoomTileMap();
				position.y = win_height - player.getHitbox().height - room_tile_map[0][0].shape.getLocalBounds().height;
				player.setNewPosition(position);
			}
		}
		else if (player.GetShape().getPosition().y + player.getHitbox().height > win_height) {
			if (map.IsMovePossible(room_map_pos_y + 1, room_map_pos_x)) {
				room_map_pos_y += 1;
				map.SetupTileMap(room_map_pos_y, room_map_pos_x);
				prepareRoomTileMap();
				position.y = room_tile_map[0][0].shape.getLocalBounds().height;
				player.setNewPosition(position);
			}
		}
		else if (player.GetShape().getPosition().x <= 0) {
			if (map.IsMovePossible(room_map_pos_y, room_map_pos_x - 1)) {
				room_map_pos_x -= 1;
				map.SetupTileMap(room_map_pos_y, room_map_pos_x);
				prepareRoomTileMap();
				position.x = win_width - player.getHitbox().width - room_tile_map[0][0].shape.getLocalBounds().width;
				player.setNewPosition(position);
			}
		}
		else if (player.GetShape().getPosition().x + player.getHitbox().width >= win_width) {
			if (map.IsMovePossible(room_map_pos_y, room_map_pos_x + 1)) {
				room_map_pos_x += 1;
				map.SetupTileMap(room_map_pos_y, room_map_pos_x);
				prepareRoomTileMap();
				position.x = room_tile_map[0][0].shape.getLocalBounds().width;
				player.setNewPosition(position);
			}
		}

		bullet_array.clear();

		if (map.GetRoomId(room_map_pos_y, room_map_pos_x) == 3) {
			current_state = TREASURE_ROOM;
			stateTR();
		}
		else if (map.GetRoomId(room_map_pos_y, room_map_pos_x) == 4) {
			current_state = BOSS_ROOM;
			stateBR();
		}
		else {
			current_state = PLAY;
		}

		new_room = true;
		return true;
	}
	return false;
}

bool Engine::checkIsUniqueVisitedRoom(int row, int col) const{
	for (int i = 0; i < visited_room_map.size(); i++) {
		if (visited_room_map[i].row == row and visited_room_map[i].col == col) {
			return false;
		}
	}
	return true;
}

void Engine::addVisitedRoom() {
	if (checkIsUniqueVisitedRoom(room_map_pos_y, room_map_pos_x)) {
		Room room;
		room.row = room_map_pos_y;
		room.col = room_map_pos_x;
		visited_room_map.push_back(room);
	}
	return;
}

void Engine::unlockDoors() {
	for (int row = 0; row < room_tile_map.size(); row++) {
		for (int col = 0; col < room_tile_map[row].size(); col++) {
			if (room_tile_map[row][col].is_door == true) {
				room_tile_map[row][col].is_wall = false;
				room_tile_map[row][col].can_go_through = true;
				room_tile_map[row][col].can_shoot_through = true;
				room_tile_map[row][col].shape.setFillColor(sf::Color::Yellow);
				room_tile_map[row][col].shape_sprite.setTexture(room_texture[2]);
			}
		}
	}
	soundUnlockDoor.play();
}

void Engine::prepareRoomTileMap() {
	std::vector<std::vector<char>> char_tile_map = map.GetRoomTileMap();

	for (int row = 0; row < char_tile_map.size(); row++) {
		for (int col = 0; col < char_tile_map[row].size(); col++) {
			room_tile_map[row][col].shape.setSize(sf::Vector2f(70, 65));
			room_tile_map[row][col].shape.setPosition(sf::Vector2f(col * 70, row * 65));
			room_tile_map[row][col].shape_sprite.setPosition(room_tile_map[row][col].shape.getPosition());
			room_tile_map[row][col].is_wall = true;
			room_tile_map[row][col].can_go_through = false;
			room_tile_map[row][col].can_shoot_through = false;
			room_tile_map[row][col].is_door = false;
			room_tile_map[row][col].shape.setFillColor(sf::Color::Red);

			switch (char_tile_map[row][col]) {
				case '.': {
					room_tile_map[row][col].is_wall = false;
					room_tile_map[row][col].can_go_through = true;
					room_tile_map[row][col].can_shoot_through = true;
					room_tile_map[row][col].shape.setFillColor(sf::Color::Magenta);
					room_tile_map[row][col].shape_sprite.setTexture(room_texture[3]);
				}
				case '_': {
					room_tile_map[row][col].is_wall = false;
					room_tile_map[row][col].can_shoot_through = true;
					room_tile_map[row][col].shape.setFillColor(sf::Color::Green);
					room_tile_map[row][col].shape_sprite.setTexture(room_texture[1]);
				}
				case 'D': {
					room_tile_map[row][col].shape_sprite.setTexture(room_texture[0]);
					if (map.IsMovePossible(room_map_pos_y - 1, room_map_pos_x) and row == 0) {
						room_tile_map[row][col].is_door = true;
					}
					if (map.IsMovePossible(room_map_pos_y + 1, room_map_pos_x) and row == room_tile_map.size() - 1) {
						room_tile_map[row][col].is_door = true;
					}
					if (map.IsMovePossible(room_map_pos_y, room_map_pos_x - 1) and col == 0) {
						room_tile_map[row][col].is_door = true;
					}
					if (map.IsMovePossible(room_map_pos_y, room_map_pos_x + 1) and col == room_tile_map[0].size() - 1) {
						room_tile_map[row][col].is_door = true;
					}
				}
				break;
			}
		}
	}
}

void Engine::drawRoom() {
	for (int row = 0; row < room_tile_map.size(); row++) {
		for (int col = 0; col < room_tile_map[row].size(); col++) {
			if (room_tile_map[row][col].is_door == true && room_tile_map[row][col].can_go_through == true) {
				win.draw(room_tile_map[row][col].shape);
				win.draw(room_tile_map[row][col].shape_sprite);
			}
		}
	}
}

bool Engine::isCollsionWithWall(sf::FloatRect objPos, bool isBullet) const{
	for (int row = 0; row < room_tile_map.size(); row++) {
		for (int col = 0; col < room_tile_map[row].size(); col++) {
			if (room_tile_map[row][col].shape.getGlobalBounds().intersects(objPos)) {
				if (isBullet and room_tile_map[row][col].can_shoot_through == true) {
					return false;
				}
				else if (isBullet and room_tile_map[row][col].can_shoot_through == false) {
					return true;
				}
				else if (room_tile_map[row][col].can_go_through == false) {
					return true;
				}
			}
		}
	}

	return false;
}