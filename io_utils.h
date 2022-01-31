#ifndef _IO_UTILS_H_
#define _IO_UTILS_H_

#include "Config.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <windows.h>
#include <fstream>
#include <filesystem>

using namespace std;
using std::filesystem::directory_iterator;
namespace fs = std::filesystem;

void gotoxy(int x, int y);
void hideCursor();
void clear_screen();

#ifndef WINDOWS	
int _getch(void);
int _kbhit(void);
void Sleep(unsigned long);
#else
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#endif

#endif