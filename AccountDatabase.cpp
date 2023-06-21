#include "AccountDatabase.h"

AccountDatabase::AccountDatabase() {
    std::ifstream in(AccountDatabase::ACCOUNTS_FILE, std::ifstream::in);
    int n = -1;
    in >> n;
    if (n == -1)
        return;
    in.ignore();
    this->accounts.resize(n);
    for (int i = 0; i < n; i++)
        in >> this->accounts[i];
}

AccountDatabase::~AccountDatabase() {
    std::ofstream out(AccountDatabase::ACCOUNTS_FILE, std::ofstream::out);
    out << this->accounts.size() << '\n';
    for (size_t i = 0; i < this->accounts.size(); i++)
        out << this->accounts[i];
}

void AccountDatabase::show() {
    printRow(Account(), this->columnNames);
    for (size_t i = 0; i < this->accounts.size(); i++)
        printRow(this->accounts[i], i);
}

int AccountDatabase::addAccount(std::string login, std::string password) {
    Account acc(login, password);
    int index = this->findByLogin(login);
    if (index == -1) {
        if (this->accounts.empty()) {
            acc.setRole(Account::Role::ADMIN);
            acc.setAccess(true);
        }
        this->accounts.push_back(acc);
        return this->accounts.size() - 1;
    }
    return index;
}

int AccountDatabase::findByLogin(std::string login) {
    for (size_t i = 0; i < this->accounts.size(); i++)
        if (this->accounts[i].compareLogin(login))
            return i;
    return -1;
}

Account AccountDatabase::getAtIndex(int index) {
    if (index < 0 || index >= static_cast<int>(this->accounts.size()))
        return Account();
    return this->accounts[index];
}

void AccountDatabase::setAtIndex(int index, Account account) {
    if (index < 0 || index >= static_cast<int>(this->accounts.size()))
        return;
    this->accounts[index] = account;
}

void AccountDatabase::deleteAtIndex(int index) {
    if (index < 0 || index >= static_cast<int>(this->accounts.size()))
        return;
    this->accounts.erase(this->accounts.begin() + index);
}