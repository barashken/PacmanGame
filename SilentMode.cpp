#include "SilentMode.h"

SilentMode::SilentMode(string fileName, string fileSteps, string fileResult, int& score, int& lives) : LoadMode(fileName, fileSteps, fileResult)
{
	int mode = 1;
	winScreen = run(score, lives, mode);
}
bool SilentMode::getStatus()
{
	return winScreen;
}