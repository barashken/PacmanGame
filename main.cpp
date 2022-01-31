#include "Menu.h"

void wrongMode();
int checkSilent(int mode, char* argv2);

int main(int argc, char** argv)
{
	int mode = SIMPLEMODE;
	bool load = false, save = false;
	if (!argv[1])
		mode = SIMPLEMODE;
	else if (strcmp(argv[1], "-load") == 0)
	{
		mode = LOADMODE;
		load = true;
	}
	else if (strcmp(argv[1], "-save") == 0)
	{
		mode = SAVEMODE;
		save = true;
	}
	else
	{
		wrongMode();
		return 0;
	}
	if (load)
	{
		if (argv[2])
		{
			mode = checkSilent(LOADMODE, argv[2]);
			if (mode == -1)
				return 0;
		}
	}
	else if (save)
	{
		if (argv[2])
		{
			mode = checkSilent(SAVEMODE, argv[2]);
			if (mode == -1)
				return 0;
		}
	}
	Menu().menu(mode);
	return 0;
}


void wrongMode()
{
	cout << "argument not valid!" << endl  << "You can use only [-save][-load | -load - silent]" << endl;
}

int checkSilent(int mode, char* argv2)
{
	if (strcmp(argv2, "-silent") == 0)
	{
		if (mode == LOADMODE)
			return SILENTMODE;
		else if (mode == SAVEMODE)
			return SAVEMODE;
		else
		{
			wrongMode();
			return WRONG;
		}
	}
	else
	{
		wrongMode();
		return WRONG;
	}
}
