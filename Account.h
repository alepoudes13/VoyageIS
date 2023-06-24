#pragma once

#include <iostream>
#include <string>

class Account {
public:
    enum Role { USER, ADMIN, EMPTY };
    const std::string rolesArray[3] = { "User", "Admin", "Empty" };
    const int columnWidth[6] = { 10, 30, 30, 30, 15, 10}, argsCnt = 6;
    friend void printRow(const Account& account, int index);

    bool compareLogin(std::string login) { return this->login == login; }
    bool compareLogin(Account account) { return this->login == account.login; }
    void setLogin(std::string login) { this->login = login; }
    bool tryPassword(std::string password) { return this->saltedHashPassword == this->saltifyPassword(password); }
    void setPassword(std::string password) { this->saltedHashPassword = this->saltifyPassword(password); }
    void setAccess(bool access) { this->access = access; }
    bool getAccess() { return this->access; }
    void setRole(Account::Role role) { this->role = role; }
    Account::Role getRole() { return this->role; }
    //------------------------------
    Account();
    Account(std::string login, std::string password, bool access = false, Role role = Account::Role::USER);
    friend std::istream& operator>>(std::istream& in, Account& acc);
    friend std::ostream& operator<<(std::ostream& out, const Account& acc);
    Account& operator=(const Account& other);
private:
    std::string login, saltedHashPassword, salt;
    Role role;
    bool access;
    void generateSalt();
    std::string saltifyPassword(std::string password);
};