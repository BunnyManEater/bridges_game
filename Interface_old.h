#pragma once
#include <ncurses.h>
#include"GridMap.h"
#include <vector>
#include <string>

struct Menu {
	std::vector<std::string> choices;
	int y_size;
	int x_size;
	int y_loc;
	int x_loc;

	Menu() : y_size(0), x_size(0), y_loc(0), x_loc(0) {};
	Menu(std::vector<std::string> _ch, int _y_s, int _x_s, int _y_l, int _x_l) : choices(_ch), y_size(_y_s), x_size(_x_s), y_loc(_y_l), x_loc(_x_l) {};
};

class Interface {
private:
	WINDOW* screen; //инициализация стандартного экрана, который всегда существует (чтобы термминал не просвечивал)
	Menu main_menu;
	Menu size_menu;
	Menu diff_menu;
public:
	Interface();
	Interface(WINDOW*);

	int showMenu(Menu& _menu);
	int showMain();
	int showSize();
	int showDiff();

	WINDOW* getWin(); //чтобы получить доступ к окну

	void showRules();
	std::pair<int, std::pair<int, int>> showGrid(GridMap& board, std::pair<int, int>& curr_pos); //отрисовка поля
	//первый инт - значение, которое вводтися, второе - где (мне не нужно) но внутри шоу грида взять стрелочки остальное в утиль (он ничего возращать не будет)

};


