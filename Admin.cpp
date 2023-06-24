#include "Admin.h"

Admin::Admin(Authorization* auth) {
	this->auth = auth;
}

void Admin::startMainModule() {
	int actionCase;
	enum State { Exit, Acc, Data };
	std::vector<std::string> menuLines = {
		"Back.",
		"Accounts management.",
		"Data management."
	};
	std::string title = "--------Admin menu---------------------------";
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
		"Back.",
		"Viewing.",
		"Addition.",
		"Editing.",
		"Deletion.",
		"Verification.",
		"Blocking."
	};
	std::string title = "--------Accounts management------------------";
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
	ñustValidatedInput("Enter account index: ", 1, "%d", &index);
	Account acc = this->auth->getAccountDB()->getAtIndex(index);
	if (acc.getRole() == Account::Role::EMPTY) {
		std::cout << "[!] No account with such an index.\n";
		return;
	}

	int actionCase;
	enum State { Exit, ChangeLogin, ChangePassword, ChangeRole };
	std::vector<std::string> menuLines = {
		"Exit.",
		"Change login.",
		"Change password.",
		"Change access."
	};
	std::string title = "--------Account edit-------------------------";
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
	std::cout << "Enter new login: ";
	std::cin >> login;
	int checkIndex = this->auth->getAccountDB()->findByLogin(login);
	if (checkIndex == -1) {
		acc.setLogin(login);
		if (this->auth->getActiveAccount().compareLogin(acc))
			this->auth->setActiveAccount(acc);
		this->auth->getAccountDB()->setAtIndex(index, acc);
		std::cout << "Login was changed.\n";
	}
	else
		std::cout << "Account with this login already exists.\n";
}

void Admin::changePassword(int index) {
	std::string password;
	Account acc = this->auth->getAccountDB()->getAtIndex(index);
	std::cout << "Enter new password: ";
	this->auth->protectedInput(password);
	acc.setPassword(password);
	if (this->auth->getActiveAccount().compareLogin(acc))
		this->auth->setActiveAccount(acc);
	this->auth->getAccountDB()->setAtIndex(index, acc);
	std::cout << "Password was changed.\n";
}

void Admin::changeRole(int index) {
	Account acc = this->auth->getAccountDB()->getAtIndex(index);
	if (acc.compareLogin(this->auth->getActiveAccount())) {
		std::cout << "[!] Can't change your own access.\n";
		return;
	}
	if (acc.getRole() == Account::Role::USER) {
		acc.setRole(Account::Role::ADMIN);
		this->auth->getAccountDB()->setAtIndex(index, acc);
		std::cout << "Account was given admin rights.\n";
	}
	else if (acc.getRole() == Account::Role::ADMIN) {
		acc.setRole(Account::Role::USER);
		this->auth->getAccountDB()->setAtIndex(index, acc);
		std::cout << "Account is no longer an admin.\n";
	}
}

void Admin::deleteAccount() {
	int index;
	ñustValidatedInput("Enter account index: ", 1, "%d", &index);
	Account acc = this->auth->getAccountDB()->getAtIndex(index);
	if (acc.getRole() == Account::Role::EMPTY) {
		std::cout << "[!] No account with such an index.\n";
		return;
	}
	if (acc.compareLogin(this->auth->getActiveAccount())) {
		std::cout << "[!] Can't delete your own account.\n";
		return;
	}
	std::cout << "Are you sure? Press ENTER to confirm.";
	char ch = _getch();
	if (ch == '\r') {
		this->auth->getAccountDB()->deleteAtIndex(index);
		std::cout << "\nAccount was deleted.\n";
	}
	else
		std::cout << "\n[!] Deletion was canceled.\n";
}

void Admin::verify() {
	int index;
	ñustValidatedInput("Enter account index: ", 1, "%d", &index);
	Account acc = this->auth->getAccountDB()->getAtIndex(index);
	if (acc.getRole() == Account::Role::EMPTY) {
		std::cout << "[!] No account with such an index.\n";
		return;
	}
	acc.setAccess(true);
	this->auth->getAccountDB()->setAtIndex(index, acc);
	std::cout << "Account got system access\n";
}

void Admin::block() {
	int index;
	ñustValidatedInput("Enter account index: ", 1, "%d", &index);
	Account acc = this->auth->getAccountDB()->getAtIndex(index);
	if (acc.getRole() == Account::Role::EMPTY) {
		std::cout << "[!] No account with such an index.\n";
		return;
	}
	if (acc.compareLogin(this->auth->getActiveAccount())) {
		std::cout << "[!] Can't block your own account.\n";
		return;
	}
	acc.setAccess(false);
	this->auth->getAccountDB()->setAtIndex(index, acc);
	std::cout << "Account no longer has system access\n";
}

//----------------------------------------------

void Admin::startDataModule() {
	int actionCase;
	enum State { Exit, View, Add, Edit, Delete, Search, Sort, Sell };
	std::vector<std::string> menuLines = {
		"Back.",
		"Viewing.",
		"Addition.",
		"Edition.",
		"Deletion.",
		"Seach.",
		"Sorting.",
		"Tickets selling."
	};
	std::string title = "--------Planes management--------------------";
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
		std::cout << "[!] Voyage with such an index already exists.\n";
}

void Admin::editPlane() {
	int index;
	ñustValidatedInput("Enter voyage index: ", 1, "%d", &index);
	Plane plane = this->planeDatabase->getAtIndex(index);
	if (plane.isObjectEmpty()) {
		std::cout << "[!] No voyage with such an index.\n";
		return;
	}

	int actionCase;
	enum State{Exit};
	std::vector<std::string> menuLines = {
		"Exit.",
		"Number.",
		"Price bussiness.",
		"Price econom.",
		"Tickets bussiness.",
		"Tickets econom.",
		"Departure time.",
		"Departure date.",
		"Arrival time.",
		"Destination.",
		"Plane type."
	};
	std::string title = "--------Voyage edit--------------------------";
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
				std::cout << "Enter new value: ", std::getline(std::cin, *newStr);
				if (*newStr == "") std::getline(std::cin, *newStr);
			}
			else if (newInt) {
				int temp;
				do {
					ñustValidatedInput("Enter new value: ", 1, "%d", &temp);
				} while (temp < 0);
				*newInt = temp;
				plane.updateCapacity();
			}
			else if (newTime)
				newTime->readLoop("Enter new value(hh:mm): ");
			else
				newDate->readLoop("Enter new value(hh:mm): ");
			this->planeDatabase->setAtIndex(index, plane);
			break;
		}
	} while (actionCase != Exit);
}

void Admin::deletePlane() {
	int index;
	ñustValidatedInput("Enter voyage index: ", 1, "%d", &index);
	Plane plane = this->planeDatabase->getAtIndex(index);
	if (plane.isObjectEmpty()) {
		std::cout << "[!] No voyage with such an index.\n";
		return;
	}
	std::cout << "Are you sure? Press ENTER to continue.";
	char ch = _getch();
	if (ch == '\r') {
		this->planeDatabase->deleteAtIndex(index);
		std::cout << "\nVoyage was deleted.\n";
	}
	else
		std::cout << "\n[!] Deletion was canceled.\n";
}