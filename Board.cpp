#include "Board.h"

BoardGame::BoardGame(string _screenName)
{
	board.resize(MAXROWS);
	for (int i = 0; i < int(board.size()); i++)
		board[i].resize(MAXCOLS);
	screenName = _screenName;
	valid = setBoard();
}

void BoardGame::setScore(int x, int y)
{
	score.setX(x);
	score.setY(y);
}

void BoardGame::setLives(int x, int y)
{
	lives.setX(x);
	lives.setY(y);
}

void BoardGame::setScreenName(string name)
{
	screenName = name;
}

bool BoardGame::setBoard()
{
	fstream file;
	Point ghostPos;
	int len, i = 0, j = 0, row = 0, count = 0, vecSize = 0, maxCol = 0, k = 0;
	char c, prevC = 0;
	bool wasPacman = false, wasLeged = false;
	char score[] = "SCORE = 0           ";
	char lives[] = "LIVES = 0           ";
	file.open(screenName, ios::in);
	if (!file)
	{
		cout << "file is not open!" << endl;
		return false;
	}
	while (((c = char(file.get())) != EOF) && (i < MAXROWS))
	{
		if (c == '\n')
		{
			if (i == 0)
			{
				if (prevC == LEGEND)
				{
					j += 19;
					wasLeged = true;
				}
				maxCol = j;
				j = 0;
			}
			else
			{
				if (j < maxCol)
					for (j; j < maxCol; j++)
						board[i][j] = SPACE;
				j = 0;
			}
			i++;
		}
		else
		{
			if (i < MAXROWS)
			{
				board[i][j] = c;
				prevC = c;
				j++;
			}
		}
	}
	k = i;
	if (!wasLeged)
	{
		if (prevC == LEGEND)
		{
			wasLeged = true;
			legend.setX(--j);
			legend.setY(i);
			for (i; i < k + 3; ++i)
			{
				for (j = 0; j < maxCol; j++)
				{
					if (board[i][j] != LEGEND)
						board[i][j] = SPACE;
				}
			}
			i--;
		}
	}
	wasLeged = false;
	i++;
	if (i > MAXROWS)
	{
		i = MAXROWS;
	}
	size.setX(maxCol);
	size.setY(i);
	for (i = 0; i < int(board.size()); i++)
	{
		for (j = 0; j < maxCol; j++)
		{
			switch (board[i][j])
			{
			case ' ':
				board[i][j] = FOOD;
				count++;
				break;
			case '%':
				board[i][j] = SPACE;
				break;
			case '&':
				if (!wasLeged)
				{
					legend.setX(j);
					legend.setY(i);
				}
				else
				{
					board[i][j] = FOOD;
					count++;
				}
				wasLeged = true;
				break;
			case '@':
				if (!wasPacman)
				{
					pacmanPos.setX(j);
					pacmanPos.setY(i);
				}
				board[i][j] = SPACE;
				wasPacman = true;
				break;
			case '$':
				ghostPos.setX(j);
				ghostPos.setY(i);
				vecGhosts.push_back(ghostPos);
				board[i][j] = SPACE;
				break;
			default:
				break;
			}
		}
	}
	if (!wasPacman || !wasLeged)
		return false;

	scoreWin = count;
	j = 0;
	len = int(strlen(score));
	for (i = legend.getX(); i < legend.getX() + len; i++)
	{
		if (score[j] == '0')
		{
			setScore(i, legend.getY());
			setLives(i, legend.getY() + 1);
		}
		row = legend.getY();
		board[row][i] = score[j];
		row++;
		board[row][i] = lives[j];
		row++;
		board[row][i] = SPACE;
		j++;
	}

	file.close();
	return true;
}

char BoardGame::get(const int x, const int y) const
{
	return board[y][x];
}

int BoardGame::getScoreWin() const
{
	return scoreWin;
}

const Point& BoardGame::getPacmanPos()const
{
	return pacmanPos;
}

int BoardGame::getVecGhostSize()const
{
	return int(vecGhosts.size());
}

const Point& BoardGame::getGhostPos(int i)const
{
	return vecGhosts[i];
}

const Point& BoardGame::getSize()const
{
	return size;
}

const Point& BoardGame::getLegend()const
{
	return legend;
}

bool BoardGame::getVaild() const
{
	return valid;
}

const string& BoardGame::getScreenName()const
{
	return screenName;
}

void BoardGame::printScore(int counter) const
{
	gotoxy(score.getX(), score.getY());
	cout << counter;
}

void BoardGame::printLives(int counter) const
{
	gotoxy(lives.getX(), lives.getY());
	cout << counter;
}

void BoardGame::printBoard(int score, int lives) const
{
	int i, j;
	for (i = 0; i < size.getY(); i++)
	{
		for (j = 0; j < size.getX(); j++)
			cout << board[i][j];
		cout << endl;
	}
	printScore(score);
	printLives(lives);
}

void BoardGame::updateBoard(int x, int y, char c)
{
	board[y][x] = c;
}


