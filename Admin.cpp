#include "Admin.h"

Admin::Admin(Authorization* auth) {
	this->auth = auth;
}

void Admin::startMainModule() {
	int actionCase;
	enum State { Exit, Acc, Data };
	std::vector<std::string> menuLines = {
		"�����.",
		"������ � ����������.",
		"������ � �������."
	};
	std::string title = "--------���� ������--------------------------";
	Menu menu(title, menuLines);

	do {
		actionCase = menu.getResponse();
		switch (actionCase)
		{
		default:
		case Exit:
			break;
		case Acc:
			this->startAccountModule();
			break;
		case Data:
			this->startDataModule();
			break;
		}
	} while (actionCase != Exit);
}

void Admin::startAccountModule() {
	int actionCase;
	enum State { Exit, View, Add, Edit, Delete, Verify, Block };
	std::vector<std::string> menuLines = {
		"�����.",
		"��������.",
		"����������.",
		"��������������.",
		"��������.",
		"�����������.",
		"����������."
	};
	std::string title = "--------������ � ����������------------------";
	Menu menu(title, menuLines);

	do {
		actionCase = menu.getResponse();
		switch (actionCase)
		{
		default:
		case Exit:
			break;
		case View:
			this->auth->getAccountDB()->show();
			break;
		case Add:
			this->auth->startModule(false);
			break;
		case Edit:
			this->editAccount();
			break;
		case Delete:
			this->deleteAccount();
			break;
		case Verify:
			this->verify();
			break;
		case Block:
			this->block();
			break;
		}
	} while (actionCase != Exit);
}

void Admin::editAccount() {
	int index;
	�ustValidatedInput("������� ������ ��������: ", 1, "%d", &index);
	Account acc = this->auth->getAccountDB()->getAtIndex(index);
	if (acc.getRole() == Account::Role::EMPTY) {
		std::cout << "[!] ��� �������� � ����� ��������.\n";
		return;
	}

	int actionCase;
	enum State { Exit, ChangeLogin, ChangePassword, ChangeRole };
	std::vector<std::string> menuLines = {
		"�����.",
		"�������� �����.",
		"�������� ������.",
		"�������� ������� �������."
	};
	std::string title = "--------�������������� ��������--------------";
	Menu menu(title, menuLines);

	std::string input;
	do {
		actionCase = menu.getResponse();
		switch (actionCase)
		{
		default:
		case Exit:
			break;
		case ChangeLogin:
			this->changeLogin(index);
			break;
		case ChangePassword:
			this->changePassword(index);
			break;
		case ChangeRole:
			this->changeRole(index);
			break;
		}
		acc = this->auth->getAccountDB()->getAtIndex(index);
	} while (actionCase != Exit);
}

void Admin::changeLogin(int index) {
	std::string login;
	Account acc = this->auth->getAccountDB()->getAtIndex(index);
	std::cout << "������� ����� �����: ";
	std::cin >> login;
	int checkIndex = this->auth->getAccountDB()->findByLogin(login);
	if (checkIndex == -1) {
		acc.setLogin(login);
		if (this->auth->getActiveAccount().compareLogin(acc))
			this->auth->setActiveAccount(acc);
		this->auth->getAccountDB()->setAtIndex(index, acc);
		std::cout << "����� ������� ��������.\n";
	}
	else
		std::cout << "����� ����� ��� ���� � ���� ������.\n";
}

void Admin::changePassword(int index) {
	std::string password;
	Account acc = this->auth->getAccountDB()->getAtIndex(index);
	std::cout << "������� ����� ������: ";
	this->auth->protectedInput(password);
	acc.setPassword(password);
	if (this->auth->getActiveAccount().compareLogin(acc))
		this->auth->setActiveAccount(acc);
	this->auth->getAccountDB()->setAtIndex(index, acc);
	std::cout << "������ ������� ��������.\n";
}

void Admin::changeRole(int index) {
	Account acc = this->auth->getAccountDB()->getAtIndex(index);
	if (acc.compareLogin(this->auth->getActiveAccount())) {
		std::cout << "[!] ������ �������� ���� ������� �������.\n";
		return;
	}
	if (acc.getRole() == Account::Role::USER) {
		acc.setRole(Account::Role::ADMIN);
		this->auth->getAccountDB()->setAtIndex(index, acc);
		std::cout << "������� ��� ������� ������� ��������������.\n";
	}
	else if (acc.getRole() == Account::Role::ADMIN) {
		acc.setRole(Account::Role::USER);
		this->auth->getAccountDB()->setAtIndex(index, acc);
		std::cout << "������� ��� ����� ���� ��������������.\n";
	}
}

void Admin::deleteAccount() {
	int index;
	�ustValidatedInput("������� ������ ��������: ", 1, "%d", &index);
	Account acc = this->auth->getAccountDB()->getAtIndex(index);
	if (acc.getRole() == Account::Role::EMPTY) {
		std::cout << "[!] ��� �������� � ����� ��������.\n";
		return;
	}
	if (acc.compareLogin(this->auth->getActiveAccount())) {
		std::cout << "[!] ������ ������� ���� �������.\n";
		return;
	}
	std::cout << "�� �������? ������� Enter, ����� ����������� ��������.";
	char ch = _getch();
	if (ch == '\r') {
		this->auth->getAccountDB()->deleteAtIndex(index);
		std::cout << "\n������� ��� ������.\n";
	}
	else
		std::cout << "\n[!] �������� ���� ��������.\n";
}

