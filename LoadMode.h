#ifndef LOADMODE_H_
#define LOADMODE_H_
//#pragma once
#include "ThePacmanGame.h"

class LoadMode : public ThePacmanGame
{
private:
	ifstream stepsFile;
	ifstream resultFile;
public:
	LoadMode(string fileName, string fileSteps, string fileResult);
	~LoadMode();
	bool run(int& score, int& lives, int level);
	bool isEof(ifstream& file);
};
#endif // !LOADMODE_H_
