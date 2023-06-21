#include "Account.h"

Account::Account() : access(false), role(Account::Role::EMPTY) {
    this->salt = this->login = this->saltedHashPassword = "";
}

Account::Account(std::string login, std::string password, bool access, Role role) : access(access), role(role) {
    this->login = login;
    this->generateSalt();
    this->saltedHashPassword = this->saltifyPassword(password);
}

void Account::generateSalt() {
    this->salt.resize(rand() % 20 + 1);
    for (size_t i = 0; i < this->salt.size(); i++)
        this->salt[i] = (char)'A' + rand() % 60;
}

std::string Account::saltifyPassword(std::string password) {
    std::string salted_password(password.size(), '-');
    int saltLen = this->salt.size();
    for (size_t i = 0; i < password.size(); i++) 
        salted_password[i] = (char) (password[i] + this->salt[i % saltLen]) % 224 + 32;
    return salted_password;
}

std::istream& operator>>(std::istream& in, Account& acc) {
    std::getline(in, acc.login);
    std::getline(in, acc.salt);
    std::getline(in, acc.saltedHashPassword);
    int n = 0;
    in >> n >> acc.access;
    acc.role = Account::Role(n);
    in.ignore(1, '\n');
    return in;
}

std::ostream& operator<<(std::ostream& out, const Account& acc) {
    out << acc.login << '\n';
    out << acc.salt << '\n';
    out << acc.saltedHashPassword << '\n';
    out << acc.role << ' ' << acc.access << '\n';
    return out;
}

Account& Account::operator=(const Account& other) {
    this->login = other.login;
    this->saltedHashPassword = other.saltedHashPassword;
    this->salt = other.salt;
    this->role = other.role;
    this->access = other.access;
    return *this;
}