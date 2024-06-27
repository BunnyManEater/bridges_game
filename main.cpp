#include "Cell.h"
#include "GridMap.h"
#include "Solver.h"
#include "MapGenerator.h"
#include "Interface.h"
#include "Game.h"
//#include<fstream>
//#include <sstream>
//#include <experimental/filesystem>
//#include <string>

//namespace fs = std::experimental::filesystem;

int main() {
//std::string maps_path = ".maps";
//generating maps:
	//testing the Generator
/*
	MapGenerator gen_1(3,2,0,4);
	GridMap test_start_map = gen_1.start_map;
	std::cout << test_start_map.GetSize() << std::endl;
	test_start_map.MakeSprite(); //It breaks here for some reason 
	test_start_map.Draw();
	std::cout<<"Ah yes"<<std::endl;
	//test_start_map.Draw();
	gen_1.IslandsGenerator();
	//gen_1.PrintGeneratedMaps();
	std::cout<<"Ah no"<<std::endl;
	gen_1.DoorsGenerator();
	std::cout<<"Doors generated"<<std::endl;
	gen_1.KeysGenerator();
	std::cout<<"Keys Generated"<<std::endl;
	gen_1.BridgesGenerator();
	std::cout<<"And bridges"<<std::endl;
	gen_1.RemoveUnsolveble();
	std::cout<<"And removed"<<std::endl;
	gen_1.PrintGeneratedMaps();
*/
/*result_maps_1 = gen_1.GetResult();

std::cout<<result_maps_1.size()<<std::endl;

MapGenerator gen_2(3,3,0,5);
gen_2.GenerateMaps();
std::vector<GridMap> result_maps_2;
result_maps_2 = gen_2.GetResult();

std::vector<std::vector<GridMap>> all_maps;
all_maps.push_back(result_maps_1);
all_maps.push_back(result_maps_2);
//generating maps

	//setting up a testing map
int level_num = 2;
if(!fs::exists(maps_path)){
		fs::create_directory(maps_path);
}
for (int i=0; i<level_num;i++)
{
	fs::path dirpath1 = maps_path + "/"+ std::to_string(i+1);
	if(!fs::exists(dirpath1)){
		fs::create_directory(dirpath1);
	}
	for (int k=0; k<all_maps[i].size();k++)
	{
		fs::path taskpath = maps_path + "/" + std::to_string(i+1) + "/" + std::to_string(k+1);
		all_maps[i][k].SaveToFile(taskpath);
	}
}*/
//	Game game_test;
//	game_test.game();	
	//generating maps:
	//testing the Generator
	MapGenerator gen_1(3,1,0,3);
	GridMap test_start_map = gen_1.start_map;
	std::cout << test_start_map.GetSize() << std::endl;
	test_start_map.MakeSprite(); //It breaks here for some reason 
	test_start_map.Draw();
	//test_start_map.Draw();
	gen_1.IslandsGenerator();
	std::cout<<"I got at least here"<<std::endl;
	//gen_1.PrintGeneratedMaps();
	gen_1.DoorsGenerator();
	gen_1.KeysGenerator();
	gen_1.BridgesGenerator();
	std::cout<<"i got here yey"<<std::endl;
	gen_1.RemoveUnsolveble();
	std::cout<<"I got here"<<std::endl;
	gen_1.PrintGeneratedMaps();
	

	return 0;
}
