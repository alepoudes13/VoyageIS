#pragma once
#include "Datetime.h"
#include "Account.h"
#include "Plane.h"
#include <string>
#include <vector>

int getWidth(int number); //Получить ширину в символах объекта типа int
int getWidth(Date date); //Получить ширину в символах объекта типа Date
int getWidth(Time time); //Получить ширину в символах объекта типа Time
int getWidth(std::string str); //Получить ширину в символах объекта типа string

template<typename T>
void printColumn(T obj, int columnWidth); //Вывести объект в ячейку таблицы указанной ширины

void printSeparator(int width, char ch); //Вывести разделитель указанной ширины между строками таблицы
void printRow(const Plane& plane, int index); //Вывести данные рейса в строку таблицы
void printRow(const Account& account, int index); //Вывести данные аккаунта в строку таблицы

void printRow(Plane tableType, std::vector<std::string> values); //Вывести шапку таблицы рейсов
void printRow(Account tableType, std::vector<std::string> values); //Вывести шапку таблицы аккаунтов