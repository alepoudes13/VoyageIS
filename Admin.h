#pragma once
#include "Authorization.h"
#include "PlaneDatabase.h"
#include "Menu.h"
#include "User.h"

class Admin : private User {
	Authorization* auth;
	void startAccountModule(); //Запуск модуля работы с аккаунтами
	void startDataModule(); //Запуск модуля работы с данными
	void editAccount(); //Редактировать аккаунт
	void changeLogin(int index); //Изменить логин
	void changePassword(int index); //Изменить пароль
	void changeRole(int index); //Изменить уровень доступа
	void deleteAccount(); //Удалить аккаунт
	void verify(); //Разрешить доступ
	void block(); //Запретить доступ
	//------------
	void addPlane(); //Добавить рейс
	void editPlane(); //Редактировать рейс
	void deletePlane(); //Удалить рейс
public:
	Admin(Authorization* auth);
	void startMainModule(); //Запуск модуля администратора
};

