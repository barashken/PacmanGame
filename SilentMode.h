#ifndef SILENTMODE_H_
#define SILENTMODE_H_
#include "LoadMode.h"

class SilentMode : public LoadMode
{
private:
	bool winScreen;
public:
	SilentMode(string fileName, string fileSteps, string fileResult, int& score, int& lives);
	bool getStatus();
};

#endif // !SILENTMODE_H_
