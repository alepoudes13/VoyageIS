#pragma once
#include <iostream>
#include <string>

class Date {
public:
    friend int getWidth(Date date);
    friend std::istream& operator>>(std::istream& in, Date& date);
    friend std::ostream& operator<<(std::ostream& out, const Date& date);
    bool operator<=(const Date& date) const;
    bool operator==(const Date& date) const;
    void readLoop(std::string message); 
private:
    bool inputError = false;
    size_t dd, mm, yy;
};

class Time {
public:
    friend int getWidth(Time time);
    friend std::istream& operator>>(std::istream& in, Time& time);
    friend std::ostream& operator<<(std::ostream& out, const Time& time);
    bool operator<=(const Time& other) const;
    void readLoop(std::string message); 
private:
    bool inputError = false;
    size_t mm, hh;
};

