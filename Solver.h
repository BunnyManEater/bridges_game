
#pragma once
#include <algorithm>
#include"GridMap.h"
#include "Cell.h"
class Solver
{
private:
	GridMap Map;
	int size;
	Cell basic_cell;
	Cell water_cell;
	std::vector<int> explored_bridges;
	int equipted_keys = 0;

	std::vector<int> originall_cells;
	std::vector<int> original_keys_pos;
	std::vector<int> original_doors_pos;

	std::vector<int> path;
	std::vector<std::vector<int>> possible_solutions;


	
	//checking if move is possible:
	bool CheckRequirements(const int current_loc);

	bool AbleToMoveMapGeom(const int current_loc, const int next_loc);
	bool AbleToMoveCell(const int _next_loc);
	bool AbleToMoveCheckBridgeConnection(const int current_loc, const int next_loc);
	bool IsBridgeNotExplored(const int _next_loc);

	bool ValidMove(const int current_loc, const int _next_step);
	//changing the map due to the move
	void ChangeEncounters(const int _current_loc);
	void BanTheBridge(const int _current_loc);

	//getting everything back
	void UnChangeEncounters(const int _current_loc);
	void UnBanTheBridge(const int _current_loc);

	void DoStep(const int _current_loc);
	void UndoStep(const int _current_loc);

	

	void SolveBackTrack(int current_loc);
	void Solve();
public:
	Solver();
	Solver(GridMap& Map);

	bool CanBeSolved();
	std::vector<int> GetSolution();
};

