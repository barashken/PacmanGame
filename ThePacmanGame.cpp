#include "ThePacmanGame.h"

/*this function init the ghosts in their position*/
void ThePacmanGame::initGhosts()
{
	for (int i = 0; i < board.getVecGhostSize(); i++)
	{
		vecGhosts.push_back(Ghost(board.getGhostPos(i), GHOST));
	}
}

/*print pause game*/
void ThePacmanGame::pauseGame() const
{
	clear_screen();
	cout << "Game paused, press ESC again to continue.";
	_kbhit();
}

/*this function check if the pacman eat breadcramb in current point*/
bool ThePacmanGame::isFood(int dir, int x, int y)const
{
	char c = board.get(x, y);
	return(c == FOOD);
}

/*this function check if the ghosts eats the pacman or fruit*/
bool ThePacmanGame::isKill(const Point& cretureLoc)const
{
	for (int i = 0; i < board.getVecGhostSize(); i++)
		if (cretureLoc == vecGhosts[i].getPoint())
			return true;
	return false;
}

/*this function check if the pacman eat the fruit*/
bool ThePacmanGame::isEaten(const Point& pacLoc, const Point& fruitLoc)const
{
	Point temp;
	int i, j;
	for (i = -1; i <= 1; i++)
	{
		for (j = -1; j <= 1; j++)
		{
			temp.setX(pacLoc.getX() + i);
			temp.setY(pacLoc.getY() + j);
			if (temp == fruitLoc)
				return true;
		}
	}
	return false;
}

/*draw the char that received to the screen*/
void ThePacmanGame::draw(int x, int y, char ch)const
{
	gotoxy(x, y);
	cout << ch << endl;
}

/*this function show the ghosts*/
void ThePacmanGame::showGhosts() const
{
	for (int i = 0; i < board.getVecGhostSize(); i++)
		vecGhosts[i].show(board.getGhostPos(i).getX(), board.getGhostPos(i).getY());
}

/*this function randomize valid location for the fruit*/
Point ThePacmanGame::locationForFruit()const
{
	Point temp;
	int x, y;
	srand((unsigned int)time(NULL));
	x = rand() % board.getSize().getX();
	y = rand() % board.getSize().getY();
	while (!isValidLoc(x, y))
	{
		x = rand() % board.getSize().getX();
		y = rand() % board.getSize().getY();
	}
	temp.setX(x);
	temp.setY(y);
	return temp;
}

/*this function check if the location for the fruit is valid*/
bool ThePacmanGame::isValidLoc(int x, int y)const
{
	return ((board.get(x, y) == FOOD) || (board.get(x, y) == SPACE));
}