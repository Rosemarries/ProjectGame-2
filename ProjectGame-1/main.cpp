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
}