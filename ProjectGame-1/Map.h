#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <string>

#ifndef MAP_GEN_H
#define MEP_GEN_H

class Map {
	int number_of_rooms;
	int room_map_size;
	int room_map[5][5];

	//Tile room_tile_map[11][15];
	std::vector < std::vector<char> > room_tile_map;

	bool IsConnection(int pos_y, int pos_x) const;
	bool IsInBoard(int pos_y, int pos_x) const;

	void Clear();

public:
	Map();
	void Generate();
	void DebugDisplay() const;

	bool IsMovePossible(int pos_y, int pos_x) const;

	void SetupTileMap(int room_map_pos_y, int room_map_pos_x);

	std::vector<std::vector<char>> GetRoomTileMap() const;

	int GetRoomId(int pos_y, int pos_x) const;
	int GetStartPosition() const;
	int GetNumberOfRooms() const;
};

#endif