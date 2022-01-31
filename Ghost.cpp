#include "Ghost.h"

/*c'tor of ghost*/
Ghost::Ghost(Point _body, char _figure) : Creature(_body, _figure)
{
	setPossibleDir();
	setDirection();
}

/*this function move and draw the ghost*/
void Ghost::move(char ch, const BoardGame& board, const Point& pacPoint, int level, int numOfGhosts)
{
	body.draw(ch);
	moveByLevel(board, pacPoint, level, numOfGhosts);
	body.draw(figure);
}

void Ghost::moveByDir(char ch, const BoardGame& board, int dir, int mode)
{
	if (mode == LOAD)
		body.draw(ch);
	moveGhostByDir(dir, board);
	if (mode == LOAD)
		body.draw(figure);
}

/*this function move the ghost by the level that the user chose*/
void Ghost::moveByLevel(const BoardGame& board, const Point& pacPoint, int level, int numOfGhosts)
{
	static int countBest, countGood, countGoodRandom, countNovice;
	static bool flagGood;
	switch (level)
	{
	case BEST:
		if (countBest < numOfGhosts)
		{
			setDirection();
			moveGhost(direction, board);
		}
		else
			smartMove(board, pacPoint);
		if (countBest == 20 * numOfGhosts)
			countBest = 0;
		countBest++;
		break;
	case GOOD:
		if (countGood == (20 * numOfGhosts))
		{
			flagGood = true;
		}
		if (flagGood)
		{
			if (countGoodRandom < numOfGhosts)
			{
				setDirection();
				moveGhost(direction, board);
			}
			else
			{
				moveGhost(direction, board);
				countGood = 0;
			}
			countGoodRandom++;
		}
		else
			smartMove(board, pacPoint);
		if (countGoodRandom == (10 * numOfGhosts))
		{
			flagGood = false;
			countGoodRandom = 0;
		}
		countGood++;
		break;
	case NOVICE:
		if (countNovice < numOfGhosts)
			setDirection();
		moveGhost(direction, board);
		if (countNovice == (20 * numOfGhosts))
		{
			countNovice = 0;
		}
		countNovice++;
		break;
	}
}

/*this function move the ghost*/
void Ghost::moveGhost(int dir, const BoardGame& board)
{
	int x = body.getX();
	int y = body.getY();
	while (!moveValid(dir, board))
	{
		setDirection();
		dir = getDirection();
	}
	switch (dir)
	{
	case UP:
		body.setY(--y);
		break;
	case DOWN:
		body.setY(++y);
		break;
	case LEFT:
		body.setX(--x);
		break;
	case RIGHT:
		body.setX(++x);
		break;
	case STAY:
		break;
	default:
		break;
	}

}

void Ghost::moveGhostByDir(int dir, const BoardGame& board)
{
	int x = body.getX();
	int y = body.getY();

	switch (dir)
	{
	case UP:
		body.setY(--y);
		break;
	case DOWN:
		body.setY(++y);
		break;
	case LEFT:
		body.setX(--x);
		break;
	case RIGHT:
		body.setX(++x);
		break;
	case STAY:
		break;
	default:
		break;
	}
}

/*set array possible direction of ghost*/
void Ghost::setPossibleDir()
{
	possibleDir[UP] = UP;
	possibleDir[DOWN] = DOWN;
	possibleDir[LEFT] = LEFT;
	possibleDir[RIGHT] = RIGHT;
}

/*set direction of ghost randomize from possible direction array*/
void Ghost::setDirection()
{
	direction = possibleDir[rand() % SIZEDIR];
}

/*set direction of smart ghost*/
void Ghost::setSmartDirection(int dir)
{
	direction = dir;
}

/*the function move the smart ghost by bfs algorithem*/
void Ghost::smartMove(const BoardGame& board, const Point& pacPoint)
{
	int xGhostPos = getPoint().getX(), yGhostPos = getPoint().getY();
	vector<vector<bool>> visit(board.getSize().getY(), vector<bool>(board.getSize().getX(), false));
	Point newPoint = BFS(board, visit, pacPoint);

	if (newPoint.getX() == xGhostPos - 1) //left
	{
		body.setX(--xGhostPos);
		setSmartDirection(LEFT);
	}

	else if (newPoint.getX() == xGhostPos + 1) //right
	{
		body.setX(++xGhostPos);
		setSmartDirection(RIGHT);
	}

	else if (newPoint.getY() == yGhostPos - 1) //up
	{
		body.setY(--yGhostPos);
		setSmartDirection(UP);
	}

	else
	{
		body.setY(++yGhostPos); // down
		setSmartDirection(DOWN);
	}
}

/*check if the next step of the smart ghost is valid*/
bool Ghost::isValidStep(const vector<vector<bool>> visit, int row, int col, const BoardGame& board)const
{
	if (row >= board.getSize().getY() || col >= board.getSize().getX() || row <= 0 || col <= 0)
		return false;

	if (board.get(col, row) == WALL)
		return false;

	if (visit[row][col])
		return false;

	return true;
}

/*bfs algorithem*/
Point Ghost::BFS(const BoardGame& board, vector<vector<bool>> visit, const Point& pacPoint)const
{
	Point ghostPoint = getPoint();
	int dirRow[] = { -1, 0, 1, 0 };
	int dirCol[] = { 0, 1, 0, -1 };
	// Stores indices of the matrix cells
	queue<Point> q;
	// Mark the starting cell as visited and push it into the queue
	Point currPos;
	currPos.setX((pacPoint.getX()));
	currPos.setY((pacPoint.getY()));
	q.push(currPos);
	visit[pacPoint.getY()][pacPoint.getX()] = true;
	// Iterate while the queue is not empty
	while (!q.empty())
	{
		Point currCell = q.front();
		int x = currCell.getX();
		int y = currCell.getY();
		q.pop();
		// Go to the adjacent cells
		for (int i = 0; i < 4; i++) {
			int adjY = y + dirRow[i];
			int adjX = x + dirCol[i];
			Point adjPoint(adjX, adjY);
			if (adjPoint == ghostPoint)
				return Point(x, y);
			else if (isValidStep(visit, adjY, adjX, board)) {
				q.push(adjPoint);
				visit[adjY][adjX] = true;
			}
		}
	}

	// if short way has not found - return the curr position
	return getPoint();
}