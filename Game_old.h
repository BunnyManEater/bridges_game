#pragma once

#include "Interface.h"

struct GameSettings { //��� �������� ���������
	int boardSize;
	int difficulty;

	GameSettings();
	GameSettings(int _size, int _diff);
};


class Game {
private:
	GameSettings settings;

	Interface gameint;

	std::string problems_path = ".problems";//���������

public:
	Game();
	void game();
	void session(); //������� ���� ��� ������� � � � 
	void setSettings(int _size, int _diff); //��������� ��������
	void setGen(); //��������� ���������� (� ����������� �� ������� � ���������) (����)

};
