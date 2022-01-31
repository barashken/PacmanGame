#ifndef _POINT_H_
#define _POINT_H_

#include "io_utils.h"

class Point {
	unsigned int _x;
	unsigned int _y;
public:
	Point() { _x = 0, _y = 0; };
	Point(int x, int y);
	void draw(char ch);
	void setX(int x);
	void setY(int y);
	int getX() const;
	int getY() const;
	bool operator==(const Point& p)const;
};

#endif