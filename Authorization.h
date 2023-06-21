#pragma once
#include "AccountDatabase.h"
#include "ValidatedInput.h"
#include <conio.h>

class Authorization {
    AccountDatabase* accountDatabase;
    Account activeAccount;
public:
    Authorization();
    ~Authorization();
    void protectedInput(std::string& password); //Ввод, скрытый символами звёздочки
    void startModule(bool isLoggingNeeded = true); //Запуск модуля авторизации
    Account getActiveAccount(); //Получить активную учётную запись
    void setActiveAccount(Account account); //Задать активную учётную запись
    AccountDatabase* getAccountDB(); //Вернуть указатель на базу аккаунтов
};

