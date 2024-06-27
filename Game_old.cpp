#include "Game.h"
GameSettings::GameSettings() : boardSize(0), difficulty(0){}

GameSettings::GameSettings(int _size, int _diff) {};


Game::Game() {
	initscr(); //оставляем инициализируем экран
	noecho(); //чтобы у меня не дублировалось на экран ничего лишнего
	curs_set(0); //курсор не виден

	Interface temp(stdscr); //надо инициализация стандартного экрана
	gameint = temp;
}

void Game::setSettings(int _size, int _diff) {
	GameSettings temp(_size, _diff);
	settings = temp;
}

int getMapIndexFromPos(int pos_x, int pos_y)
{
   return ( pos_y/Map.GetSizeCell())*Map.GetSize() + pos_x/Map.GetSizeCell();
}

bool CheckWinCase(int current_pos_x, current_pos_y)
{
		
}

void Game::game() { //оставляем как есть
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
			break;
		case 2:
			clear();
			gameint.showRules();
			break;
		case 3:
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

void Game::session() {
	int choice;
	bool end = 0;
	int _size;
	int difficulty;
	choice = gameint.showSize();
	switch (choice) {
	case 0:
		clear();
		_size = 2;
		break;
	case 1:
		clear();
		_size = 3;
		break;
	case 2:
		clear();
		_size = 4;
		break;
	case 3://квит
		end = 1;
		break;
	default:
		break;
	}
	if (end)
		return;
	else {
		choice = gameint.showDiff();//с выбором сложности
		switch (choice) {
		case 0:
			clear();
			difficulty = 0;
			break;
		case 1:
			clear();
			difficulty = 1;
			break;
		case 2:
			clear();
			difficulty = 2;
			break;
		case 3:
			clear();
			difficulty = 3;
			break;
		case 4:
			clear();
			difficulty = 4;
			break;
		case 5:
			clear();
			difficulty = 5;
			break;
		case 6:
			end = 1;
			break;
		default:
			break;
		}
	}

	if (end)
		return;


	this->setSettings(_size, difficulty);

	wclear(gameint.getWin());
	std::pair<int, std::pair<int, int>> move;
	std::pair<int, int> curr_pos;
	curr_pos = std::make_pair(0, 0);
	
	while (!(board == solution)) {//пока голооволомка не решена
		mvwprintw(gameint.getWin(), 0, 0, "Mistakes: %d/%d", 2, 2);//постоянная справочная инфа

		mvwprintw(gameint.getWin(), y_max - 3, 0, "Use arrows to move");

		mvwprintw(gameint.getWin(), y_max - 1, 0, "q - quit to main menu");
		move = gameint.showGrid(board, curr_pos);
		if (move.first == 'q') {
			return;
		}
		else if (dec(move.first) > 0 && dec(move.first) <= settings.boardSize * settings.boardSize && board[move.second.first][move.second.second] == 0) {
			if (dec(move.first) == solution[move.second.first][move.second.second]) {
				board.change(move.second.first, move.second.second, dec(move.first));
	
			}

		}
		else {
		
		}

		curr_pos = move.second;
	}
	if (board == solution) {
	
	
		}
	}
	else if (end) {
		gameint.showMessage("OOOPS.Too many mistakes!");
	}
	
}

