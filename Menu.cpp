#include "Menu.h"

Menu::Menu(std::string title, std::vector<std::string> lines) : activeLine(0) {
	this->title = title;
	this->lines = lines;
	this->consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	//Включить ANSI Escape коды для консоли
	DWORD lpMode;
	GetConsoleMode(this->consoleHandle, &lpMode);
	SetConsoleMode(this->consoleHandle, lpMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN);
}

void Menu::display() {
	std::cout << this->title << '\n';
	for (int i = 0; i < static_cast<int>(this->lines.size()); i++) {
		if (i == this->activeLine) {
			SetConsoleTextAttribute(this->consoleHandle, this->COLOR_RED);
			std::cout << '>' << this->lines[i] << '\n';
			SetConsoleTextAttribute(this->consoleHandle, this->COLOR_WHITE);
		}
		else
			std::cout << this->lines[i] << '\n';
	}
}

void Menu::destroy() {
	for (size_t i = 0; i < this->lines.size(); i++)
		std::cout << "\033[A\33[2K\r";
	std::cout << "\033[A\33[2K\r";
}

//ANSI Escape коды
/* 
   \033[A - перевести курсор на строку вверх
   \33[2K - удалить строку, на которой находится курсор
   \r     - переместить курсор в начало текущей строки
*/

int Menu::getResponse() {
	this->activeLine = 0;
	this->display();
	for (char inp = _getch(); inp != '\r'; inp = _getch()) {
		if (inp == this->KEY_UP)
			this->activeLine = (this->activeLine - 1 + this->lines.size()) % this->lines.size();
		else if (inp == this->KEY_DOWN)
			this->activeLine = (this->activeLine + 1) % this->lines.size();
		else
			continue;
		this->destroy();
		this->display();
	}
	this->destroy();
	return this->activeLine;
}
