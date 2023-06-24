#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <conio.h>
#include <Windows.h>

#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#define DISABLE_NEWLINE_AUTO_RETURN  0x0008

class Menu
{
	const int KEY_UP = 72, KEY_DOWN = 80, COLOR_WHITE = 7, COLOR_RED = 12;
	int activeLine;
	std::string title;
	std::vector<std::string> lines;
	HANDLE consoleHandle;
	void destroy();
	void display();
public:
	Menu(std::string title, std::vector<std::string> lines);
	int getResponse();
};

