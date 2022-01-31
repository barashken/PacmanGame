#ifndef SIMPLEMODE_H_
#define SIMPLEMODE_H_
#include "ThePacmanGame.h"

class SimpleMode :public ThePacmanGame
{
private:
	string screenName;
public:
	SimpleMode(string screenName);
	bool run(int& score, int& lives, int level);
};


#endif // !SIMPLEMODE_H_
