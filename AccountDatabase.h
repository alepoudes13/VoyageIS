#pragma once

#include "TablePrinting.h"
#include "Account.h"
#include <vector>
#include <fstream>

class AccountDatabase {
    const std::string ACCOUNTS_FILE = "accounts.txt";
    std::vector<Account> accounts;
    Account accountsVector[100];
public:
    const std::vector<std::string> columnNames = { "Индекс", "Логин", "Пароль(под солью)", "Соль", "Роль", "Доступ" };
    AccountDatabase();
    ~AccountDatabase();
    void show(); //Вывести данные аккаунтов таблицей
    int addAccount(std::string login, std::string password); //Добавить аккаунт в базу, вернуть индекс
    int findByLogin(std::string login); //Найти индекс аккаунта в базе по логину
    Account getAtIndex(int index); //Вернуть аккаунт по индексу в базе
    void setAtIndex(int index, Account account); //Установить аккаунт в позицию индекса в базе
    void deleteAtIndex(int index); //Удалить аккаунт из базы по индексу
};

