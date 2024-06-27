#pragma once

#include "Interface.h"

struct GameSettings { //это наверное оставляем
	int boardSize;
	int difficulty;

	GameSettings();
	GameSettings(int _size, int _diff);
};


class Game {
private:
	GameSettings settings;

	Interface gameint;

	std::string problems_path = ".problems";//оставляем

public:
	Game();
	void game();
	void session(); //игровой цикл без менюшек и т д 
	void setSettings(int _size, int _diff); //утсановка настроек
	void setGen(); //настройка генератора (в зависимости от размера и сложности) (надо)

};
