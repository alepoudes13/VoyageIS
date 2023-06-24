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
    const std::vector<std::string> columnNames = { "Index", "Login", "Salted password", "Salt", "Role", "Access" };
    AccountDatabase();
    ~AccountDatabase();
    void show();
    int addAccount(std::string login, std::string password);
    int findByLogin(std::string login);
    Account getAtIndex(int index);
    void setAtIndex(int index, Account account);
    void deleteAtIndex(int index);
};
