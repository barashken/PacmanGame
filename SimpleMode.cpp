#include "SimpleMode.h"

SimpleMode::SimpleMode(string screenName) : ThePacmanGame(screenName)
{
	this->screenName = screenName;
}

/*this main function of the game, return true if the user finish the board. otherwise, false*/
bool SimpleMode::run(int& score, int& lives, int level)
{
	if (!board.getVaild())
		return false;
	Pacman pac(board.getPacmanPos(), PACMAN);
	initGhosts();
	int key = 0, tempKey, dir, movePac = 0, scoreCount, livesCount, i, countFruit = 0, timeFruit = 0, moveGhost = 0, fruitScore, checkScore, time = 0;
	bool flagGhost = false, eatFruit = false, fruitFlag = false, flag = false;
	char c;
	checkScore = board.getScoreWin();
	scoreCount = score;
	livesCount = lives;
	hideCursor();
	board.printBoard(scoreCount, livesCount);
	showGhosts();
	Point location;
	location = locationForFruit();
	Fruit* newFruit = new Fruit(location, '0');
	newFruit->setFigure();
	newFruit->show(newFruit->getPoint().getX(), newFruit->getPoint().getY());
	do {
		board.printScore(scoreCount);
		board.printLives(livesCount);
		if (_kbhit())
		{
			key = _getch();
			if (key == ESC)
			{
				pauseGame();
				key = _getch();
				while (key != ESC)
				{
					_kbhit();
					key = _getch();
				}
				clear_screen();
				board.printBoard(scoreCount, livesCount);
			}
			else
			{
				tempKey = key;
				if (isupper(tempKey))
				{
					key = tolower(tempKey);
				}
				if ((dir = pac.getDirectionFromKB(key)) != -1)
				{
					pac.setDirection(dir);
				}
			}
		}

		if (newFruit && fruitFlag)
		{
			fruitFlag = false;
			newFruit->move(board.get(newFruit->getPoint().getX(), newFruit->getPoint().getY()), board);
			eatFruit = isEaten(pac.getPoint(), newFruit->getPoint());
		}

		if (countFruit == 100 || eatFruit || (newFruit && isKill(newFruit->getPoint())))
		{
			if (newFruit)
			{
				if (eatFruit)
				{
					fruitScore = int(newFruit->getFigure() - '0');
					scoreCount += fruitScore;
				}
				c = board.get(newFruit->getPoint().getX(), newFruit->getPoint().getY());
				newFruit->Creature::setFigure(c);
				newFruit->show(newFruit->getPoint().getX(), newFruit->getPoint().getY());
				delete newFruit;
				newFruit = nullptr;
			}
			else if (timeFruit == 200)
			{
				timeFruit = 0;
				location = locationForFruit();
				newFruit = new Fruit(location, '0');
				newFruit->setFigure();
				newFruit->show(newFruit->getPoint().getX(), newFruit->getPoint().getY());
			}
			countFruit = 0;
		}

		if (isFood(pac.getDirection(), pac.getPoint().getX(), pac.getPoint().getY()))
		{
			if (pac.getDirection() != STAY)
			{
				scoreCount++;
				checkScore--;
				board.updateBoard(pac.getPoint().getX(), pac.getPoint().getY(), SPACE);
			}
		}

		if (isKill(pac.getPoint()))
		{
			livesCount--;
			draw(pac.getPoint().getX(), pac.getPoint().getY(), SPACE);
			for (i = 0; i < board.getVecGhostSize(); i++)
				draw(vecGhosts[i].getPoint().getX(), vecGhosts[i].getPoint().getY(), board.get(vecGhosts[i].getPoint().getX(), vecGhosts[i].getPoint().getY()));
			pac.setBody(board.getPacmanPos());
			pac.setDirection(STAY);
			for (i = 0; i < board.getVecGhostSize(); i++)
				vecGhosts[i].setBody(board.getGhostPos(i));
			showGhosts();
		}

		if (pac.isWall(board, pac.getDirection(), pac.getPoint().getX(), pac.getPoint().getY()))
			pac.setDirection(STAY);

		else
		{
			pac.move(SPACE, board.getSize(), SAVE);
			movePac++;
			time++;
			countFruit++;
			timeFruit++;
			if (movePac == 2)
			{
				flagGhost = true;
				movePac = 0;
			}
			if (flagGhost)
			{
				for (i = 0; i < board.getVecGhostSize(); i++)
				{
					vecGhosts[i].move(board.get(vecGhosts[i].getPoint().getX(), vecGhosts[i].getPoint().getY()), board, pac.getPoint(), level, board.getVecGhostSize());
				}
				moveGhost++;


				flagGhost = false;
			}
			if (moveGhost == 2)
			{
				fruitFlag = true;
				moveGhost = 0;
			}
			Sleep(100);

		}
	} while (checkScore > 0 && livesCount != 0);
	clear_screen();
	score = scoreCount;
	lives = livesCount;
	if (livesCount == 0)
		return false;
	return true;
}