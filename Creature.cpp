#include "Creature.h"

/*c'tor for creature*/
Creature::Creature(Point _body, char _figure)
{
	setBody(_body);
	setFigure(_figure);
}

/*return the figure of the creature*/
char Creature::getFigure()const
{
	return figure;
}

/*set the loction body of the creature*/
void Creature::setBody(Point _body)
{
	body.setX(_body.getX());
	body.setY(_body.getY());
}

/*set creature of the creature*/
void Creature::setFigure(const char _figure)
{
	figure = _figure;
}

/*this function create new arr of possible possition of next step for creature*/

int* Creature::newPosDir(int dir)
{
	int* arr = new int[3];
	switch (dir)
	{
	case 0:
		arr[0] = DOWN;
		arr[1] = LEFT;
		arr[2] = RIGHT;
		break;
	case 1:
		arr[0] = UP;
		arr[1] = LEFT;
		arr[2] = RIGHT;
		break;
	case 2:
		arr[0] = UP;
		arr[1] = DOWN;
		arr[2] = RIGHT;
		break;
	case 3:
		arr[0] = UP;
		arr[1] = DOWN;
		arr[2] = LEFT;
		break;
	default:
		break;
	}
	return arr;
}

/*return the location body of the creature*/
const Point& Creature::getPoint() const
{
	return body;
}

/*return the direction of the creature*/
int Creature::getDirection() const
{
	return direction;
}

/*draw the creature on the screen in current possition*/
void Creature::show(int x, int y) const
{
	gotoxy(x, y);
	cout << figure;
}

/*check if the next step of creature is wall*/
bool Creature::isWall(const BoardGame& board, int dir, int x, int y)const
{
	char c = '0';
	switch (dir) {
	case 0: // UP
		if (y == 0)
			c = board.get(x, board.getSize().getY() - 1);
		else
			c = board.get(x, y - 1);
		break;
	case 1: // DOWN
		if (y == board.getSize().getY() - 1)
			c = board.get(x, 0);
		else
			c = board.get(x, y + 1);
		break;
	case 2: // LEFT
		if (x == 0)
			c = board.get(board.getSize().getX() - 1, y);
		else
			c = board.get(x - 1, y);
		break;
	case 3: // RIGHT
		if (x == (board.getSize().getX() - 1))
			c = board.get(0, y);
		else
			c = board.get(x + 1, y);
		break;
	case 4: // STAY
		break;
	default:
		break;
	}
	return(c == WALL);
}

/*check if next step of creature is valid to move*/
bool Creature::moveValid(int dir, const BoardGame& board)
{
	int x = body.getX();
	int y = body.getY();
	switch (dir)
	{
	case UP:
		y = y - 1;
		break;
	case DOWN:
		y = y + 1;
		break;
	case LEFT:
		x = x - 1;
		break;
	case RIGHT:
		x = x + 1;
		break;
	case STAY:
		break;
	default:
		break;
	}
	return (isValid(y, x, board));
}

/*check if next step of creature is valid*/
bool Creature::isValid(int row, int col, const BoardGame& board)const
{
	if (row >= board.getSize().getY() || col >= board.getSize().getX() || row <= 0 || col <= 0)
		return false;

	if (board.get(col, row) == WALL)
		return false;

	return true;
}