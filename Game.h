#pragma once

#include "Interface.h"
#include "MapGenerator.h"
class Game {
private:

	//MapGenerator game_gen;
	Interface gameint;

public:
	Game();
	void game();
	GridMap InitLevel(int level);
	void session(); //игровой цикл без менюшек и т д 
	bool CheckIfOnTrack(GridMap& Map, int _curr_x, int _curr_y, int _next_x, int _next_y);
	bool CheckStep(GridMap& Map, int _curr_x, int _curr_y, int _next_x, int _next_y, int eq_k);
	void ChangeMapCurr(GridMap& Map, int curr_x, int curr_y, int* eq_keys);
	void ChangeMapPrev(GridMap& Map, int prev_x, int prev_y, int cirr_x, int curr_y);
	bool CheckWinCase(GridMap& Map,int pos_x, int pos_y,int* eq_keys);
	//void setGen();
};
