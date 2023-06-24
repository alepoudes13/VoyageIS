#pragma once
#include "Datetime.h"
#include "Account.h"
#include "Plane.h"
#include <string>
#include <vector>

int getWidth(int number); 
int getWidth(Date date); 
int getWidth(Time time); 
int getWidth(std::string str);

template<typename T>
void printColumn(T obj, int columnWidth);

void printSeparator(int width, char ch);
void printRow(const Plane& plane, int index);
void printRow(const Account& account, int index);

void printRow(Plane tableType, std::vector<std::string> values); 
void printRow(Account tableType, std::vector<std::string> values);