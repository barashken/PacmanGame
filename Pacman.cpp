#include "Pacman.h"

/*c'tor*/
Pacman::Pacman(Point _body, char _figure) : Creature(_body, _figure)
{
	setArrowKeys("wxads");
	setDirection(STAY);
}

/*set the arrow keys array*/
void Pacman::setArrowKeys(const char* keys)
{
	arrowKeys[0] = keys[0];
	arrowKeys[1] = keys[1];
	arrowKeys[2] = keys[2];
	arrowKeys[3] = keys[3];
	arrowKeys[4] = keys[4];
}

/*set the direction of pacman*/
void Pacman::setDirection(int dir)
{
	direction = dir;
}

/*set the direction of pacman from keyboard*/
int Pacman::getDirectionFromKB(char key) const
{
	for (int i = 0; i < SIZEARROWKEYS; i++)
	{
		if (key == arrowKeys[i])
			return i;
	}
	return -1;
}

/*this function move and draw the pacman*/
void Pacman::move(char c, const Point& size, int mode)
{
	if (mode == LOAD)
		body.draw(' ');
	movePacman(direction, size);
	if (mode == LOAD)
		body.draw(figure);
}

/*this function move to pacman*/
void Pacman::movePacman(int dir, const Point& size)
{
	int x = body.getX();
	int y = body.getY();
	switch (dir) {
	case UP:
		body.setY(--y);
		if (y < 0) {
			body.setY(size.getY() - 1);
		}
		break;
	case DOWN:
		body.setY(++y);
		if (y >= size.getY()) {
			body.setY(0);
		}
		break;
	case LEFT:
		body.setX(--x);
		if (x < LEFTLIMIT) {
			body.setX(size.getX() - 1);
		}
		break;
	case RIGHT:
		body.setX(++x);
		if (x >= size.getX()) {
			body.setX(LEFTLIMIT);
		}
		break;
	case STAY:
		break;
	default:
		break;
	}
}