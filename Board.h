#ifndef _BOARD_H_
#define _BOARD_H_
#include "Point.h"
#include "Symbols.h"

class BoardGame
{
private:
	Point score;
	Point lives;
	Point size;
	Point legend;
	Point pacmanPos;
	string screenName;
	vector<Point> vecGhosts;
	vector< vector<char> > board;
	int scoreWin;
	bool valid;
public:
	BoardGame(string _screenName);
	void setScore(int x, int y);
	void setLives(int x, int y);
	void setScreenName(string name);
	bool setBoard();
	char get(const int x, const int y) const;
	int getScoreWin()const;
	const Point& getPacmanPos()const;
	int getVecGhostSize()const;
	const Point& getGhostPos(int i)const;
	const Point& getSize()const;
	const Point& getLegend()const;
	bool getVaild() const;
	const string& getScreenName()const;
	void printScore(int conuter) const;
	void printLives(int conuter) const;
	void printBoard(int score, int lives) const;
	void updateBoard(int x, int y, char c);
};

#endif