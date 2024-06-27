#include "MapGenerator.h"

MapGenerator::MapGenerator(int _size, int _additional_islands_count, int _additional_doors_count, int _bridges_num)
{
	size = _size;
	additional_islands_count = _additional_islands_count;
	additional_doors_count = _additional_doors_count;
	keys_count = additional_doors_count + 1;
	bridges_count = _bridges_num;
	Cell tmp_island(1);
	basic_island = tmp_island;
	Cell tmp_door(1);
	tmp_door.AddDoor();
	island_with_door = tmp_door;
	Cell tmp_key(1);
	tmp_key.AddKey();
	island_with_key = tmp_key;
	GridMap tmp_map(size);
	start_map.Resize(size);
	start_map.AddCell(&basic_island, 0);
	start_map.AddCell(&island_with_door, size * size - 1);

	Cell tmp_br_2(2);
	Cell tmp_br_3(3);
	Cell tmp_br_4(4);
	Cell tmp_br_5(5);
	Cell tmp_br_6(6);
	Cell tmp_br_7(7);

	bridge_2 = tmp_br_2;
	bridge_3 = tmp_br_3;
	bridge_4 = tmp_br_4;
	bridge_5 = tmp_br_5;
	bridge_6 = tmp_br_6;
	bridge_7 = tmp_br_7;
}



void MapGenerator::RemoveDuplicatesOneVector(std::vector<GridMap>& maps)
{
	int i = 0;
	int j;
	while (i < maps.size())
	{
		j = i + 1;
		while (j < maps.size())
		{
			if (maps[i] == maps[j]) {
				maps.erase(maps.begin() + j);
			}
			else { j++; }
		}
		i++;
	}
}

void MapGenerator::RemoveDuplicatesMultVectors(std::vector<std::vector<GridMap>>& v_maps)
{
	int start_pos = 0;
	int start_v = 0;
	int end_v = v_maps.size() - 1;
	int end_pos = v_maps[end_v].size() - 1;
	while(start_v < v_maps.size())
	{
		
	}
	
}

void MapGenerator::VectorSolveCheck(std::vector<GridMap>& maps)
{
	int n = 0;
	while (n < maps.size())
	{	
		std::cout<<"Making solver"<<n<<std::endl;
		Solver s(maps[n]);
		std::cout<<"Solver init complete"<<std::endl;
		if (s.CanBeSolved() == false)
		{
			std::cout<<"before erasing"<<std::endl;
			maps.erase(maps.begin()+n);
			std::cout<<"after erasing"<<std::endl;
		}
		else { n++; }
	}
}

//islands:
std::vector<int> MapGenerator::IslandsGetForbiddenTiles(int i, int size)
{
	std::vector<int> temp;
	//обработка углов:
	if (i == 0) {
		temp = { i ,i + 1,i + size };
		return temp;
	}
	if (i == size - 1) {
		temp = { i, i - 1, i + size };
		return temp;
	}
	if (i == size * size - 1) {
		temp = { i,i - 1,i - size };
		return temp;
	}
	if (i == size * size - size) {
		temp = { i,i + 1,i - size };
		return temp;
	}
	//обработка границ без углов:
	if (i > 0 && i < size - 1) {
		temp = { i,i - 1,i + 1,i + size };
		return temp;
	}
	if (i > (size * size - 1) && i < (size * size - 1)) {
		temp = { i,i - 1,i + 1,i - size };
		return temp;
	}
	if (i > 0 && i < (size * size - size) && i % size == 0) {
		temp = { i,i - size,i + size,i + 1 };
		return temp;
	}
	if (i > size - 1 && i < size * size - 1 && (i + 1) % size == 0) {
		temp = { i,i - size,i + size,i - 1 };
		return temp;
	}
	else {
		temp = { i,i + 1,i - 1,i + size,i - size };
		return temp;
	}
}

