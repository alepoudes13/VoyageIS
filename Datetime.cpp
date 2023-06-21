#include "Datetime.h"

std::istream& operator>>(std::istream& in, Time& time) {
	char buf;
	in >> time.hh >> buf >> time.mm;
	if (in.fail() || buf != ':' || time.hh > 23 || time.mm > 59)
		time.inputError = true;
	else
		time.inputError = false;
	return in;
}

std::ostream& operator<<(std::ostream& out, const Time& time) {
	if (time.hh < 10)
		out << 0;
	out << time.hh << ':';
	if (time.mm < 10)
		out << 0;
	out << time.mm;
	return out;
}

bool Time::operator<=(const Time& other) const {
	return this->hh == other.hh ? this->mm <= other.mm : this->hh <= other.hh;
}

void Time::readLoop(std::string message) {
	do {
		std::cout << message;
		std::cin >> *this;
		std::cin.clear();
		std::cin.ignore(10000, '\n');
	} while (this->inputError);
}

//=================================================

std::istream& operator>>(std::istream& in, Date& date) {
	char buf1, buf2;
	in >> date.dd >> buf1 >> date.mm >> buf2 >> date.yy;
	if (in.fail() || buf1 != '.' || buf2 != '.' || date.dd > 31 || date.mm > 12)
		date.inputError = true;
	else
		date.inputError = false;
	return in;
}

std::ostream& operator<<(std::ostream& out, const Date& date) {
	if (date.dd < 10)
		out << 0;
	out << date.dd << '.';
	if (date.mm < 10)
		out << 0;
	out << date.mm << '.' << date.yy;
	return out;
}

bool Date::operator<=(const Date& other) const {
	return this->yy == other.yy ? (this->mm == other.mm ? this->dd <= other.dd : this->mm <= other.mm) : this->yy <= other.yy;
}

bool Date::operator==(const Date& other) const {
	return this->yy == other.yy && this->mm == other.mm && this->dd == other.dd;
}

void Date::readLoop(std::string message) {
	do {
		std::cout << message;
		std::cin >> *this;
		std::cin.clear();
		std::cin.ignore(10000, '\n');
	} while (this->inputError);
}