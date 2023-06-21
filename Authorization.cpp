#include "Authorization.h"

Authorization::Authorization() {
	this->accountDatabase = new AccountDatabase;
}

Authorization::~Authorization() {
	delete this->accountDatabase;
}

void Authorization::protectedInput(std::string& password) {
	password.clear();
	for (char x = _getch(); x != '\r'; x = _getch()) {
		if (x == '\b') {
			if (!password.empty()) {
				std::cout << "\b \b";
				password.erase(password.size() - 1);
			}
			continue;
		}
		password += x;
		putch('*');
	}
	std::cout << '\n';
}

void Authorization::startModule(bool isLoggingNeeded) {
	std::string login, password;
	std::cout << "������� ����� - ";
	std::cin >> login;
	std::cout << "������� ������ - ";
	this->protectedInput(password);
	int index = this->accountDatabase->addAccount(login, password);
	Account acc = this->accountDatabase->getAtIndex(index);
	if (acc.tryPassword(password)) {
		if (acc.getAccess() == false) {
			std::cout << "�� ���� ������� � ����. �������� ������������� ����������� ���������������.\n";
			if (isLoggingNeeded)
				this->activeAccount = Account();
		}
		else if (isLoggingNeeded)
			this->activeAccount = this->accountDatabase->getAtIndex(index);
		else
			std::cout << "�� ����� ���������� ������ ������������� ��������.\n";
	}
	else {
		std::cout << "������������ ������\n";
		if(isLoggingNeeded)
			this->activeAccount = Account();
	}
}

Account Authorization::getActiveAccount() {
	return this->activeAccount;
}

void Authorization::setActiveAccount(Account account) {
	this->activeAccount = account;
}

AccountDatabase* Authorization::getAccountDB() {
	return this->accountDatabase;
}