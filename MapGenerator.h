#pragma once
#include "Cell.h"
#include "GridMap.h"
#include "Solver.h"
class MapGenerator
{
public:
	GridMap start_map;
	//parametrs
	int size;
	int additional_islands_count=1;
	int keys_count=1;
	int additional_doors_count = 0;
	int bridges_count = 0; 

	//list of cells for generation:
	Cell water_cell;
	Cell basic_island;
	Cell island_with_key;
	Cell island_with_door;
	Cell bridge_2;
	Cell bridge_3;
	Cell bridge_4;
	Cell bridge_5;
	Cell bridge_6;
	Cell bridge_7;
	
	//list of additional vectors:
	
	//for generating islands:
	std::vector<GridMap> Islands_Result;
	
	//methods that belong to island generation will be started with "Islands"
	//for generating doors: 
	std::vector<std::vector<GridMap>> Doors_Result;
	//for generating keys: 
	std::vector<std::vector<GridMap>> Keys_Result;
	//for generating bridges:
	std::vector<std::vector<GridMap>> Bridges_Result;

	std::vector<GridMap> Final_Result;

public:
	MapGenerator(int _size, int _additional_islands_num, int _additional_doors_count, int _bridges_num);

	//global methods (suitible for every part of generation)

	void RemoveDuplicatesOneVector(std::vector<GridMap>& maps);
	void RemoveDuplicatesMultVectors(std::vector<std::vector<GridMap>>& Result_map_stacks);

	void VectorSolveCheck(std::vector<GridMap>& maps);

	//islands generation:
	std::vector<int> IslandsGetForbiddenTiles(int i, int size);
	void IslandsBackTrack(int* placed_island_count, std::vector<int>& forbidden, int island_num, int size, std::vector<GridMap>& res, Cell& island, GridMap& permutation);

	void IslandsGenerator();

	//doors generation:
	void DoorsBackTrack(int* placed_doors_count, int additional_doors_count, std::vector<GridMap>& res, GridMap& permutation, int size);
	std::vector<GridMap> DoorsGeneratorOneMap(GridMap& _Map);
	void DoorsGenerator();

	//keys generation:
	void KeysBackTrack(int* placed_keys_count, int keys_count, std::vector<GridMap>& res, GridMap& permutation, int size);
	std::vector<GridMap> KeysGeneratorOneMap(GridMap& _Map);
	void KeysGenerator();

	//bridges:
	void GetForbiddenTilesBridges(std::vector<int>& forbidden, GridMap& Map);
	void BridgesMakeIslandPairs(GridMap& Map, std::vector<std::pair<int, int>>& start_end_index);
	bool BridgesAbleToMove(const int _current_loc, const int _next_loc, const int size);
	void BridgesMakeVectorsStartEndAll(std::vector<int>& forbidden, int size, 
		std::vector<std::vector<int>>& res, std::vector<int>& permutation, const int _start, const int _end);

	std::vector<int> BridgesChooseVectorShortest(std::vector<std::vector<int>>& bridges);
	std::vector<int> BridgesBuildOneStartEndVector(std::vector<int>& forbidden, int size, int _start, int _end);

	void BridgesMakeBriedgeViewOneVector(std::vector<int>& briedge_coord, GridMap& Map, int size);
	GridMap BridgesMakeBridgeViewStack(GridMap& Map, std::vector<std::vector<int>>& bridge_pack);

	void BridgesBuildBridgesStacks(int* placed_bridges_count, int bridge_count, std::vector<std::pair<int, int>>& start_end_index, 
		std::vector<std::vector<std::vector<int>>>& res, std::vector<std::vector<int>>& permutation, std::vector<int>& forbidden, int size);

	std::vector<GridMap> BridgesGeneratorOneMap(GridMap& _Map);

	void BridgesGenerator();
	
	//Global Generation:
	//void GenerateMaps();
	void RemoveUnsolveble();
	void PrintGeneratedMaps();
	//std::vector<GridMap> GetResult();
};

