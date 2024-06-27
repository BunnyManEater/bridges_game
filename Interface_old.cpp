#include "Interface.h"

Interface::Interface() : screen(nullptr) {}

Interface::Interface(WINDOW* _screen) {
	screen = _screen;
	std::vector<std::string> main_choices = { "Play", "Rules", "Quit" };
	int x, y;
	getmaxyx(screen, y, x); //функция ncurses которая возвращает макс размер экрана
	Menu _main(main_choices, main_choices.size() + 2, 20, (y - main_choices.size() + 2) / 2, (x - 20) / 2);
	main_menu = _main;

	std::vector<std::string> size_choices = { "4x4", "9x9", "16x16", "Back" };
	Menu _size(size_choices, size_choices.size() + 2, 20, (y - size_choices.size() + 2) / 2, (x - 20) / 2);
	size_menu = _size;

	std::vector<std::string> diff_choices = { "Beginner", "Easy", "Normal", "Hard","Back" };
	Menu _diff(diff_choices, diff_choices.size() + 2, 20, (y - size_choices.size() + 2) / 2, (x - 20) / 2);
	diff_menu = _diff;
}


int Interface::showMenu(Menu& _menu) {
	cbreak();//они вроде ничего не делают, но можно оставить спокойно
	refresh();//

	WINDOW* menuwin = subwin(screen, _menu.y_size, _menu.x_size, _menu.y_loc, _menu.x_loc);//создание подокна
	box(menuwin, 0, 0); //граница
	wborder(menuwin, 124, 124, 45, 45, 43, 43, 43, 43);//границы палочками
	wrefresh(menuwin); //применение настроек

	keypad(menuwin, true);//включает системные клавиши (в том числе стрелочки)
	int choice; //переменная для хранения клавиши, которую нажимает пользователь
	int highlight = 0; //тот вариант, который надо подсвечивать в менюшке (текущее положение)
	while (1) {
		for (int i = 0; i < _menu.choices.size(); ++i) {
			if (i == highlight) {
				wattron(menuwin, A_REVERSE); //инввертирование window attribute on 
			}
			mvwprintw(menuwin, i + 1, 1, _menu.choices[i].c_str());//move window print то есть окно + курсор и куда перенести
			wattroff(menuwin, A_REVERSE); //выключить атрибут
		}
		choice = wgetch(menuwin);//кладу то, что нажал человек

		switch (choice) {
		case KEY_UP:
		case 'w':
			highlight--;
			if (highlight == -1) {
				highlight = 0;
			}
			break;
		case KEY_DOWN:
		case 's':
			highlight++;
			if (highlight == _menu.choices.size()) {
				highlight = _menu.choices.size() - 1;
			}
			break;
		default:
			break;
		}
		if (choice == 10) {//10 - энтр
			break;
		}
	}
	clear();//системное не трогать
	refresh(); //системное не трогать
	return highlight;//возвращение выбранной опции
}

int Interface::showMain() {
	clear();
	return showMenu(main_menu);
}

int Interface::showSize() {
	mvwprintw(screen, size_menu.y_loc - 1, size_menu.x_loc, "Choose the board size");
	return showMenu(size_menu);
}

int Interface::showDiff() {
	mvwprintw(screen, diff_menu.y_loc - 1, diff_menu.x_loc, "Choose the difficulty");
	return showMenu(diff_menu);
}

WINDOW* Interface::getWin() {
	return screen;
}


std::pair<int, std::pair<int, int>> Interface::showGrid(GridMap& Map, std::pair<int, int>& curr_pos) {
	cbreak();//системное не убирать
	refresh();//системное не убирать
	int board_size = Map.GetSize() * Map.GetSizeCell();
	int grid_size = board_size * board_size;
	int y_loc, x_loc;
	getmaxyx(screen, y_loc, x_loc);

	WINDOW* gridwin = subwin(screen, grid_size + Map.GetSize() + 1, 2 * grid_size + 1, (y_loc - grid_size) / 2, (x_loc - 2 * grid_size) / 2);
	box(gridwin, 0, 0);
	wborder(gridwin, 124, 124, 45, 45, 43, 43, 43, 43);

	keypad(gridwin, true);
	int choice;
	std::pair<int, int> highlight;
	highlight = std::make_pair(curr_pos.first, curr_pos.second);

	std::pair<int, std::pair<int, int>>  prev;
	int end = 0;
	//вот тут я дописываю параметры:

	while (1) {
		for (int i = 0; i < grid_size; ++i) {//отрисовка игрового поля и все
			for (int j = 0; j < grid_size; ++j) {
				wmove(gridwin, 0, 0);
				if (i == highlight.first && j == highlight.second) {
					wattron(gridwin, A_REVERSE);
				}

				mvwprintw(gridwin, i + i / board_size + 1, 2 * j + 1,std::to_string( Map.GetSpriteChar(i*board_size+j)).c_str());

			}
		}
		choice = wgetch(gridwin);//оставляем (возвращает клавишу, которую нажал чел)

		switch (choice) {
		case KEY_UP:
			highlight.first--;
			if (highlight.first == -1) {
				highlight.first = 0;
			}
			break;
		case KEY_DOWN:
			highlight.first++;
			if (highlight.first == grid_size) {
				highlight.first = grid_size - 1;
			}
			break;
		case KEY_LEFT:
			highlight.second--;
			if (highlight.second == -1) {
				highlight.second = 0;
			}
			break;
		case KEY_RIGHT:
			highlight.second++;
			if (highlight.second == grid_size) {
				highlight.second = grid_size - 1;
			}
			break;
		default:
			prev = std::make_pair(choice, highlight);//чтобы позиция не сбрасывалась (мне наверное надо, если буду меню вызывать, но наверное нет)
			end = 1;
			break;
		}
		if (end == 1) {//просто доска заново отрисуется, если было нажато что-то кроме стрелочек
			break;
		}
	}
	clear();
	refresh();
	return prev; //возвращаешь prev потому что его стравнивают с решенной задачей (это мне не надо) 
}

void Interface::showRules() {
	int x, y;
	getmaxyx(screen, y, x);

	WINDOW* rules = subwin(screen, 20, 70, (y - 20) / 2, (x - 70) / 2);
	box(rules, 0, 0);
	wborder(rules, 124, 124, 45, 45, 43, 43, 43, 43);
	wrefresh(rules);
	mvwprintw(rules, 1, 32, "Rules");
	mvwprintw(rules, 2, 1, "*Your goal is to reach the door at the left bootom");
	mvwprintw(rules, 3, 1, "*To open the doors you need keys");
	mvwprintw(rules, 4, 1, "*Collect the keys on the level");
	mvwprintw(rules, 5, 1, "*The Islands are stable, but the bridges are fragile");
	mvwprintw(rules, 6, 1, "*Every time you pass throug a bridge, it breaks");

	mvwprintw(rules, 10, 1, "Press any key to go back to main menu");
	wrefresh(rules);
	wgetch(rules);
	clear();
}

void Interface::showCongrat(){
	int x, y;
	getmaxyx(screen, y, x);

	WINDOW* rules = subwin(screen, 20, 70, (y - 20) / 2, (x - 70) / 2);
	box(rules, 0, 0);
	wborder(rules, 124, 124, 45, 45, 43, 43, 43, 43);
	wrefresh(rules);
	mvwprintw(rules, 1, 32, "CONGRATULATIONS! YOU WON!");
	
	mvwprintw(rules, 10, 1, "Press any key to go back to main menu");
	wrefresh(rules);
	wgetch(rules);
	clear();
}
