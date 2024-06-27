#include "GridMap.h"

void GridMap::MakeDefaultMap() //блин блинский
{
	for (int i = 0; i < size * size; i++) {
		Map[i] = &default_cell;
	}
}

GridMap::GridMap()
{
	size = 0;
	
	Cell temp(0);
	default_cell = temp;
	Cell temp_1(1);
	basic_island = temp_1;
	Cell temp_2(1);
	island_with_door = temp_2;
	island_with_door.AddDoor();
	Cell temp_3(1);
	island_with_key = temp_3;
	island_with_key.AddKey();
	
}
GridMap::GridMap(int _size)
{
	this->size = _size;
	Map.resize(size * size);
	Cell temp(0);
	default_cell = temp;
	Cell temp_1(1);
	basic_island = temp_1;
	Cell temp_2(1);
	island_with_door = temp_2;
	island_with_door.AddDoor();
	Cell temp_3(1);
	island_with_key = temp_3;
	island_with_key.AddKey();
	MakeDefaultMap();

}

GridMap::GridMap(std::string file_name)
{
	Cell temp(0);
	default_cell = temp;
	Cell temp_1(1);
	basic_island = temp_1;
	Cell temp_2(1);
	island_with_door = temp_2;
	island_with_door.AddDoor();
	Cell temp_3(1);
	island_with_key = temp_3;
	island_with_key.AddKey();
	
	Cell br_t_2(2);
	br_2 = br_t_2;
	Cell br_t_3(3);
	br_3 = br_t_3;
	Cell br_t_4(4);
	br_4 = br_t_4;
	Cell br_t_5(5);
	br_5 = br_t_5;
	Cell br_t_6(6);
	br_6 = br_t_6;
	Cell br_t_7(7);
	br_7 = br_t_7;

	

	std::ifstream file(file_name);
	std::vector<int> cell_types;
	if(file.is_open())
	{ 
		int temp;
		file>>temp;
		this->size = int(temp);
		Map.resize(size * size);
		MakeDefaultMap();
		std::cout<<"size "<<size<<std::endl;
		std::cout<<"yey"<<std::endl;
		for(int k=0; k<size*size;k++)
		{
			file>>temp;
			cell_types.push_back(int(temp));
		}
		file.close();
	}
	else{
		std::cerr<<"Error: Unable to open the file"<<std::endl;
	}
	for(int i=0; i<cell_types.size();i++)
	{
		if(cell_types[i] == 0){
			Map[i]=&default_cell;
		}
		else if(cell_types[i]==1){
			Map[i] = &basic_island;
		}
		else if(cell_types[i] == 2){
			Map[i] = &br_2;
		}
		else if(cell_types[i] == 3){
			Map[i] = &br_3;
		}
		else if(cell_types[i] == 4){
			Map[i] = &br_4;
		}
		else if(cell_types[i] == 5){
			Map[i] = &br_5;
		}
		else if(cell_types[i] == 6){
			Map[i] = &br_6;
		}
		else if(cell_types[i] == 7){
			Map[i] = &br_7;
		}
		else if(cell_types[i] == 8){
			Map[i] = &island_with_key;
		}
		else if(cell_types[i] == 9){
			Map[i] = &island_with_door;
		}	
	}
	std::cout<<"yey 2"<<std::endl;
}

void GridMap::Resize(int _size)
{
	size = _size;
	Map.resize(size * size);
	MakeDefaultMap();
}

Cell GridMap::operator[](int _i)
{
	return *Map[_i];
}


void GridMap::AddCell(Cell* _cell, int _pos_x, int _pos_y)
{
	Map[_pos_y *size + _pos_x] = _cell;
}

void GridMap::AddCell(Cell* _cell, int _index)
{
	Map[_index] = _cell;
}

void GridMap::RemoveCell(int _index) {
	Map[_index] = &default_cell;
}

void GridMap::SetWater(int _i)
{
	Map[_i] = &default_cell;
}

void GridMap::SetKey(int _index)
{
	Map[_index] = &island_with_key;
}

void GridMap::RemoveKey(int _index)
{
	Map[_index] = &basic_island;
}

void GridMap::SetDoor(int _index)
{
	
	Map[_index] = &island_with_door;
}

void GridMap::RemoveDoor(int _index)
{
	Map[_index] = &basic_island;
}

bool GridMap::HasKey(int _index)
{
	return Map[_index]->IsKeyPlaced();
}

bool GridMap::HasDoor(int _index)
{
	return Map[_index]->IsDoorPlaced();
}

bool GridMap::IsIslandEmpty(int _index)
{
	if (Map[_index]->IsCellEmpty() == true)
	{
		return true;
	}
	else { return false; }
}