void Admin::verify() {
	int index;
	�ustValidatedInput("������� ������ ��������: ", 1, "%d", &index);
	Account acc = this->auth->getAccountDB()->getAtIndex(index);
	if (acc.getRole() == Account::Role::EMPTY) {
		std::cout << "[!] ��� �������� � ����� ��������.\n";
		return;
	}
	acc.setAccess(true);
	this->auth->getAccountDB()->setAtIndex(index, acc);
	std::cout << "������� ������� ������ � �������\n";
}

void Admin::block() {
	int index;
	�ustValidatedInput("������� ������ ��������: ", 1, "%d", &index);
	Account acc = this->auth->getAccountDB()->getAtIndex(index);
	if (acc.getRole() == Account::Role::EMPTY) {
		std::cout << "[!] ��� �������� � ����� ��������.\n";
		return;
	}
	if (acc.compareLogin(this->auth->getActiveAccount())) {
		std::cout << "[!] ������ ������������� ���� �������.\n";
		return;
	}
	acc.setAccess(false);
	this->auth->getAccountDB()->setAtIndex(index, acc);
	std::cout << "������� ��� ����� ������� � �������\n";
}

//----------------------------------------------

void Admin::startDataModule() {
	int actionCase;
	enum State { Exit, View, Add, Edit, Delete, Search, Sort, Sell };
	std::vector<std::string> menuLines = {
		"�����.",
		"��������.",
		"����������.",
		"��������������.",
		"��������.",
		"�����.",
		"����������.",
		"������� �������."
	};
	std::string title = "--------������ � ����������------------------";
	Menu menu(title, menuLines);

	do {
		actionCase = menu.getResponse();
		switch (actionCase)
		{
		default:
		case Exit:
			break;
		case View:
			this->planeDatabase->show();
			break;
		case Add:
			this->addPlane();
			break;
		case Edit:
			this->editPlane();
			break;
		case Delete:
			this->deletePlane();
			break;
		case Search:
			this->findPlanes();
			break;
		case Sort:
			this->sortPlanes();
			break;
		case Sell:
			this->sellTickets();
			break;
		}
	} while (actionCase != Exit);
}

void Admin::addPlane() {
	Plane plane;
	plane.read();
	int index = this->planeDatabase->addPlane(plane);
	if (index == -1)
		std::cout << "[!] ������� � ����� ������� ��� ���� � ���� ������.\n";
}

void Admin::editPlane() {
	int index;
	�ustValidatedInput("������� ������ ��������: ", 1, "%d", &index);
	Plane plane = this->planeDatabase->getAtIndex(index);
	if (plane.isObjectEmpty()) {
		std::cout << "[!] ��� �������� � ����� ��������.\n";
		return;
	}

	int actionCase;
	enum State{Exit};
	std::vector<std::string> menuLines = {
		"�����.",
		"�����.",
		"���� ������.",
		"���� ������.",
		"������� ������.",
		"������� ������.",
		"����� �����������.",
		"���� �����������.",
		"����� ��������.",
		"�����������.",
		"��� ��������."
	};
	std::string title = "--------�������������� ��������--------------";
	Menu menu(title, menuLines);

	std::string* newStr; size_t* newInt; Time* newTime; Date* newDate;
	do {
		actionCase = menu.getResponse();
		switch (actionCase)
		{
		case Exit:
			break;
		default:
			plane.assignPointers(newStr, newInt, newTime, newDate, actionCase);
			if (newStr) {
				std::cout << "������� ����� �������� ����: ", std::getline(std::cin, *newStr);
				if (*newStr == "") std::getline(std::cin, *newStr);
			}
			else if (newInt) {
				int temp;
				do {
					�ustValidatedInput("������� ����� �������� ����: ", 1, "%d", &temp);
				} while (temp < 0);
				*newInt = temp;
				plane.updateCapacity();
			}
			else if (newTime)
				newTime->readLoop("������� ����� �������� ����(��:��): ");
			else
				newDate->readLoop("������� ����� �������� ����(��:��): ");
			this->planeDatabase->setAtIndex(index, plane);
			break;
		}
	} while (actionCase != Exit);
}

void Admin::deletePlane() {
	int index;
	�ustValidatedInput("������� ������ ��������: ", 1, "%d", &index);
	Plane plane = this->planeDatabase->getAtIndex(index);
	if (plane.isObjectEmpty()) {
		std::cout << "[!] ��� �������� � ����� ��������.\n";
		return;
	}
	std::cout << "�� �������? ������� Enter, ����� ����������� ��������.";
	char ch = _getch();
	if (ch == '\r') {
		this->planeDatabase->deleteAtIndex(index);
		std::cout << "\n������� ��� ������.\n";
	}
	else
		std::cout << "\n[!] �������� ���� ��������.\n";
}