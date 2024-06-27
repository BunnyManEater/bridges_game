#include "Game.h"

Game::Game() {
	initscr(); //оставляем инициализируем экран
	noecho(); //чтобы у меня не дублировалось на экран ничего лишнего
	curs_set(0); //курсор не виден

	Interface temp(stdscr); //надо инициализация стандартного экрана
	gameint = temp;
}

void Game::game() { 
	int choice;
	bool end = 0;
	int del = 0;
	while (1) {
		choice = gameint.showMain();
		switch (choice) {
		case 0://из выбора менюшки
			clear();
			this->session();
			break;
		case 1:
			clear();
			gameint.showRules();
			break;
		case 2:
			end = 1;
			break;
		default:
			break;
		}
		if (end)
			break;
	}
	endwin();
}

bool Game::CheckIfOnTrack(GridMap& Map, int _curr_x, int _curr_y, int _next_x, int _next_y)
{
	if(_next_x !=_curr_x)//moving gorizontally
	{
		if(_curr_x%Map.GetSizeCell() == 1){return true;}
		else{return true;}
	}
	if(_next_y != _curr_y){
		if(_curr_y%Map.GetSizeCell() == 1) {return true;}
		else{return true;}
	}
	
}

bool Game::CheckStep(GridMap& Map, int _curr_x, int _curr_y, int _next_x, int _next_y, int eq_keys)
{
	int curr_map_index =( _curr_y/Map.GetSizeCell())*Map.GetSize() + _curr_x/Map.GetSizeCell();
	int next_map_index =(_next_y/Map.GetSizeCell())*Map.GetSize()+_next_x/Map.GetSizeCell();

	 if(CheckIfOnTrack(Map,_curr_x,_curr_y,_next_x,_next_y)==true)
	     { if(curr_map_index == next_map_index){ return true;}
		else {
			if(Map.IsMovePossible(curr_map_index,next_map_index,eq_keys)==true)
			{ return true;}
			else {return false;}
	
		}
	     }
	else{return false;}
}

void Game::ChangeMapPrev(GridMap& Map, int prev_x, int prev_y, int curr_x, int curr_y)
{
	int curr_map_ind = (curr_y/Map.GetSizeCell())*Map.GetSize()+curr_x/Map.GetSizeCell();
	int prev_map_ind = (prev_y/Map.GetSizeCell())*Map.GetSize()+prev_x/Map.GetSizeCell();
	if(curr_map_ind == prev_map_ind){ return;}
	else{
		if(Map.GetCellType(prev_map_ind)!=1)
		{
			Map.SetWater(prev_map_ind);
		}
	}



}

void Game::ChangeMapCurr(GridMap& Map, int pos_x, int pos_y, int* eq_keys)//i will change only prev cells
{
	int map_index = (pos_y/Map.GetSizeCell())*Map.GetSize()+pos_x/Map.GetSizeCell();
	if(Map.GetCellType(map_index) !=0 && Map.GetCellType(map_index) !=1)
	{
	

	}
	else if(Map.GetCellType(map_index) == 1)
	{
		if(Map.HasKey(map_index) == true)
		{
				(*eq_keys)++;
				Map.RemoveKey(map_index);}
					
		if(Map.HasDoor(map_index) == true)
		{
			
			(*eq_keys)--;	
			Map.RemoveDoor(map_index);
		}
		
	}
	Map.MakeSprite();
}

bool Game::CheckWinCase(GridMap& Map,int pos_x, int pos_y, int* eq_keys)
{
	int map_index = (pos_y/Map.GetSizeCell())*Map.GetSize()+pos_x/Map.GetSizeCell();
	if(map_index == Map.GetSize()*Map.GetSize()-1)
	{
		if(*eq_keys>0){
			return true;
		}
	}
	else {return false;}
}

GridMap Game::InitLevel(int level)
{
	GridMap map_1(2);
	return map_1;
}

