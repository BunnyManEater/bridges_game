#include "Cell.h"
void Cell::InitProperties(int _type) //MAYBE I CAN DO IT BETTER?
{
	
	if (_type == 0) { //water
		sprite= { ':',':',':',':',':',':',':',':',':' };
	}
	else if (_type == 1) { //iland
		sprite = { '#','#','#','#','#','#','#','#','#' };
	}
	else if (_type == 2) { // left-right br
		sprite = { ':',':',':','+','+','+',':',':',':' };
	}
	else if (_type == 3) { // up-down bridge
		sprite = { ':','+',':',':','+',':',':','+',':'};
	}
	else if (_type == 4) { //left-up brigde
		sprite = { ':','+',':','+','+',':',':',':',':' };
	}
	else if (_type == 5) { //left-down bridge
		sprite = { ':',':',':','+','+',':',':','+',':' };
	}
	else if (_type == 6) { //right-up bridge
		sprite = { ':','+',':',':','+','+',':',':',':' };
	}
	else if (_type == 7) {//right-down bridge
		sprite = { ':',':',':',':','+','+',':','+',':' };
	}
	else { std::cout << "Unvalid cell type!" << std::endl; }

	
}
void Cell::AddKey()
{
	if (type != 1) { std::cerr << "Unable to place key not on an island" << std::endl; return; }
	if (has_key == true) { std::cerr << "The island already has a key" << std::endl; return; }
	has_key = true;
	sprite[4] = 'K';
	return;
}
void Cell::RemoveKey()
{
	if (has_key == true) { has_key = false;}
	if (type == 1) { sprite[4] = '#'; }
	else { std::cerr << "The Cell does not have a key" << std::endl; }
}
void Cell::AddDoor()
{
	if (type != 1) { std::cerr << "Unable to place door not on an island" << std::endl; return; }
	if (has_door == true) { std::cerr << "The island already has a door" << std::endl; return; }
	has_door = true;
	sprite[4] = 'D';
	return;
}
void Cell::RemoveDoor()
{
	if (has_door == true) { has_door = false; }
	if (type == 1) { sprite[4] = '#'; }
	else { std::cerr << "The Cell does not have a door" << std::endl; }
}
bool Cell::IsKeyPlaced()
{
	if (has_key == true) { return true; }
	else { return false; }
}
bool Cell::IsDoorPlaced()
{
	if (has_door == false) { return false; }
	else { return false; }
}
bool Cell::IsCellEmpty()
{
	if (has_key == false && has_door == false)
	{
		return true;
	}
	else { return false; }
}
Cell::Cell(int _type)
{
	has_key = false;
	has_door = false;
	this->type = _type;
	sprite.resize(cell_size*cell_size);
	InitProperties(_type); 
}
Cell::Cell() {};
void Cell::Draw()
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			std::cout << sprite[i * 3 + j];
		}
		std::cout << "\n";
	}
}

int Cell::GetType()
{
	return type;
}

std::vector<char> Cell::getSprite()
{
	return sprite;
}

bool Cell::operator==(const Cell& other) const
{
	return  type == other.type;
}
