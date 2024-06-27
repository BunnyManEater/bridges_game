#pragma once
#include "Cell.h"
#include <fstream>
#include <string>

class GridMap
{ 
private:
	int size; //size of the board
	int cell_size = 3;
	std::vector<Cell*> Map;
	std::vector<char> map_sprite;
	Cell default_cell;
	Cell basic_island;
	Cell island_with_key;
	Cell island_with_door;

	Cell br_2;
	Cell br_3;
	Cell br_4;
	Cell br_5;
	Cell br_6;
	Cell br_7;

	void MakeDefaultMap();
public:
	GridMap();
	GridMap(int _size);
	GridMap(std::string file_name);
	void Resize(int _size);

	Cell operator[](int _i);
	void AddCell(Cell* _cell, int _pos_x, int _pos_y);
	void AddCell(Cell* _cell, int _index);
	void RemoveCell(int _pos_x, int _pos_y);
	void RemoveCell(int _index);

	void SetWater(int _i);

	void SetKey(int _index);
	void RemoveKey(int _index);
	void SetDoor(int _index);
	void RemoveDoor(int _index);

	bool HasKey(int _index);
	bool HasDoor(int _index);

	bool IsIslandEmpty(int _index);

	void MakeSprite();
	void Draw();
	int GetCellType(int _i);
	int GetSize();
	int GetSizeCell();
	char GetSpriteChar(int _index);
	void SaveToFile(std::string file_out); //Make Late
	bool AbleToMoveCell(const int _next_loc, int eq_keys);
	bool AbleToMoveMapGeom(const int _current_loc, const int _next_loc);

	bool AbleToMoveCheckBridgeConnection(const int curr_loc, const int next_loc);
	
	bool IsMovePossible(int curr_index, int next_index, int eq_keys);
	bool operator==(const GridMap& other) const;
};

