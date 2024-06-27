#include "Interface.h"


Interface::Interface() : screen(nullptr) {}

Interface::Interface(WINDOW* _screen) {
	screen = _screen;
	std::vector<std::string> main_choices = { "Play", "Rules", "Quit" };
	int x, y;
	getmaxyx(screen, y, x); //функция ncurses которая возвращает макс размер экрана
	Menu _main(main_choices, main_choices.size() + 2, 20, (y - main_choices.size() + 2) / 2, (x - 20) / 2);
	main_menu = _main;

	std::vector<std::string> level_choices = { "Level 1", "Level 2","Level 3","Level 4","Level 5", "Level 6", "Quit" };
	
	Menu _levels(level_choices, level_choices.size() + 2, 20, (y - level_choices.size() + 2) / 2, (x - 20) / 2);
	level_menu = _levels;


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

int Interface::showLevels() {
	clear();
	return showMenu(level_menu);
}

WINDOW* Interface::getWin() {
	return screen;
}



int Interface::showGrid(GridMap& Map, int curr_x, int curr_y) {

	cbreak();
	refresh();
	int board_size = Map.GetSize() * Map.GetSizeCell();
	
	int y_loc, x_loc;
	getmaxyx(screen, y_loc, x_loc);

	WINDOW* gridwin = subwin(screen, board_size + 2, board_size+2, (y_loc - board_size) / 2, (x_loc - board_size) / 2);
	box(gridwin, 0, 0);
	wborder(gridwin, 124, 124, 45, 45, 43, 43, 43, 43);

	keypad(gridwin, true);
	int choice;
	std::pair<int, int> highlight;
	
	highlight = std::make_pair(curr_x,curr_y);

	int end = 0;

	
	 for (int i = 0; i < board_size*board_size; ++i) {
		    if (i/board_size == highlight.first && i%board_size == highlight.second) {
					wattron(gridwin, A_REVERSE);
				}


		mvwprintw(gridwin,i/board_size +1, i%board_size +1,"%c",Map.GetSpriteChar(i));
		wattroff(gridwin,A_REVERSE);
	    }
		
	choice = wgetch(gridwin);

	
	clear();
	refresh();
	return choice;	
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
	mvwprintw(rules, 5, 32, "CONGRATULATIONS! You have passed the level!");
	
	mvwprintw(rules, 10, 1, "Press any key to go back to main menu");
	wrefresh(rules);
	wgetch(rules);
	clear();
}
