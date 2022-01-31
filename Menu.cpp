#include "Menu.h"

Menu::Menu()
{
	createScreenVector();
}

void Menu::menu(int mode)
{
	int score = 0, lives = 3, choice = 0, c = 0, i = 0, level = 0, tempLevel = 0;
	bool winScreen = false, isChose;
	string userScreen;

	if (mode == LOADMODE || mode == SILENTMODE)
	{
		while (i < int(names.size()))
		{
			clear_screen();
			string nameSteps = names[i];
			nameSteps.erase(nameSteps.size() - 7, nameSteps.size());
			nameSteps += ".steps";
			string nameResult = names[i];
			nameResult.erase(nameResult.size() - 7, nameResult.size());
			nameResult += ".result";
			try {
				if (mode == LOADMODE)
				{
					winScreen = LoadMode(names[i], nameSteps, nameResult).run(score, lives, 0);
				}
				else
				{
					SilentMode silent(names[i], nameSteps, nameResult, score, lives);
					winScreen = silent.getStatus();
				}

				if (winScreen)
				{
					cout << "test passed for: " << names[i] << endl;
					printWin(LOADWIN, names[i]);
				}
				else
				{
					cout << "test passed for: " << names[i] << endl;
					printLose(names[i]);
					break;
				}
			}
			catch (const char* ex)
			{
				clear_screen();
				cout << ex;
				c = _getch();
				return;
			}
			c = _getch();
			i++;
			clear_screen();
		}
	}

	else 
	{
		while (choice != EXITGAME)
		{
			i = 0, score = 0, lives = 3;
			winScreen = true, isChose = false;
			clear_screen();
			printMenu();
			choice = _getch();
			switch (choice)
			{
			case NEWGAME:
				while (i < int(names.size()) && winScreen)
				{
					clear_screen();
					if (!isChose)
					{
						level = chooseLevel();
						while (!checkLevel(level))
							level = chooseLevel();
						isChose = true;
					}
					if (mode == SAVEMODE)
							winScreen = SaveMode(names[i++]).run(score, lives, level);
					else
						winScreen = SimpleMode(names[i++]).run(score, lives, level);

					if (winScreen && i < int(names.size()))
					{
						printWin(MOVEBOARD, names[i-1]);
						c = _getch();
					}
					else if (!winScreen)
					{
						printLose(names[i-1]);
						c = _getch();
						break;
					}
				}
				if (winScreen)
				{
					printWin(FINISH, names[i-1]);
					c = _getch();
				}
				i = 0;
				clear_screen();
				break;
			case SCREENUSER:
				clear_screen();
				if (mode == SAVEMODE)
				{
					cout << "cant run your screen in save mode" << endl
						<< "press any key to return menu" << endl;
					c = _getch();
					break;
				}
				else
				{
					cout << "enter your screen name: " << endl;
					cin >> userScreen;
					clear_screen();
					level = chooseLevel();
					while (!checkLevel(level))
						level = chooseLevel();
					score = 0, lives = 3;
					winScreen = SimpleMode(userScreen).run(score, lives, level);
				}
				if (winScreen)
				{
					printWin(WINNER, userScreen);
					c = _getch();
				}
				else
				{
					printLose(userScreen);
					c = _getch();
				}
				break;
			case INSTRUCTIONS:
				clear_screen();
				printInsru();
				c = _getch();
				clear_screen();
				break;
			case EXITGAME:
				clear_screen();
				cout << "goodbye";
				break;
			default:
				clear_screen();
				break;
			};
		}
	}
}

void Menu::createScreenVector()
{
	std::string path = ".";
	string temp;
	for (const auto& entry : fs::directory_iterator(path))
	{
		if (entry.path().string().ends_with("screen"))
		{
			temp = entry.path().string();
			temp.erase(0, 2);
			names.push_back(temp);
		}
	}
	sort(names.begin(), names.end());
}

/*print the menu of the game*/
void Menu::printMenu()
{
	cout << "(1) start a new game" << endl << "(2) load your screen " << endl << "(8) present instructions and keys" << endl << "(9) exit" << endl;
}

/*print the instructions of the game*/
void Menu::printInsru()
{
	cout << "Instructions:" << endl <<
		"The player controls the Pac-Man character (@) through an enclosed maze." << endl <<
		"The objective of the game is to eat all of the food (*) placed in the maze while avoiding two ghosts ($) that pursue him." << endl <<
		"When Pac-Man eats all of the food, the player win." << endl <<
		"If Pac-Man makes contact with a ghost, he will lose a life." << endl <<
		"The game ends when all lives are lost." << endl;
	cout << endl << "Keys:" << endl << "UP - W/w " << endl <<
		"DOWN - X/x" << endl << "RIGHT - D/d" << endl <<
		"LEFT - A/a" << endl << "STAY - S/s" << endl << "PAUSE - ESC" << endl;
	cout << endl << "Press any key to return the main menu." << endl;
}

/*return the user choice of level of the ghosts*/
int Menu::chooseLevel()
{
	int level = 0, tempLevel;
	cout << "choose level of ghosts: " << endl << "(a) BEST" << endl << "(b) GOOD" << endl << "(c) NOVICE" << endl;
	level = _getch();
	tempLevel = level;
	if (isupper(tempLevel))
	{
		level = tolower(tempLevel);
	}
	clear_screen();
	return level;
}

bool Menu::checkLevel(int level)
{
	if ((level == BEST) || (level == GOOD) || (level == NOVICE))
	{
		return true;
	}
	return false;
}

/*prints winner messages*/
void Menu::printWin(int typeWin, string nameScreen)
{

	if (typeWin == MOVEBOARD)
		cout << "Good Job, you finished: " << nameScreen << endl << "you move to the next screen" << endl << "press any key to continue." << endl;
	else if (typeWin == FINISH)
		cout << "Well done! You finished all the screens!" << endl << "press any key to return menu." << endl;
	else if (typeWin == LOADWIN)
		cout << "You finished: " << nameScreen << endl << "press any key to continue loading" << endl;
	else
		cout << "You win: " << nameScreen << " !" << endl << "press any key to return menu." << endl;
}

/*print loser message*/
void Menu::printLose(string nameScreen)
{
	cout << "GAME OVER!" << endl << "You lose in: " << nameScreen << endl << "press any key to return menu." << endl;
}