void MapGenerator::IslandsBackTrack(int* placed_island_count, std::vector<int>& forbidden, int island_num, int size, std::vector<GridMap>& res, Cell& island, GridMap& permutation)
{

	std::vector<int> temp_forbidden;
	if (*placed_island_count == island_num) {
		res.push_back(permutation);
		return;
	}
	for (int i = 0; i < size * size; i++) {
		if (std::find(begin(forbidden), end(forbidden), i) == end(forbidden)) {
			(*placed_island_count)++;
			permutation.AddCell(&island, i);
			temp_forbidden = IslandsGetForbiddenTiles(i, size);
			for (int k = 0; k < temp_forbidden.size(); k++) {
				forbidden.push_back(temp_forbidden[k]);
			}
			IslandsBackTrack(placed_island_count, forbidden, island_num, size, res, island, permutation);
			for (int k = 0; k < temp_forbidden.size(); k++) {
				forbidden.pop_back();
			}
			permutation.SetWater(i);
			(*placed_island_count)--;
		}
	}
}

void MapGenerator::IslandsGenerator()
{
	int placed_islands_count=0;
	std::vector<int> forbidden_tiles_islands;
	std::vector<int> temp_forbidden;
	temp_forbidden = IslandsGetForbiddenTiles(0, size);
	for (int k = 0; k < temp_forbidden.size(); k++) {
		forbidden_tiles_islands.push_back(temp_forbidden[k]);
	}
	temp_forbidden = IslandsGetForbiddenTiles(size * size - 1, size);
	for (int k = 0; k < temp_forbidden.size(); k++) {
		forbidden_tiles_islands.push_back(temp_forbidden[k]);
	}
	//вот тут, чтобы все "заработало" мы вроде делали копию карты, вот только если я тут копию сделаю у меня нахрен все удалится потом вне функции
	IslandsBackTrack(&placed_islands_count, forbidden_tiles_islands,additional_islands_count, size, Islands_Result,basic_island,start_map);
	for (int k = 0; k < Islands_Result.size(); k++) {
		Islands_Result[k].MakeSprite();
	}
	RemoveDuplicatesOneVector(Islands_Result);
}


//doors:

void MapGenerator::DoorsBackTrack(int* placed_doors_count, int additional_doors_count, std::vector<GridMap>& res, GridMap& permutation, int size)
{
	if (*placed_doors_count == additional_doors_count)
	{
		res.push_back(permutation);
		return;
	}
	for (int i = 1; i < size * size - 1; i++)
	{
		if (permutation.GetCellType(i) == 1 && permutation.IsIslandEmpty(i) == true)
		{
			(*placed_doors_count)++;
			permutation.SetDoor(i);

			DoorsBackTrack(placed_doors_count, additional_doors_count, res, permutation, size);

			(*placed_doors_count)--;
			permutation.RemoveDoor(i);
		}
	}

}

std::vector<GridMap> MapGenerator::DoorsGeneratorOneMap(GridMap& _Map)
{
	int placed_doors_count = 0;
	std::vector<GridMap> OneMapDoors_Result;
	DoorsBackTrack(&placed_doors_count, additional_doors_count,OneMapDoors_Result, _Map, size);
	for (int k = 0; k < OneMapDoors_Result.size(); k++) {
		OneMapDoors_Result[k].MakeSprite();
	}
	RemoveDuplicatesOneVector(OneMapDoors_Result);

	return OneMapDoors_Result;
}

void MapGenerator::DoorsGenerator()
{
	for (int k = 0; k < Islands_Result.size(); k++) {
		Doors_Result.push_back(DoorsGeneratorOneMap(Islands_Result[k]));
	}
}


//keys:

