#include "TablePrinting.h"

int getWidth(int number) {
	int width = 1;
	while (number / 10) {
		number /= 10;
		width++;
	}
	return width;
}

int getWidth(Date date) {
	return getWidth(date.dd) + (date.dd < 10 ? 1 : 0) + getWidth(date.mm) + (date.mm < 10 ? 1 : 0) + getWidth(date.yy) + 2;
}

int getWidth(Time time) {
	return getWidth(time.mm) + (time.mm < 10 ? 1 : 0) + getWidth(time.hh) + (time.hh < 10 ? 1 : 0) + 1;
}

int getWidth(std::string str) {
	return str.size();
}


void printSeparator(int width, char ch) {
	while (width--)
		std::cout << ch;
	std::cout << '\n';
}

template<typename T>
void printColumn(T obj, int columnWidth) {
	std::cout << ' '; columnWidth--;
	std::cout << obj; columnWidth -= getWidth(obj);
	while (columnWidth-- > 0)
		std::cout << ' ';
	std::cout << '|';
}

void printRow(const Account& account, int index) {
	int totalWidth = 0;
	for (int i = 0; i < account.argsCnt; i++)
		totalWidth += account.columnWidth[i];
	totalWidth += account.argsCnt;
	printColumn(index, account.columnWidth[0]);
	printColumn(account.login, account.columnWidth[1]);
	printColumn(account.saltedHashPassword, account.columnWidth[2]);
	printColumn(account.salt, account.columnWidth[3]);
	printColumn(account.rolesArray[account.role], account.columnWidth[4]);
	printColumn(account.access, account.columnWidth[5]);
	std::cout << '\n';
	printSeparator(totalWidth, '-');
}

void printRow(const Plane& plane, int index) {
	int totalWidth = 0;
	for (int i = 0; i < plane.argsCnt; i++)
		totalWidth += plane.columnWidth[i];
	totalWidth += plane.argsCnt;
	printColumn(index, plane.columnWidth[0]);
	printColumn(plane.number, plane.columnWidth[1]);
	printColumn(plane.ticketCost[Plane::Business], plane.columnWidth[2]);
	printColumn(plane.ticketsCnt[Plane::Business], plane.columnWidth[3]);
	printColumn(plane.ticketCost[Plane::Econom], plane.columnWidth[4]);
	printColumn(plane.ticketsCnt[Plane::Econom], plane.columnWidth[5]);
	printColumn(plane.planeCapacity, plane.columnWidth[6]);
	printColumn(plane.departureTime, plane.columnWidth[7]);
	printColumn(plane.departureDate, plane.columnWidth[8]);
	printColumn(plane.arrivalTime, plane.columnWidth[9]);
	printColumn(plane.destination, plane.columnWidth[10]);
	printColumn(plane.type, plane.columnWidth[11]);
	std::cout << '\n';
	printSeparator(totalWidth, '-');
}

void printRow(Plane tableType, std::vector<std::string> values) {
	int totalWidth = 0;
	for (int i = 0; i < tableType.argsCnt; i++)
		totalWidth += tableType.columnWidth[i];
	totalWidth += tableType.argsCnt;

	printSeparator(totalWidth, '-');
	for (int i = 0; i < tableType.argsCnt; i++)
		printColumn(values[i], tableType.columnWidth[i]);
	std::cout << '\n';
	printSeparator(totalWidth, '-');
}

void printRow(Account tableType, std::vector<std::string> values) {
	int totalWidth = 0;
	for (int i = 0; i < tableType.argsCnt; i++)
		totalWidth += tableType.columnWidth[i];
	totalWidth += tableType.argsCnt;

	printSeparator(totalWidth, '-');
	for (int i = 0; i < tableType.argsCnt; i++)
		printColumn(values[i], tableType.columnWidth[i]);
	std::cout << '\n';
	printSeparator(totalWidth, '-');
}