void Game::session() {

	GridMap Play_Map(4);
	GridMap Play_2(4);
	
	Cell start_island_2(1);
	Cell end_island_2(1);
	Play_2.AddCell(&start_island_2, 0, 0);
	Play_2.AddCell(&end_island_2, 3, 3);
	Play_2.SetDoor(15);
	Cell Middle_island_1_2(1);
	Cell Middle_island_2_2(1);
	Cell Middle_island_3_2(1);
	
	Play_2.AddCell(&Middle_island_1_2, 3);
	Play_2.AddCell(&Middle_island_2_2, 12);
	Play_2.AddCell(&Middle_island_3_2,9);
	Play_2.SetKey(3);
	Play_2.SetKey(12);
	

	Cell br_1_2(2);
	Play_2.AddCell(&br_1_2, 1);
	Play_2.AddCell(&br_1_2,2);
	Cell br_2_2(5);
	Cell br_3_2(3);
	Play_2.AddCell(&br_3_2, 4);
	Play_2.AddCell(&br_3_2, 8);
	
	Play_2.AddCell(&br_3_2, 7);
	Play_2.AddCell(&br_3_2, 11);
	Cell br_4_2(4);
	Cell br_5_2(7);
	Play_2.AddCell(&br_4_2, 13);
	Cell br_6_2(6);
	Cell br_7_2(2);
	Play_2.AddCell(&br_6_2,14);
	Play_2.AddCell(&br_2_2, 10);
	Play_2.MakeSprite();






	GridMap Play_1(4);
	Cell start_island(1);
	Cell end_island(1);
	Play_1.AddCell(&start_island, 0, 0);
	Play_1.AddCell(&end_island, 3, 3);
	Play_1.SetDoor(15);
	Cell Middle_island_1(1);
	Cell Middle_island_2(1);
	
	Play_1.AddCell(&Middle_island_1, 2, 0);
	Play_1.AddCell(&Middle_island_2, 1, 2);
	Play_1.SetKey(9);

	Cell br_1(2);
	Play_1.AddCell(&br_1, 1, 0);
	Cell br_2(5);
	Cell br_3(3);
	Play_1.AddCell(&br_2, 3);
	Play_1.AddCell(&br_3, 7);
	Play_1.AddCell(&br_3, 11);
	Cell br_4(4);
	Cell br_5(7);
	Play_1.AddCell(&br_4, 6);
	Play_1.AddCell(&br_5, 5);
	Cell br_6(6);
	Cell br_7(2);
	Play_1.AddCell(&br_6,13);
	Play_1.AddCell(&br_7, 14);
	Play_1.MakeSprite();

	int eq_keys = 0;
	int choice;
	bool end = 0;
	int level;	
	choice = gameint.showLevels();
	switch (choice) {
	case 0:
		clear();
		
		level = 1;
		break;
	case 1:
		clear();
		
		level = 2;
		break;
	case 2:
		level = 3;
		break;
	case 3:
		level = 4;
		break;
	case 4:
		level = 5;
		break;
	case 5:
		level = 6;
		break;
	case 7:
		end = 1;
		break;
	default:
		break;
	}
	if (end)
		return;
	
	int y_max;
	int x_max;
	getmaxyx(gameint.getWin(),y_max,x_max);
	wclear(gameint.getWin());
	
	mvwprintw(gameint.getWin(), 0, 0, "Eqipted Keys: %d",eq_keys );

	mvwprintw(gameint.getWin(), y_max - 3, 0, "Use arrows to move");

	mvwprintw(gameint.getWin(), y_max - 1, 0, "q - quit to main menu");
	
	int prev_x = 1;
	int prev_y = 1;
	int curr_x = 1;
	int curr_y = 1;
	int next_x = 1;
	int next_y = 1;
	
	int board_size = Play_Map.GetSize()*Play_Map.GetSizeCell();
	while(CheckWinCase(Play_Map, curr_x, curr_y,&eq_keys) == false){
		choice = gameint.showGrid(Play_Map,curr_y, curr_x);
		mvwprintw(gameint.getWin(), 0, 0, "Eqipted Keys: %d",eq_keys );

		mvwprintw(gameint.getWin(), y_max - 3, 0, "Use arrows to move");

		mvwprintw(gameint.getWin(), y_max - 1, 0, "q - quit to main menu");
		switch (choice) {
			case KEY_UP:
				next_y = curr_y-1;
				next_x = curr_x;
				if (next_y == -1) {
					next_y = 0;
				}
				break;
			case KEY_DOWN:
				next_y = curr_y+1;
				next_x = curr_x;
				if (next_y  == board_size) {
					next_y = board_size - 1;
				}
				break;
			case KEY_LEFT:
				next_x = curr_x-1;
				next_y = curr_y;
				if (next_x == -1) {
					next_x = 0;
				}
				break;
			case KEY_RIGHT:
				next_x = curr_x +1;
				next_y = curr_y;
				if (next_x == board_size) {
					next_x = board_size -1;
				}
				break;
			case 'q':
				end =1;
				break;
			default:
			
				break;

			}
		if(end == 1){break;}
		if(CheckStep(Play_Map,curr_x, curr_y, next_x, next_y,eq_keys) == true)
		{
			prev_x = curr_x;
			prev_y = curr_y;
			curr_x = next_x;
			curr_y = next_y;
			ChangeMapCurr(Play_Map,curr_x, curr_y,&eq_keys);
			ChangeMapPrev(Play_Map,prev_x,prev_y, curr_x, curr_y);

		}
				}
	if(CheckWinCase(Play_Map, curr_x, curr_y,&eq_keys) == true){	gameint.showCongrat();}


			
			
}
