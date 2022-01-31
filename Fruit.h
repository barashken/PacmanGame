#ifndef FRUIT_H_
#define FRUIT_H_

#include "Creature.h"

class Fruit : public Creature
{
private:
	int* possibleDir;
	char* figureArr;

public:
	Fruit(Point _body, char _figure);
	~Fruit()
	{
		delete[] possibleDir;
		delete[] figureArr;
	}

	void move(char ch, const BoardGame& board);
	void moveByDir(char ch, const BoardGame& board, int dir, int mode);
	void moveFruit(int dir, const BoardGame& board);
	void setFigure();
	void setPossibleDir();
	void setDirection();
	void setDirection(int dir);
	void setFigureArr();
};


#endif // !FRUIT_H_