void MapGenerator::KeysBackTrack(int* placed_keys_count, int keys_count, std::vector<GridMap>& res, GridMap& permutation, int size)
{
	if (*placed_keys_count == keys_count) {
		res.push_back(permutation);
		return;
	}
	for (int i = 0; i < size * size-1; i++)
	{
		if (permutation.GetCellType(i) == 1 && permutation.IsIslandEmpty(i) == true) {
			(*placed_keys_count)++;
			permutation.SetKey(i);

			KeysBackTrack(placed_keys_count, keys_count, res, permutation, size);

			(*placed_keys_count)--;
			permutation.RemoveKey(i);
		}
	}
}

std::vector<GridMap> MapGenerator::KeysGeneratorOneMap(GridMap& _Map)
{
	int placed_keys_count = 0;
	std::vector<GridMap> OneMapKeys_Result;
	KeysBackTrack(&placed_keys_count, keys_count, OneMapKeys_Result, _Map, size);
	for (int k = 0; k < OneMapKeys_Result.size(); k++) {
		OneMapKeys_Result[k].MakeSprite();
	}
	RemoveDuplicatesOneVector(OneMapKeys_Result);

	return OneMapKeys_Result;

}

void MapGenerator::KeysGenerator()
{
	for (int k = 0; k < Doors_Result.size(); k++)
	{
		for (int j = 0; j < Doors_Result[k].size(); j++) {
			Keys_Result.push_back(KeysGeneratorOneMap(Doors_Result[k][j]));
		}
	}
}

//bridges:
void MapGenerator::GetForbiddenTilesBridges(std::vector<int>& forbidden, GridMap& Map)
{
	int size = Map.GetSize();
	for (int i = 0; i < size * size; i++) {
		if (Map.GetCellType(i) != 0) {
			forbidden.push_back(i);
		}
	}
}

void MapGenerator::BridgesMakeIslandPairs(GridMap& Map, std::vector<std::pair<int, int>>& start_end_index)
{
	int size = Map.GetSize();
	for (int i = 0; i < size * size; i++) {
		if (Map[i].GetType() == 1)
		{
			for (int j = i + 1; j < size * size; j++) {
				if (Map[j].GetType() == 1) {
					start_end_index.push_back(std::make_pair(i, j));
				}
			}
		}

	}
}

