#pragma once
#include <string>
#include <iostream>
#include <vector>
class Cell
{
private:
	std::vector<char> sprite;
	int type;
	int cell_size=3;
	bool has_key = false;
	bool has_door = false;
public:
	Cell();
	Cell(int _type);
	void InitProperties(int _type);

	void AddKey();
	void RemoveKey();
	void AddDoor();
	void RemoveDoor();

	bool IsKeyPlaced();
	bool IsDoorPlaced();

	bool IsCellEmpty();

	void Draw();
	int GetType();
	std::vector<char> getSprite();
	bool operator==(const Cell& other) const;
};

