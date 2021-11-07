#include "Map.h"
#include <iostream>
#include <string>

Map::Map() {

	room_tile_map.resize(11, std::vector<char>(15, ' '));

	number_of_rooms = 5;
	room_map_size = 5;
	//generate();
}

bool Map::IsConnection(int pos_y, int pos_x) const {
	if (IsMovePossible(pos_y + 1, pos_x) or IsMovePossible(pos_y - 1, pos_x) or
		IsMovePossible(pos_y, pos_x + 1) or IsMovePossible(pos_y, pos_x - 1))
		return true;
	return false;
}

bool Map::IsInBoard(int pos_y, int pos_x) const {
	if (pos_y >= 0 and pos_y < room_map_size and pos_x >= 0 and pos_x < room_map_size)
		return true;
	return false;
}

void Map::Clear() {
	for (int i = 0; i < room_map_size; ++i) {
		for (int j = 0; j < room_map_size; ++j)
			room_map[i][j] = 0;
	}
}

void Map::Generate() {
	Clear();

	int start_pos_y, start_pos_x;
	start_pos_y = start_pos_x = room_map_size / 2;
	room_map[start_pos_y][start_pos_x] = 1;

	int new_pos_y;
	int new_pos_x;

	for (int i = 0; i < number_of_rooms; ++i) {
		do {
			new_pos_y = rand() % room_map_size;
			new_pos_x = rand() % room_map_size;
		} while (!IsConnection(new_pos_y, new_pos_x) or room_map[new_pos_y][new_pos_x] != 0);
		room_map[new_pos_y][new_pos_x] = rand() % 2 + 1;

		if (i == number_of_rooms - 2) {
			room_map[new_pos_y][new_pos_x] = 3;
		}

		if (i == number_of_rooms - 1) {
			room_map[new_pos_y][new_pos_x] = 4;
		}
	}
}

void Map::DebugDisplay() const {
	for (int i = 0; i < room_map_size; ++i) {
		for (int j = 0; j < room_map_size; ++j) {
			std::cout << "[" << room_map[i][j] << "]";
		}
		std::cout << "\n";
	}
}

bool Map::IsMovePossible(int pos_y, int pos_x) const {
	if (!IsInBoard(pos_y, pos_x))
		return false;

	if (room_map[pos_y][pos_x] != 0)
		return true;

	return false;
}

int Map::GetRoomId(int pos_y, int pos_x) const {
	return room_map[pos_y][pos_x];
}

int Map::GetStartPosition() const {
	return room_map_size / 2;
}

std::vector<std::vector<char>> Map::GetRoomTileMap() const {
	return room_tile_map;
}


void Map::SetupTileMap(int room_map_pos_y, int room_map_pos_x) {
	std::ifstream file;
	file.open("Text/Room" + std::to_string(room_map[room_map_pos_y][room_map_pos_x]) + ".txt");
	if (!file.good()) {
		abort();
	}

	for (size_t row = 0; row < room_tile_map.size(); ++row) {
		for (size_t col = 0; col < room_tile_map[row].size(); ++col) {
			file >> room_tile_map[row][col];
		}
	}

	file.close();
}

int Map::GetNumberOfRooms() const {
	return number_of_rooms + 1;
}
