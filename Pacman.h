#ifndef _PACMAN_H_
#define _PACMAN_H_
#include "Creature.h"
#include "Point.h"

class Pacman :public Creature
{
private:
	char arrowKeys[SIZEARROWKEYS];
public:
	Pacman(Point _body, char _figure);
	void setArrowKeys(const char* keys);
	void setDirection(int dir);
	int getDirectionFromKB(char key) const;
	void move(char c, const Point& size, int mode);
	void movePacman(int dir, const Point& size);
};

#endif