bool MapGenerator::BridgesAbleToMove(const int _current_loc, const int _next_loc, const int size) {
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

void MapGenerator::BridgesMakeVectorsStartEndAll(std::vector<int>& forbidden, int size, std::vector<std::vector<int>>& res, std::vector<int>& permutation, const int _start, const int _end)
{

	int current_loc = _start;
	int next_step[4] = { current_loc - 1, current_loc + 1, current_loc - size, current_loc + size };
	int previous_step[4] = { current_loc + 1, current_loc - 1, current_loc + size, current_loc - size };
	int previous_pos = current_loc;
	permutation.push_back(current_loc);

	if (permutation.size() != 0) {
		if (permutation[permutation.size() - 1] == _end) {
			res.push_back(permutation);
			return;
		}
	}

	for (int i = 0; i < 4; i++) {

		if (BridgesAbleToMove(current_loc, next_step[i], size) && std::find(begin(forbidden), end(forbidden), next_step[i]) == end(forbidden))
		{
			//permutation.push_back(next_step[i]);
			current_loc = next_step[i];
			forbidden.push_back(current_loc);

			BridgesMakeVectorsStartEndAll(forbidden, size, res, permutation, current_loc, _end);

			forbidden.pop_back();
			current_loc = previous_pos;//tyt problema
			permutation.pop_back();
		}

	}
}

std::vector<int> MapGenerator::BridgesChooseVectorShortest(std::vector<std::vector<int>>& bridges) {
	int min_length = bridges[0].size();
	int min_index = 0;
	for (int k = 0; k < bridges.size(); k++)
	{
		if (bridges[k].size() < min_length) {
			min_length = bridges[k].size();
			min_index = k;
		}
	}
	return bridges[min_index];
}

std::vector<int> MapGenerator::BridgesBuildOneStartEndVector(std::vector<int>& forbidden, int size, int _start, int _end)
{
	std::vector<std::vector<int>> all_possible_bridges;
	std::vector<int> one_of_possible_bridges;
	std::vector<int> the_shortest_bridge;

	BridgesMakeVectorsStartEndAll(forbidden, size, all_possible_bridges, one_of_possible_bridges, _start, _end);
	if (all_possible_bridges.size() == 0) {
		return std::vector<int>();
	}
	else {
		the_shortest_bridge = BridgesChooseVectorShortest(all_possible_bridges);

		return the_shortest_bridge;
	}
	
}



void MapGenerator::BridgesBuildBridgesStacks(int* placed_bridges_count, int bridge_count, std::vector<std::pair<int, int>>& start_end_index, std::vector<std::vector<std::vector<int>>>& res, std::vector<std::vector<int>>& permutation, std::vector<int>& forbidden, int size)
{
	std::vector<int> forbidden_use;
	std::vector<int>bridge;
	if (*placed_bridges_count == bridge_count) {
		res.push_back(permutation);
		return;
	}
	for (int i = 0; i < start_end_index.size(); i++) {
		int start = start_end_index[i].first;
		int end = start_end_index[i].second;
		forbidden_use = forbidden;
		
		if (permutation.size() > 0) {
			for (int k = 0; k < permutation.size(); k++)
			{
				for (int j = 0; j < permutation[k].size(); j++)
				{
					forbidden_use.push_back(permutation[k][j]);
				}
			}
		}
		while (std::find(forbidden_use.begin(), forbidden_use.end(), end) != forbidden_use.end()) {
			forbidden_use.erase(find(forbidden_use.begin(), forbidden_use.end(), end));
		}

		bridge = BridgesBuildOneStartEndVector(forbidden_use, size, start, end);
		forbidden_use.push_back(end);
		if (bridge.size() != 0) {
			permutation.push_back(bridge);
			
			(*placed_bridges_count)++;

			BridgesBuildBridgesStacks(placed_bridges_count, bridge_count, start_end_index, res, permutation, forbidden, size);

			permutation.pop_back();

			(*placed_bridges_count)--;
		}
		

	}
}

void MapGenerator::BridgesMakeBriedgeViewOneVector(std::vector<int>& briedge_coord, GridMap& Map, int size)
{
	//v[0] - остров, с которого начинаем идти
	// v[size-1] - остров, в который приходим
	for (int k = 1; k < briedge_coord.size() - 1; k++) {
		if ((briedge_coord[k] - briedge_coord[k - 1] == 1 && briedge_coord[k] - briedge_coord[k + 1] == -1) || (briedge_coord[k] - briedge_coord[k - 1] == -1 && briedge_coord[k] - briedge_coord[k + 1] == 1)) {
			Map.AddCell(&bridge_2, briedge_coord[k]);
		}
		else if ((briedge_coord[k] - briedge_coord[k - 1] == -size && briedge_coord[k] - briedge_coord[k + 1] == size) || (briedge_coord[k] - briedge_coord[k - 1] == size && briedge_coord[k] - briedge_coord[k + 1] == -size)) {
			Map.AddCell(&bridge_3, briedge_coord[k]);
		}
		else if ((briedge_coord[k] - briedge_coord[k - 1] == size && briedge_coord[k] - briedge_coord[k + 1] == 1) || (briedge_coord[k] - briedge_coord[k - 1] == 1 && briedge_coord[k] - briedge_coord[k + 1] == size)) {
			Map.AddCell(&bridge_4, briedge_coord[k]);
		}
		else if ((briedge_coord[k] - briedge_coord[k - 1] == 1 && briedge_coord[k] - briedge_coord[k + 1] == -size) || (briedge_coord[k] - briedge_coord[k - 1] == -size && briedge_coord[k] - briedge_coord[k + 1] == 1)) {
			Map.AddCell(&bridge_5, briedge_coord[k]);
		}
		else if ((briedge_coord[k] - briedge_coord[k - 1] == size && briedge_coord[k] - briedge_coord[k + 1] == -1) || (briedge_coord[k] - briedge_coord[k - 1] == -1 && briedge_coord[k] - briedge_coord[k + 1] == size)) {
			Map.AddCell(&bridge_6, briedge_coord[k]);
		}
		else if ((briedge_coord[k] - briedge_coord[k - 1] == -size && briedge_coord[k] - briedge_coord[k + 1] == -1) || (briedge_coord[k] - briedge_coord[k - 1] == -1 && briedge_coord[k] - briedge_coord[k + 1] == -size)) {
			Map.AddCell(&bridge_7, briedge_coord[k]);
		}
		else { std::cerr << "Unable to make a briedge!" << std::endl; }
	}
}

GridMap MapGenerator::BridgesMakeBridgeViewStack(GridMap& Map, std::vector<std::vector<int>>& bridge_pack)
{
	GridMap Map_1 = Map;
	for (int k = 0; k < bridge_pack.size(); k++)
	{
		BridgesMakeBriedgeViewOneVector(bridge_pack[k], Map_1, size);
	}
	return Map_1;
}

std::vector<GridMap> MapGenerator::BridgesGeneratorOneMap(GridMap& _Map)
{
	std::vector<std::pair<int, int>> IslandPairs;

	BridgesMakeIslandPairs(_Map, IslandPairs);
	
	std::vector<int>forbidden_tiles;
	GetForbiddenTilesBridges(forbidden_tiles, _Map);
	
	
	int placed_bridges_num = 0;
	std::vector<std::vector<std::vector<int>>> result_bridges_packs;
	std::vector<std::vector<int>> permutation_bridges;
	BridgesBuildBridgesStacks(&placed_bridges_num, bridges_count, IslandPairs, result_bridges_packs, permutation_bridges, forbidden_tiles, size);

	std::vector<GridMap> OneMap_Bridges;

	for (int k = 0; k < result_bridges_packs.size(); k++) {
		for (int i = 0; i < result_bridges_packs[k].size(); i++)
		{
			OneMap_Bridges.push_back(BridgesMakeBridgeViewStack(_Map, result_bridges_packs[k]));
		}
	}
	RemoveDuplicatesOneVector(OneMap_Bridges);
	return  OneMap_Bridges;
}



void MapGenerator::BridgesGenerator()
{
	std::vector<GridMap> temp_vector;
	for (int k = 0; k < Keys_Result.size(); k++)
	{
		for (int j = 0; j < Keys_Result[k].size(); j++)
		{
			temp_vector = BridgesGeneratorOneMap(Keys_Result[k][j]);
			if (temp_vector.size() > 0) {
				Bridges_Result.push_back(temp_vector);
			}
		}
	}
}

void MapGenerator::RemoveUnsolveble()
{
	for (int k = 0; k < Bridges_Result.size(); k++)
	{
		std::cout<<"Remove "<<k<<std::endl;
		VectorSolveCheck(Bridges_Result[k]);
	}
}

void MapGenerator::PrintGeneratedMaps()
{
	std::cout << "After generating bridges" << std::endl;
	if(Bridges_Result.size() == 0) {std::cout<<"please stop this"<<std::endl;}
	for (int i = 0; i < Bridges_Result.size(); i++)
	{
		std::cout << "Bridge stack num " << i << " :" << std::endl;
		for (int k = 0; k < Bridges_Result[i].size(); k++)
		{
			std::cout << "Bridge map num " << k << " :" << std::endl;
			Bridges_Result[i][k].MakeSprite();
			Bridges_Result[i][k].Draw();
			
		}
	}
	
}

/*void MapGenerator::GenerateMaps()
{
	DoorsGenerator();
	KeysGenerator();
	BridgesGenerator();
	RemoveUnsolveble();
	
}

std::vector<GridMap> MapGenerator::GetResult()
{
	return Final_Result;
}*/