void GridMap::MakeSprite()
{
	unsigned map_size = size;
	unsigned position = 0;
	map_sprite.resize(map_size * cell_size * map_size * cell_size);
	for (int cell_num = 0; cell_num < size*size; cell_num++) {
		for (int cell_row = 0; cell_row < cell_size; cell_row++) {
			for (int cell_col = 0; cell_col < cell_size; cell_col++) {
				position = (cell_num / map_size) * (map_size * cell_size * cell_size) + (cell_num % map_size) * cell_size + cell_row * cell_size * map_size + cell_col;
				//std::cout << "Cell_num: " << cell_num << "Position: " <<position<< std::endl;
				map_sprite[position] =  Map[cell_num]->getSprite()[cell_row * cell_size + cell_col];
				
			}
		}
	}
}

void GridMap::Draw()
{
	for(int i = 0; i < cell_size*size; i++) {
		for (int j = 0; j < cell_size*size; j++) {
			std::cout << map_sprite[i * cell_size*size + j];
		}
		std::cout << "\n";
	}
}

int GridMap::GetCellType(int _i)
{
	return Map[_i]->GetType();
}

int GridMap::GetSize()
{
	return size;
}

int GridMap::GetSizeCell()
{
	return cell_size;
}

char GridMap::GetSpriteChar(int _index)
{
	return map_sprite[_index];
}

void GridMap::SaveToFile(std::string file_out)
{
	
	std::vector<int> cell_types;
	cell_types.push_back(size);
	for (int i = 0; i < size * size; i++)
	{
		if (Map[i]->GetType() == 1)
		{
			if (Map[i]->IsKeyPlaced() == true)
			{
				cell_types.push_back(8);
			}
			else if (Map[i]->IsDoorPlaced() == true)
			{
				cell_types.push_back(9);
			}
			else {
				cell_types.push_back(1);
			}
		}
		else
		{
			cell_types.push_back(Map[i]->GetType());
		}
	}
	
	std::ofstream file(file_out);
	if(file.is_open())
	{ 
		for(int k=0;k<cell_types.size();k++)
		{ 
			file<<cell_types[k]<<" ";
		}
		file.close();
	}
	else{std::cerr<<"Error: Unable to open the file"<<std::endl;}


}


bool GridMap::operator==(const GridMap& other) const
{
	if (map_sprite.size() != 0) {
		return size == other.size && map_sprite == other.map_sprite && default_cell == other.default_cell;
	}
	else {
		std::cerr << "Unable to == Maps until they have thier sprites" << std::endl;
		return false;
	}
}

bool GridMap::AbleToMoveMapGeom(const int _current_loc, const int _next_loc)
{
	if (_next_loc < 0 || _next_loc >= size * size) { return false; }
	else if (_current_loc % size == 0) {
		if (_next_loc == _current_loc - 1) { return false; }
		else { return true; }
	}
	else if (_current_loc % size == size - 1) {
		if (_next_loc == _current_loc + 1) { return false; }
		else { return true; }
	}
	else { return true; }
	
}

bool GridMap::AbleToMoveCell(const int _next_loc, int eq_keys)
{
	if (GetCellType(_next_loc) == 0) {
		return false;
	}
	else if (GetCellType(_next_loc) == 1)
	{
		if (HasDoor(_next_loc) == true) {
			if (eq_keys > 0) {
				return true;
			}
			else { return false; }
		}
		else { return true; }
	}
	else { return true; }
}

bool GridMap::AbleToMoveCheckBridgeConnection(const int current_loc, const int next_loc)
{
	if (GetCellType(current_loc) == 1)
	{
		return true;
	}
	else if (GetCellType(current_loc) == 2)
	{
		if (next_loc == current_loc - 1 || next_loc == current_loc + 1)
		{
			return true;
		}
		else { return false; }
	}
	else if (GetCellType(current_loc) == 3)
	{
		if (next_loc == current_loc - size || next_loc == current_loc + size)
		{
			return true;
		}
		else { return false; }
	}
	else if (GetCellType(current_loc) == 4)
	{
		if (next_loc == current_loc - size || next_loc == current_loc - 1)
		{
			return true;
		}
		else { return false; }
	}
	else if (GetCellType(current_loc) == 5)
	{
		if (next_loc == current_loc - 1 || next_loc == current_loc + size)
		{
			return true;
		}
		else { return false; }
	}
	else if (GetCellType(current_loc) == 6)
	{
		if (next_loc == current_loc - size || next_loc == current_loc + 1)
		{
			return true;
		}
		else { return false; }
	}
	else if (GetCellType(current_loc) == 7)
	{
		if (next_loc == current_loc + size || next_loc == current_loc + 1)
		{
			return true;
		}
		else { return false; }
	}
	else {
		std::cout << "thats sus!" << std::endl;
		return true;
	}
}


bool GridMap::IsMovePossible(int current_loc, int _next_step, int eq_keys)
{
	if (AbleToMoveMapGeom(current_loc, _next_step) == true)
	{
		if (AbleToMoveCell(_next_step,eq_keys) == true)
		{
			if(AbleToMoveCheckBridgeConnection(current_loc,_next_step)== true){ return true; }
			}
		}
	
	
	else { return false; }
		
}
