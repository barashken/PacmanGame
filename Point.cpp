#include "Point.h"

/*c'tor of point*/
Point::Point(int x, int y)
{
	_x = x;
	_y = y;
}

/*draw the char that received to the screen*/
void Point::draw(char ch) {
	gotoxy(_x, _y);
	cout << ch << endl;
}

/*set the x of the point*/
void Point::setX(int x)
{
	_x = x;
}

/*set the y of the point*/
void Point::setY(int y)
{
	_y = y;
}

/*return the x of the point*/
int Point::getX() const
{
	return _x;
}

/*return the y of the point*/
int Point::getY() const
{
	return _y;
}

/*opertor of equal between points*/
bool Point::operator==(const Point& p)const
{
	return((this->getX() == p.getX()) && this->getY() == p.getY());
}
