#ifndef _THEPACMANGAME_H_
#define _THEPACMANGAME_H_
//#pragma once
#include "Board.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Fruit.h"
#include "Symbols.h"

class ThePacmanGame
{
protected:
	BoardGame board;
	vector <Ghost> vecGhosts;
public:
	ThePacmanGame(string file) :board(file) {}
	virtual bool run(int& score, int& lives, int level) = 0;
	void initGhosts();
	Point locationForFruit()const;
	bool isFood(int dir, int x, int y)const;
	bool isKill(const Point& cretureLoc)const;
	bool isEaten(const Point& pacLoc, const Point& fruitLoc)const;
	void pauseGame() const;
	void draw(int x, int y, char ch)const;
	void showGhosts() const;
	bool isValidLoc(int x, int y)const;
};

#endif
