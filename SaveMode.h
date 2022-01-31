#ifndef SAVEMODE_H_
#define SAVEMODE_H_
//#pragma once
#include "ThePacmanGame.h"

class SaveMode : public ThePacmanGame
{
private:
	ofstream stepsFile;
	ofstream resultFile;
	string screenName;

public:
	SaveMode(string file);
	bool run(int& score, int& lives, int level); // virtual
	~SaveMode();
};

#endif // !SAVEMODE_H_
