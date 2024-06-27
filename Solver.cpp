#include "Solver.h"

Solver::Solver()
{
}

Solver::Solver(GridMap& _Map)
{
	//std::cout<<"See you space cowbow"<<std::endl;
	Map = _Map;
	size = Map.GetSize();
	for (int i = 0; i < size * size; i++) {
		originall_cells.push_back(Map.GetCellType(i));
		if (Map.HasDoor(i) == true) { original_doors_pos.push_back(i); }
		if (Map.HasKey(i) == true) { original_keys_pos.push_back(i); }
	}
	
}



bool Solver::AbleToMoveMapGeom(const int _current_loc, const int _next_loc)
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

bool Solver::AbleToMoveCell(const int _next_loc)
{
	if (Map.GetCellType(_next_loc) == 0) {
		return false;
	}
	else if (Map.GetCellType(_next_loc) == 1)
	{
		if (Map.HasDoor(_next_loc) == true) {
			if (equipted_keys > 0) {
				return true;
			}
			else { return false; }
		}
		else { return true; }
	}
	else { return true; }
}

bool Solver::AbleToMoveCheckBridgeConnection(const int current_loc, const int next_loc)
{
	if (Map.GetCellType(current_loc) == 1)
	{
		return true;
	}
	else if (Map.GetCellType(current_loc) == 2)
	{
		if (next_loc == current_loc - 1 || next_loc == current_loc + 1)
		{
			return true;
		}
		else { return false; }
	}
	else if (Map.GetCellType(current_loc) == 3)
	{
		if (next_loc == current_loc - size || next_loc == current_loc + size)
		{
			return true;
		}
		else { return false; }
	}
	else if (Map.GetCellType(current_loc) == 4)
	{
		if (next_loc == current_loc - size || next_loc == current_loc - 1)
		{
			return true;
		}
		else { return false; }
	}
	else if (Map.GetCellType(current_loc) == 5)
	{
		if (next_loc == current_loc - 1 || next_loc == current_loc + size)
		{
			return true;
		}
		else { return false; }
	}
	else if (Map.GetCellType(current_loc) == 6)
	{
		if (next_loc == current_loc - size || next_loc == current_loc + 1)
		{
			return true;
		}
		else { return false; }
	}
	else if (Map.GetCellType(current_loc) == 7)
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

bool Solver::IsBridgeNotExplored(const int _next_loc)
{
	if (std::find(explored_bridges.begin(), explored_bridges.end(), _next_loc) != explored_bridges.end())
	{
		return false;
	}
	else { return true; }
}

bool Solver::ValidMove(const int current_loc, const int _next_step)
{
	if (AbleToMoveMapGeom(current_loc, _next_step) == true)
	{
		if (AbleToMoveCell(_next_step) == true)
		{
			if (IsBridgeNotExplored(_next_step) == true) {
				if (AbleToMoveCheckBridgeConnection(current_loc, _next_step) == true) {
					return true;
				}
			}
		}
	}
	else { return false; }
}

void Solver::ChangeEncounters(const int _current_loc)
{
	if (Map.GetCellType(_current_loc) == 1)
	{
		if (Map.HasDoor(_current_loc) == true) {
			if (equipted_keys > 0) {
				equipted_keys--;
				Map.RemoveDoor(_current_loc);
			}
		
		}
		if (Map.HasKey(_current_loc) == true) {
			equipted_keys++;
			Map.RemoveKey(_current_loc);
		}
	}
}

void Solver::BanTheBridge(const int _current_loc)
{
	if (Map.GetCellType(_current_loc) != 0 && Map.GetCellType(_current_loc) != 1)
	{
		explored_bridges.push_back(_current_loc);
	}
}

void Solver::UnChangeEncounters(const int _current_loc)
{
	if (Map.GetCellType(_current_loc) == 1)
	{
		if (find(original_doors_pos.begin(),original_doors_pos.end(),_current_loc) != original_doors_pos.end()) {
			Map.SetDoor(_current_loc);
			equipted_keys++;
		}
		else if (find(original_keys_pos.begin(), original_keys_pos.end(), _current_loc) != original_keys_pos.end()) {
			equipted_keys--;
			Map.SetKey(_current_loc);
		}
	}
}

void Solver::UnBanTheBridge(const int _current_loc)
{
	if (originall_cells[_current_loc] != 0 && originall_cells[_current_loc] != 1) {
		explored_bridges.push_back(_current_loc);
	}
}

void Solver::DoStep(const int _current_loc)
{
	BanTheBridge(_current_loc);
	ChangeEncounters(_current_loc);
}

void Solver::UndoStep(const int _current_loc)
{
	UnBanTheBridge(_current_loc);
	UnChangeEncounters(_current_loc);
}


bool Solver::CheckRequirements(const int current_loc)
{
	if (current_loc == size * size - 1 ) {
		return true;
	}
	else { return false; }
}

void Solver::SolveBackTrack(int current_loc)
{
	int next_step[4] = { current_loc - 1, current_loc + 1, current_loc - size, current_loc + size };
	int previous_step = current_loc;
	
	if (CheckRequirements(current_loc) == true)
	{
		possible_solutions.push_back(path);
	}
	for (int i = 0; i < 4; i++) {
		if (ValidMove(current_loc, next_step[i]) == true)
		{
			
			current_loc = next_step[i];
			DoStep(current_loc);
			path.push_back(current_loc);

			SolveBackTrack(current_loc);

			path.pop_back();
			UndoStep(current_loc);
			current_loc = previous_step;
			
		}

	}
}

void Solver::Solve()
{
	int start_pos = 0;
	SolveBackTrack(start_pos);
}

bool Solver::CanBeSolved()
{
	Solve();
	if (possible_solutions.size() == 0)
	{
		return false;
	}
	else {
		return true;
	}
}
std::vector<int> Solver::GetSolution()
{
	Solve();
	if (possible_solutions.size() == 0)
	{
		return std::vector<int>();
	}
	else {
		return possible_solutions[0];
	}
	
}
