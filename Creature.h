#ifndef CREATURE_H_
#define CREATURE_H_

#include "Point.h"
#include "Board.h"
#include "Symbols.h"

class Creature
{
protected:
	Point body;
	int direction;
	char figure;
public:
	Creature(Point _body, char _figure);
	virtual void setFigure(const char _figure);
	void setBody(Point _body);
	char getFigure()const;
	int getDirection() const;
	const Point& getPoint() const;
	int* newPosDir(int dir);
	void show(int x, int y) const;
	bool isWall(const BoardGame& board, int dir, int x, int y)const;
	bool isValid(int row, int col, const BoardGame& board)const;
	bool moveValid(int dir, const BoardGame& board);
};

#endif // !CREATURE_H_
