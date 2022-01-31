#include "LoadMode.h"
LoadMode::LoadMode(string fileName, string fileSteps, string fileResult) :ThePacmanGame(fileName)
{
	stepsFile.open(fileSteps, ios::in);
	if (!stepsFile)
		throw "step file not open!";
	resultFile.open(fileResult, ios::in);
	if(!resultFile)
		throw "result file not open!";
}

bool LoadMode::run(int& score, int& lives, int level)
{
	if (!board.getVaild())
		return false;
	Pacman pac(board.getPacmanPos(), PACMAN);
	initGhosts();
	int scoreCount, livesCount, i, fruitScore, checkScore, time = 0, timeFromFile, locX, locY;
	bool flagGhost = false, eatFruit = false, fruitFlag = false, flag = false;
	char c;
	string str, strResult;
	map<string, int> mapDir{ {"Up", 0}, {"Down", 1}, {"Left", 2}, {"Right", 3}, {"Stay", 4} };
	checkScore = board.getScoreWin();
	scoreCount = score;
	livesCount = lives;
	hideCursor();
	if (level == LOAD)
	{
		board.printBoard(scoreCount, livesCount);
		showGhosts();
	}
	getline(stepsFile, str);
	if (isEof(stepsFile))
		return false;
	stepsFile >> locX >> locY;
	if (isEof(stepsFile))
		return false;
	stepsFile.get(c);
	Point location;
	location = { locX, locY };
	getline(stepsFile, str);
	if (isEof(stepsFile))
		return false;
	Fruit* newFruit = new Fruit(location, str[0]);
	if (level == LOAD)
		newFruit->show(newFruit->getPoint().getX(), newFruit->getPoint().getY());
	getline(resultFile, strResult, ' ');
	resultFile >> timeFromFile;
	resultFile.get(c);
	getline(stepsFile, str, ' ');
	if (isEof(stepsFile))
		return false;
	do {
		if (level == LOAD)
		{
			board.printScore(scoreCount);
			board.printLives(livesCount);
		}
		if (str == "Fruit:")
		{
			if (newFruit)
			{
				getline(stepsFile, str, '\n');
				if (isEof(stepsFile))
					break;
				newFruit->moveByDir(board.get(newFruit->getPoint().getX(), newFruit->getPoint().getY()), board, mapDir[str], level);
				eatFruit = isEaten(pac.getPoint(), newFruit->getPoint());
			}
			getline(stepsFile, str, ' ');
			if (isEof(stepsFile))
				break;
		}

		if (str == "Fruit")
		{
			getline(stepsFile, str, '\n');
			if (isEof(stepsFile))
				break;
			if (str == "disappearance")
			{
				if (eatFruit)
				{
					fruitScore = int(newFruit->getFigure() - '0');
					scoreCount += fruitScore;
				}
				c = board.get(newFruit->getPoint().getX(), newFruit->getPoint().getY());
				newFruit->Creature::setFigure(c);
				if (level == LOAD)
					newFruit->show(newFruit->getPoint().getX(), newFruit->getPoint().getY());
				delete newFruit;
				newFruit = nullptr;
			}
			else
			{
				if (isEof(stepsFile))
					break;
				stepsFile >> locX >> locY;
				if (isEof(stepsFile))
					return false;
				stepsFile.get(c);
				Point location;
				location = { locX, locY };
				getline(stepsFile, str);
				if (isEof(stepsFile))
					break;
				newFruit = new Fruit(location, str[0]);
				if (level == LOAD)
					newFruit->show(newFruit->getPoint().getX(), newFruit->getPoint().getY());
			}
			getline(stepsFile, str, ' ');
			if (isEof(stepsFile))
				break;
		}
		if (isFood(pac.getDirection(), pac.getPoint().getX(), pac.getPoint().getY()))
		{
			if (pac.getDirection() != STAY)
			{
				scoreCount++;
				checkScore--;
				board.updateBoard(pac.getPoint().getX(), pac.getPoint().getY(), SPACE);
			}
		}

		if (isKill(pac.getPoint()))
		{
			livesCount--;
			if (level == LOAD)
			{
				draw(pac.getPoint().getX(), pac.getPoint().getY(), SPACE);
				for (i = 0; i < board.getVecGhostSize(); i++)
					draw(vecGhosts[i].getPoint().getX(), vecGhosts[i].getPoint().getY(), board.get(vecGhosts[i].getPoint().getX(), vecGhosts[i].getPoint().getY()));
			}
			pac.setBody(board.getPacmanPos());
			pac.setDirection(STAY);
			for (i = 0; i < board.getVecGhostSize(); i++)
				vecGhosts[i].setBody(board.getGhostPos(i));
			if (level == LOAD)
				showGhosts();
			if (strResult == "died")
			{
				if (timeFromFile == time)
				{
					getline(resultFile, strResult, ' ');
					resultFile >> timeFromFile;
					resultFile.get(c);
				}
				else
				{
					throw "test failed - the pacman wasnt supposed to die this time";
				}
			}
			else
			{
				throw "test failed - the pacman wasnt supposed to die";
			}
		}

		if (pac.isWall(board, pac.getDirection(), pac.getPoint().getX(), pac.getPoint().getY()))
			pac.setDirection(STAY);

		else
		{
			if (str == "Pacman:")
			{
				getline(stepsFile, str, '\n');
				if (isEof(stepsFile))
					break;
				pac.setDirection(mapDir[str]);
				pac.move(SPACE, board.getSize(), level);
				getline(stepsFile, str, ' ');
				time++;
				if (str == "Ghost1:")
				{
					for (i = 0; i < board.getVecGhostSize(); i++)
					{
						getline(stepsFile, str, '\n');
						if (isEof(stepsFile))
							break;
						vecGhosts[i].moveByDir(board.get(vecGhosts[i].getPoint().getX(), vecGhosts[i].getPoint().getY()), board, mapDir[str], level);
						if (i + 1 < board.getVecGhostSize())
						{
							getline(stepsFile, str, ' ');
							if (isEof(stepsFile))
								break;
						}
					}
					getline(stepsFile, str, ' ');
				}
				if (level == LOAD)
					Sleep(100);
			}
		}
	} while (!isEof(stepsFile) || (checkScore > 0 && livesCount != 0));
	clear_screen();
	score = scoreCount;
	lives = livesCount;
	if (livesCount == 0)
	{
		if (strResult == "lose")
		{
			if (timeFromFile == time)
				return false;
			else
				throw "test failed - the pacman doesnt lose in this time";
		}
		else
		{
			throw "test failed - the pacman doesnt lose";
		}

	}
	else
	{
		if (strResult == "finish")
		{
			if (timeFromFile == time)
				return true;
			else
				throw "test failed - the pacman doesnt finish in this time";
		}
		else
		{
			throw "test failed - the pacman doesnt finish";
		}
	}
}

bool LoadMode::isEof(ifstream& file)
{
	return file.eof();
}

LoadMode::~LoadMode()
{
	stepsFile.close();
	resultFile.close();
}
