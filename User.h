#pragma once
#include "PlaneDatabase.h"
#include "Menu.h"

class User {
protected:
	PlaneDatabase* planeDatabase;
	void findPlanes(); //Поиск рейсов
	void sortPlanes(); //Сортировка рейсов
	void sellTickets(); //Продажа билетов
public:
	User();
	~User();
	void startModule(); //Запуск модуля пользователя
};

