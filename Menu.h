#pragma once

#include "io_utils.h"
#include "SimpleMode.h"
#include "SaveMode.h"
#include "LoadMode.h"
#include "SilentMode.h"
#include "Symbols.h"

class Menu
{
private:
	vector<string> names;
public:
	Menu();
	void menu(int mode);
	void createScreenVector();
	void printInsru();
	void printMenu();
	void printLose(string nameScreen);
	void printWin(int typeWin, string nameScreen);
	int chooseLevel();
	bool checkLevel(int level);

};


